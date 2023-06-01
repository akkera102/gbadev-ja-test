//by Pegmode  

#define LIB_MODE 0//flag to disable main/ enable library call

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include "patchrom.h"
//CONSTANTS
//===========================================================
#define DEFLEMASK_DATA_START 0xC0
#define VGM_SAMPLE_RATE 44100//this is rate that a vgm file samples the registers
#define GB_BANK_SIZE 0x3FFF//~16kb per bank
#define TMA_RATE0 4096//TMA rate in hz
#define TMA_RATE1 262144//TMA rate in hz
#define TMA_RATE2 65536//TMA rate in hz
#define TMA_RATE3 16384
#define MAX_TEXT_LEN 20
//vgm commands
#define WRITEVGMCOMMAND 0xB3
#define WAITSTDVGMCOMMAND 0x62 //wait for a single engine frame (1/60s)
#define WAITVGMCOMMAND 0x61 //wait for xy vgm frames (1/VGM_SAMPLE_RATE)
#define ENDVGMCOMMAND 0x66
#define DATABLOCKVGMCOMMAND 0x67
#define WAITPALCOMMAND 0x63//wait for a PAL engine frame (legal in Deflemask)
//custom GB engine commands

#define WRITECUSCOMMAND 0xB0 //writedata to 0xFFxy
#define WRITECUSHRAM 0xB0 //writes data to anywhere in HRAM
#define WAITCUSCOMMAND 0x80 //wait for x frames
#define NEXTBANKCUSCOMMAND 0xA0 //go to next bank
#define LOOPCUSCOMMAND 0xC0 //Loop to loop address and bank
#define ENDSONGCUSCOMMAND 0xD0 //end song
//ENGINE VARS
//===========================================================
#define DATA_START_BANK 0x01
#define DEFAULT_SYNC_HIGH_ADDRESS 0x80//change this to change where the sync signal writes to 
#define MAX_DATABANKS 0xFF//must be less than or equal to what the asm engine is designed to handle and never greater than 0xFF

//Deflemask Player ROM Pointers
//===========================================================
//Pointers for included player ROM
//There is a helper script ../tools/generateRomPointers.py to automatically scan for these from the asm .sym file
#define ROM_LOOP_POINTER_ADDRESS 0x3FFC// loopAddress label in ROM, gives address to loop to
#define ROM_LOOP_BANK_ADDRESS 0x3FFE// loopBank label in ROM, gives bank to loop to
#define ROM_SONG_TMA_MOD_CONST 0x3FFA//tmaMod label in ROM, gives song TMA, disables if 0
#define ROM_SONG_TMA_TAC_CONST 0x3FFB
#define TITLE_PATCH_ADDRESS 0x22F //textData5
#define AUTHOR_PATCH_ADDRESS 0x0244 //textData6

//GBS consts
//===========================================================
//WARNING THESE CAN CHANGE IF ROM IS UPDATED
#define GBS_DATA_START 0x3EF0//address contained in "EngineCode" section in ROM
#define GBS_INIT GBS_DATA_START//our gbs code is at the beginning of load
#define GBS_PLAY 0x3f26// DMEngineUpdate label
#define GBS_SP 0xFFFE


struct VgmBuffer{//contains vgm info and file buffer for Deflemask generated GB Vgm
    uint8_t* buffer;
    int size;
    uint8_t rate;
};
typedef struct VgmBuffer VgmBuffer;

struct LoopInfo{//contains address and bank info for looping 
    int gbLoopAddress;
    int gbLoopBank;
};
typedef struct LoopInfo LoopInfo;

struct SongInfo{
    char* artist;//20 char long
    char* title;
};
typedef struct SongInfo SongInfo;

//Globals
//===========================================================
int EXPORTMODE = 0;//0 = patch .gb, 1 = bin, 2 = gbs
int ENGINE_RATE = 60;//default rate to 60hz
char OUTPATH[0xFF] = "output";
char* PATCHROM_PATH = "patchROM.gb";
int TMA_OFFSET = 0;//value to add to TMA for fine control
int LOOPVGMADDR = 0;//loop address in .vgm file 0 = no loop

char* HELPSTRING = "\nversion 0.6\nHelp:\n DeflemaskGBGMConverter <input vgm> [args...]\n\
\nargs:\n\
-r <rate> set engine rate\n\
-o <outpath> set the output path\n\
-bin export as .bin file instead of patching .gb\n\
-g export as .gbs\n\
-ti <offset> increase tma offset timing (speed up song if using custom engine speed)\n\
-td <offset> decrease tma offset timing (slow down song if using custom engine speed)\n";
 
//CODE
//===========================================================

uint8_t vgmToGBTL(uint8_t value){//translate vgm write command destination address to actual FFxy value
    return value + 0x10;
}

void write16Bit(uint8_t* dest,int val){//little endian for .gbs
    dest[0] = (uint8_t)val&0xFF;
    dest[1] = (uint8_t)(val>>8)&0xFF;
}

void printfLibless(char* format,...){//printf only when LIB_MODE = 0 for Deflemask support requested by Delek
#if LIB_MODE
    return;
#else
    va_list args;
    va_start(args, format);
    printf(format,args);
    return;
#endif
}

void sprintfLibless(char* format,...){//sprintf only when LIB_MODE = 0 for Deflemask support requested by Delek
#if LIB_MODE
    return;
#else
    va_list args;
    va_start(args, format);
    sprintf(format,args);
    return;
#endif
}

void openFile(char* path,VgmBuffer* vgmBuffer){
    FILE *f;
    f = fopen(path,"rb");
    fseek(f,0,SEEK_END);
    int fileSize = ftell(f);
    vgmBuffer->buffer = malloc(fileSize);
    fseek(f,0,SEEK_SET);
    if(fread(vgmBuffer->buffer,1,fileSize,f) < 1){
        //womp womp
        printfLibless("Error: VGM file had issue opening\n");
    }
    fclose(f);
    vgmBuffer->size = fileSize;
}

void checkHeader(VgmBuffer vgmBuffer){
    //test Header

    if (memcmp(vgmBuffer.buffer,"Vgm",3) != 0){
        printfLibless(".vgm header fail\n");
        exit(0);
    }
    //check gb
    int gbEmptyVal = 0;
    if (memcmp(&vgmBuffer.buffer[0x80],&gbEmptyVal,4) == 0){
        printfLibless(".vgm does not use Game Boy\n");
        exit(0);
    }
    //copy loop value
    int loopVal = 0;
    int loopSamples;//use for detecting legacy
    memcpy(&loopSamples,&vgmBuffer.buffer[0x20],4);
    if (loopSamples != 0){//check for legacy Deflemask .vgm bug
        memcpy(&loopVal,&vgmBuffer.buffer[0x1C],4);
    }
    if(loopVal > 0x1C){
        loopVal += 0x1C;//calculate offset val
    }
    LOOPVGMADDR = loopVal;
}

int checkIfBankEnd(int currentOutputPos,int distance){//check if a given write operation to the output buffer will fall outside a Game Boy ROM bank
    if((currentOutputPos + distance + 1) > GB_BANK_SIZE){//add 1 so we make sure we have room for bank
        return 1;
    }
    else{
        return 0;
    }
}

int samplesToFrames(int engineRate,int samples){//calculate the number of frames based on number of samples
    float frameCount = ((float)samples / (float)VGM_SAMPLE_RATE) / (1 / (float)engineRate);
    //printf("frameCount: %u\nengineRate: %u\nsamples: %u\n",frameCount,engineRate,samples);
    if (frameCount != (int)frameCount){
        double whole;
        float fractional = modf(frameCount, &whole);
        if (fractional < 0.98){
            printfLibless("ERROR: Frame calculation failure. Engine tick rate of %uhz is likely incorrect. Use -r argumment to change engine rate\n",ENGINE_RATE);
            exit(1);
        }
        whole++;
        frameCount = whole;
    }
    return (int)frameCount;
}

int calculateTMAModulo(int tmaRate){//calculate the modulo value to use
    float floatDistance = (float)tmaRate/(float)ENGINE_RATE;
    double whole;
    float fract;
    fract = modf(floatDistance,&whole);
    if (fract >= 0.5){
        whole++;
    }
    return 0xFF-(int)whole;
}

void checkVgmIsDeflemask(VgmBuffer vgmBuffer){
    uint8_t deflemaskFooter[] = {0x44, 0x00, 0x65, 0x00, 0x66, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x4D, 0x00, 0x61, 0x00, 0x73, 0x00, 0x6B, 0x00, 0x20, 0x00, 0x54, 0x00, 0x72, 0x00, 0x61, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x65, 0x00, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00,};
    uint8_t footerBuffer[0x26];
    memcpy(footerBuffer,&vgmBuffer.buffer[vgmBuffer.size-0x26],0x26);
    if(memcmp(deflemaskFooter,footerBuffer,0x26) != 0){
        printfLibless("vgm was not Generated by Deflemask. Only Deflemask .vgms are supported.");
        exit(1);
    }
}

void writeAllBanks(uint8_t** banks,int numBanks){//bin export mode
    char outputName[0xFF];
    for(int i = 0; i <= numBanks; i++){
        sprintf(outputName,"%s%u.bin",OUTPATH,i);
        FILE *f = fopen(outputName,"wb");
        fwrite(banks[i],1,GB_BANK_SIZE,f);
        fclose(f);
    }
}

int findStartOfVGMString(VgmBuffer vgmBuffer, int startPos){//scans for the beginning of a string in .vgm
    bool isScanning = true;
    int i = 0;
    while(isScanning){
        if(vgmBuffer.buffer[vgmBuffer.size-startPos-2*i] == 0){
            return vgmBuffer.size-startPos-2*i + 2;
        }
        else if(vgmBuffer.size-startPos-2*i == 0){//couldn't find begnning of string
            //error
        }
        else{
            i++;
        }
    }
}

int scanVgmString(VgmBuffer vgmBuffer, char* output, int startPos){
    //find start of string
    int stringStartAddress = findStartOfVGMString(vgmBuffer, startPos);
    for(int i = 0; i < MAX_TEXT_LEN; i++){
        output[i] = vgmBuffer.buffer[stringStartAddress + i*2];
        if(vgmBuffer.buffer[stringStartAddress + i*2] == '\0'){
            return stringStartAddress;
        }
    }
    output[MAX_TEXT_LEN-1] = '\0';
    return stringStartAddress;
    
}

void getSongInfo(SongInfo* songInfo, VgmBuffer vgmBuffer){
    //to get song/artist, walk backwards from Defle Ident
    char* artist = malloc(MAX_TEXT_LEN);
    char* title = malloc(MAX_TEXT_LEN);
    int artistStartAddress = scanVgmString(vgmBuffer, artist, 0x3E);
    int titleEndoffset = vgmBuffer.size - (artistStartAddress - 0x32); //offset from EOF, really hacky
    int songStartAddress = scanVgmString(vgmBuffer, title, titleEndoffset);
    #if !LIB_MODE
    printf("Artist: %s\n", artist);
    printf("Title: %s\n", title);
    #endif    
    songInfo->title = title;
    songInfo->artist = artist;
}

void exportGBS(SongInfo songInfo, uint8_t* patchBuffer, int patchBufferSize){//patch patched rom to .gbs and export
    //build gbs
    uint8_t* gbsFile;
    int gbsSize = 0x70 + patchBufferSize - GBS_DATA_START;
    gbsFile = (uint8_t*) malloc(gbsSize);
    memcpy(&gbsFile[0],"GBS",3);//Identifier
    gbsFile[3] = 1;
    gbsFile[4] = 1;//NUMBER OF SONGS
    gbsFile[5] = 1;//First song
    //load Address
    write16Bit(&gbsFile[0x6], GBS_DATA_START);
    //init address
    write16Bit(&gbsFile[0x8], GBS_INIT);
    //play address
    write16Bit(&gbsFile[0xA], GBS_PLAY);
    //SP init
    write16Bit(&gbsFile[0xC], GBS_SP);
    //timer modulo(rTMA)
    gbsFile[0xE] = 0;//init 0
    //timer control(rTAC)
    gbsFile[0xF] = 0;//init0

    if (patchBuffer[ROM_SONG_TMA_TAC_CONST] != 0 ){
        //overwrite TMA,TAC if using custom timing
        memcpy(&gbsFile[0xE], &patchBuffer[ROM_SONG_TMA_MOD_CONST], 1);
        memcpy(&gbsFile[0xF], &patchBuffer[ROM_SONG_TMA_TAC_CONST], 1);
    }

    //add title/author
    strcpy(&gbsFile[0x10], songInfo.title);
    strcpy(&gbsFile[0x30], songInfo.artist);

    //printf("PATCH BUFFER %x\n", patchBuffer[GBS_DATA_START]);
    memcpy(&gbsFile[0x70], &patchBuffer[GBS_DATA_START], patchBufferSize - GBS_DATA_START);

    //write to .gbs file
    char outROMPath[0xFF];

    if(OUTPATH[strlen(OUTPATH)-4]!='.'){
        sprintf(outROMPath,"%s.gbs",OUTPATH);
    }
    else{//deflemask call compatibility  
        sprintf(outROMPath,"%s",OUTPATH);
    }
    FILE* f = fopen(outROMPath, "wb");
    fwrite(gbsFile, 1, gbsSize, f);
    fclose(f);
    free(gbsFile);
    return;
}

void patchROM(uint8_t** banks,int numBanks, LoopInfo loopInfo, SongInfo songInfo){
    //load patch ROM into buffer
    int patchBufferSize = gb_patch_rom_length + (numBanks + 1) * 0x4000;
    uint8_t* patchBuffer = malloc(patchBufferSize);
    memcpy(patchBuffer, gb_patch_rom, gb_patch_rom_length);
    //copy bank buffer 
    for (int i = 0; i < numBanks+1; i++){
        memcpy(&patchBuffer[0x4000+i*0x4000],banks[i],0x3FFF);
    }
    // write TMA 
    int tmaDistance = 0;
    if (ENGINE_RATE != 60){
        tmaDistance = calculateTMAModulo(TMA_RATE0);
        patchBuffer[ROM_SONG_TMA_TAC_CONST] = 4;
    }
    else{
        patchBuffer[ROM_SONG_TMA_TAC_CONST] = 0;
    }
    //write loop data
    if (LOOPVGMADDR != 0){
        memcpy(&patchBuffer[ROM_LOOP_POINTER_ADDRESS],&loopInfo.gbLoopAddress,2);
        memcpy(&patchBuffer[ROM_LOOP_BANK_ADDRESS],&loopInfo.gbLoopBank,2);
    }

    patchBuffer[ROM_SONG_TMA_MOD_CONST] = tmaDistance + TMA_OFFSET;

    if(EXPORTMODE == 0){//.gb export mode
        strcpy(&patchBuffer[TITLE_PATCH_ADDRESS], songInfo.title);
        strcpy(&patchBuffer[AUTHOR_PATCH_ADDRESS], songInfo.artist);

        char outROMPath[0xFF];
        sprintf(outROMPath,"%s.gb",OUTPATH);
        if(OUTPATH[strlen(OUTPATH)-3]!='.'){
            sprintf(outROMPath,"%s.gb",OUTPATH);
        }
        else{//deflemask call compatibility  
            sprintf(outROMPath,"%s",OUTPATH);
        }
        FILE* f = fopen(outROMPath,"wb");
        
        int outputSize = gb_patch_rom_length + 0x4000 * (numBanks + 1);
        fwrite(patchBuffer,1,outputSize,f);
        fclose(f);
    }
    if(EXPORTMODE == 2){//.gbs export mode
        exportGBS(songInfo, patchBuffer, patchBufferSize);
    }
    free(patchBuffer);

}

void convertToNewFormat(VgmBuffer vgmBuffer){
    LoopInfo loopInfo;
    int currentVgmPos = DEFLEMASK_DATA_START;
    int currentBank = 0;//NOT TRUE BANK, is position in output array
    int currentOutputPos = 0;
    int notEndOfFile = 1;
    uint8_t* output[0xFF];//array of banks
    while(notEndOfFile){//we don't know how many banks the output will take up ahead of time
        //create new block
            //while in block parse until we hit the maxsize
            //create new ,
        uint8_t* currentBankBuffer = malloc(GB_BANK_SIZE);
        memset(currentBankBuffer,0,GB_BANK_SIZE);
        currentOutputPos = 0;
        int notEndOfBank = 1 ;
        while(notEndOfBank){
            if (currentVgmPos == LOOPVGMADDR){//checkForLoop
                printfLibless("loop found!\n");
                loopInfo.gbLoopAddress = currentOutputPos + 0x4000;
                loopInfo.gbLoopBank = currentBank+ DATA_START_BANK;
                printfLibless("DEBUG loop adr %X\nloopBank %X\n",loopInfo.gbLoopAddress,loopInfo.gbLoopBank);
            }
            switch(vgmBuffer.buffer[currentVgmPos]){
                case WRITEVGMCOMMAND://write to 0xFFXX
                    if (checkIfBankEnd(currentOutputPos,3)){
                        notEndOfBank = 0;    
                        currentBankBuffer[currentOutputPos] = NEXTBANKCUSCOMMAND;
                    }
                    else{
                        //NOTE new format means that NRxx register writes addresses take up the command space
                        //if first byte bit7 = 0 then this byte contains the write address
/*
                        currentVgmPos++;
                        currentBankBuffer[currentOutputPos] = vgmToGBTL(vgmBuffer.buffer[currentVgmPos]);//write address
                        currentVgmPos++;
                        currentOutputPos++;
                        currentBankBuffer[currentOutputPos] = vgmBuffer.buffer[currentVgmPos];//write value
                        currentVgmPos++;
                        currentOutputPos++;
*/
//---------------------------------------------------------------------------
// patched. GB->GBA sound register 2023/06/01

	currentVgmPos++;
	uint8_t adr1 = vgmToGBTL(vgmBuffer.buffer[currentVgmPos]);//write address
	uint8_t adr2 = 0;

	switch(adr1)
	{
	case 0x10: adr2 = 0x60-0x50; break;	// NR 10
	case 0x11: adr2 = 0x62-0x50; break;	// NR 11
	case 0x12: adr2 = 0x63-0x50; break;	// NR 12
	case 0x13: adr2 = 0x64-0x50; break;	// NR 13
	case 0x14: adr2 = 0x65-0x50; break;	// NR 14
	case 0x16: adr2 = 0x68-0x50; break;	// NR 21
	case 0x17: adr2 = 0x69-0x50; break;	// NR 22
	case 0x18: adr2 = 0x6c-0x50; break;	// NR 23
	case 0x19: adr2 = 0x6d-0x50; break;	// NR 24
	case 0x1a: adr2 = 0x70-0x50; break;	// NR 30
	case 0x1b: adr2 = 0x72-0x50; break;	// NR 31
	case 0x1c: adr2 = 0x73-0x50; break;	// NR 32
	case 0x1d: adr2 = 0x74-0x50; break;	// NR 33
	case 0x1e: adr2 = 0x75-0x50; break;	// NR 34
	case 0x20: adr2 = 0x78-0x50; break;	// NR 41
	case 0x21: adr2 = 0x79-0x50; break;	// NR 42
	case 0x22: adr2 = 0x7c-0x50; break;	// NR 43
	case 0x23: adr2 = 0x7d-0x50; break;	// NR 44
	case 0x24: adr2 = 0x80-0x50; break;	// NR 50
	case 0x25: adr2 = 0x81-0x50; break;	// NR 51
	case 0x26: adr2 = 0x84-0x50; break;	// NR 52

	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x3d:
	case 0x3e:
	case 0x3f:
		adr2 = 0x90 + (adr1 - 0x30) - 0x50;
		break;

	default:
		printfLibless("WARNING invalid adr=%x\n", adr1);
		break;
	}

	currentBankBuffer[currentOutputPos] = adr2;
    currentVgmPos++;
    currentOutputPos++;


	uint8_t dat = vgmBuffer.buffer[currentVgmPos];//write value

	// NR 30
	if(adr1 == 0x1a)
	{
		dat &= 0x80;
	}

	// NR 32
	if(adr1 == 0x1c)
	{
		dat &= 0x60;
	}

	// NR 50
	if(adr1 == 0x24 && dat & 0x08)
	{
		printfLibless("WARNING no use GBA bit. FF24 Right Flag.\n");
	}

	// NR 50
	if(adr1 == 0x24 && dat & 0x80)
	{
		printfLibless("WARNING no use GBA bit. FF24 Left Flag.\n");
	}

    currentBankBuffer[currentOutputPos] = dat;
    currentVgmPos++;
    currentOutputPos++;

//---------------------------------------------------------------------------

                    }                                       
                    break;
                case WAITVGMCOMMAND://wait for XX frames
                    if (checkIfBankEnd(currentOutputPos,3)){
                        notEndOfBank = 0;    
                        currentBankBuffer[currentOutputPos] = NEXTBANKCUSCOMMAND;
                    }
                    else{
                        //be careful: calculate frames from number of samples
                        currentBankBuffer[currentOutputPos] = WAITCUSCOMMAND;//write new command
                        currentOutputPos++;
                        currentVgmPos++;
                        int highV = (int)vgmBuffer.buffer[currentVgmPos];
                        currentVgmPos++;
                        int lowV = (int)vgmBuffer.buffer[currentVgmPos];
                        int numberOfSamples = (lowV << 8) | highV;//mask 16bit 
                        int numberOfFrames = samplesToFrames(ENGINE_RATE,numberOfSamples);//change 60 to be scanned value later
                        currentBankBuffer[currentOutputPos] = numberOfFrames;
                        currentVgmPos++;
                        currentOutputPos++; 
                    }
                    break;
                case WAITSTDVGMCOMMAND://wait for 1 frame in 60hz engine rate
                    if (checkIfBankEnd(currentOutputPos,3)){
                        notEndOfBank = 0;   
                        currentBankBuffer[currentOutputPos] = NEXTBANKCUSCOMMAND; 
                    }
                    else{
                        currentBankBuffer[currentOutputPos] = WAITCUSCOMMAND;//write new command
                        currentOutputPos++;
                        currentBankBuffer[currentOutputPos] = 1;
                        currentVgmPos++;
                        currentOutputPos++;
                    }
                    break;

                case DATABLOCKVGMCOMMAND://write data to 0xFF<SYNC_ADDRESS> +=9
                    if (checkIfBankEnd(currentOutputPos,3)){
                        notEndOfBank = 0;    
                        currentBankBuffer[currentOutputPos] = NEXTBANKCUSCOMMAND;
                    }
                    else{
                        currentVgmPos += 9;//jump to data block value
                        currentBankBuffer[currentOutputPos] = WRITECUSHRAM;
                        currentOutputPos++;
                        currentBankBuffer[currentOutputPos] = DEFAULT_SYNC_HIGH_ADDRESS;
                        currentOutputPos++;
                        currentBankBuffer[currentOutputPos] = vgmBuffer.buffer[currentVgmPos];
                        currentVgmPos++;
                        currentOutputPos++;
                    }
                    break;
                case WAITPALCOMMAND:
                    if (checkIfBankEnd(currentOutputPos,3)){
                        notEndOfBank = 0;   
                        currentBankBuffer[currentOutputPos] = NEXTBANKCUSCOMMAND; 
                    }
                    else{
                        if(ENGINE_RATE != 50){
                            printfLibless("Error: PAL wait tick found in non PAL timed module! Did you enter the correct engine speed?\n");
                            exit(1);
                        }
                        currentBankBuffer[currentOutputPos] = WAITCUSCOMMAND;//write new command
                        currentOutputPos++;
                        currentBankBuffer[currentOutputPos] = 1;
                        currentVgmPos++;
                        currentOutputPos++;
                    }
                break;
                case ENDVGMCOMMAND://end the song
                    printfLibless("VGM end found!\n");
                    if (LOOPVGMADDR == 0){
                        currentBankBuffer[currentOutputPos] = ENDSONGCUSCOMMAND;//write new command

                    }
                    else{
                        currentBankBuffer[currentOutputPos] = LOOPCUSCOMMAND;//write new command

                    }
                    currentOutputPos++;
                    notEndOfBank = 0;
                    notEndOfFile = 0;
                    break;
                default:
                    printfLibless("Error while parsing vgm commands, incorrect command found\n");
                    exit(1);
            }
        }
    output[currentBank] = currentBankBuffer;
    if (notEndOfFile){
        currentBank++;
    }
    }

    
    if (EXPORTMODE == 1){//if asm export (.bin) mode was enabled
        if (ENGINE_RATE != 60){
            int tmaDistance = calculateTMAModulo(TMA_RATE0);
            printfLibless("Non-vBlank Engine speed found, set TMA to = 0x%X\n",tmaDistance);
        }
        writeAllBanks(output,currentBank);       
    }

    else{//.gb export mode or .gbs export mode
        SongInfo songInfo;
        //debug
        getSongInfo(&songInfo, vgmBuffer);
        patchROM(output, currentBank, loopInfo, songInfo);
        free(songInfo.artist);
        free(songInfo.title);
    }

    #if !LIB_MODE
    printf("Conversion Complete!\n%u banks used\n",currentBank+1);//hacky bug solution
    #endif
}

void parseArgs(int argc, char** argv){
    if (argc < 2){
        printfLibless("Must give a .vgm as argument to program\n");
        printfLibless(HELPSTRING);
        exit(1);
    }
    for (int i = 2; i < argc; i++){
        if(strcmp("-r",argv[i]) == 0){//rate
            i++;
            ENGINE_RATE = atoi(argv[i]);
            #if !LIB_MODE
            printf("Engine rate set to %i\n",ENGINE_RATE);//hacky bug solution
            #endif
        }
        else if(strcmp("-o",argv[i]) == 0){//output path
            i++;
            strcpy(OUTPATH,argv[i]);
        }
        else if(strcmp("-h",argv[i]) == 0){//help 
            printfLibless(HELPSTRING);
            exit(1);
        }
        else if(strcmp("-bin",argv[i]) == 0){//bin export
            EXPORTMODE = 1;
        }
        else if(strcmp("-td",argv[i]) == 0){//tma decrease
            TMA_OFFSET = -atoi(argv[++i]);
        }
        else if(strcmp("-ti",argv[i]) == 0){//tma increase
            TMA_OFFSET = atoi(argv[++i]);
        }
        else if(strcmp("-g",argv[i]) == 0){//gbs export
            //.gbs is generated is ROM patch because .gbs patching only cuts off
            //lower addresses from the patched rom
            EXPORTMODE = 2;
        }
    }   

}
#if LIB_MODE
int gbvgm(char *vgm_source_path, int hz, char* romPath){  // For .gb creation in library mode
    EXPORTMODE = 0;
    TMA_OFFSET = 0;
    ENGINE_RATE = hz;
    strcpy(OUTPATH,romPath);
    VgmBuffer vgmBuffer;
    openFile(vgm_source_path,&vgmBuffer);
    checkHeader(vgmBuffer);
    checkVgmIsDeflemask(vgmBuffer);
    convertToNewFormat(vgmBuffer);
    free(vgmBuffer.buffer);
    return 0;
}

int gbsRender(char *vgm_source_path, int hz, char* romPath){//I think this should work. Feel free to change if it does not
    EXPORTMODE = 2;
    TMA_OFFSET = 0;
    ENGINE_RATE = hz;
    strcpy(OUTPATH,romPath);
    VgmBuffer vgmBuffer;
    openFile(vgm_source_path,&vgmBuffer);
    checkHeader(vgmBuffer);
    checkVgmIsDeflemask(vgmBuffer);
    convertToNewFormat(vgmBuffer);
    free(vgmBuffer.buffer);
    return 0;

}
#else
int main(int argc, char* argv[]){
    parseArgs(argc,argv);
    printfLibless("RUNNING\n");
    VgmBuffer vgmBuffer;
    printfLibless("OPENING .vgm\n");    
    openFile(argv[1],&vgmBuffer);
    printfLibless("OPENED\n");
    checkHeader(vgmBuffer);
    printfLibless("Header Check passed!\n");
    checkVgmIsDeflemask(vgmBuffer);
    printfLibless("Deflemask Footer check passed!\n");
    convertToNewFormat(vgmBuffer);
    free(vgmBuffer.buffer);
    return 0;
}
#endif