/**************************************/
#pragma once
/**************************************/
#ifndef __ASSEMBLER__
/**************************************/
#include <stdint.h>
/**************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**************************************/

//! [18h] ULC File Header
struct ulc_FileHeader_t {
	uint32_t Magic;        //! [00h] Magic value/signature
	uint16_t BlockSize;    //! [04h] Transform block size
	uint16_t MaxBlockSize; //! [06h] Largest block size (in bytes; 0 = Unknown)
	uint32_t nBlocks;      //! [08h] Number of blocks
	uint32_t RateHz;       //! [0Ch] Playback rate
	uint16_t nChan;        //! [10h] Channels in stream
	uint16_t RateKbps;     //! [12h] Nominal coding rate
	uint32_t StreamOffs;   //! [14h] Offset of data stream
};

//! [10h] ULC State Structure
struct ulc_State_t {
	uint8_t  RdBufIdx;         //! [00h] Buffer currently being streamed by DMA
	uint8_t  nBufProc;         //! [01h] Number of buffers that need processing
	uint16_t LastSubBlockSize; //! [02h] Last subblock size processed
	uint32_t WrBufIdx:1;       //! [04h, b0.. 0] Buffer to next write to
	uint32_t PauseBit:1;       //! [04h, b1.. 1] Stream-is-paused toggle
	uint32_t nBlkRem:30;       //! [04h, b2..31] Blocks remaining in playback
	const struct ulc_FileHeader_t *SoundFile; //! [08h] Sound file being played
	const void *NextData;      //! [0Ch] Next data to read from
};




// fixed 2025/07/26 by akkera102
extern struct ulc_State_t ulc_State;




/**************************************/

//! The size of this buffer depends on:
//!  -ULC_MAX_BLOCK_SIZE
//!  -ULC_STEREO_SUPPORT
//!  -ULC_SINGLE_BUFFER
//! Internally, this is:
//!   int8_t ulc_OutputBuffer[1+ULC_STEREO_SUPPORT][2-ULC_SINGLE_BUFFER][ULC_MAX_BLOCK_SIZE]
extern int8_t ulc_OutputBuffer[];

/**************************************/

//! ulc_StartPlayer(SoundFile)
//! Description: Begin stream playback.
//! Arguments:
//!   SoundFile: Pointer to sound data to play.
//! Returns: Returns TRUE on success, FALSE on failure.
//! Notes:
//!  -This function automatically configures the sound hardware for playback,
//!   but does NOT configure any interrupts. Hardware timer 0 is always used
//!   for FIFO timing, so the recommended usage is to use hardware timer 1 in
//!   slave mode, counting up BlockSize samples, and calling ulc_Sync().
int ulc_StartPlayer(const struct ulc_FileHeader_t *SoundFile);

//! ulc_PausePlayer()
//! ulc_UnpausePlayer()
//! Description: Pause/unpause stream playback.
//! Arguments: None.
//! Returns: Nothing; player is paused.
//! Notes:
//!  -This function is inline because it is very simple.
//!  -This function is safe, as long as the thread calling ulc_UpdatePlayer()
//!   does not race with the thread calling this function.
inline void ulc_PausePlayer  (void) { ulc_State.PauseBit = 1; }
inline void ulc_UnpausePlayer(void) { ulc_State.PauseBit = 0; }

//! ulc_StopPlayer()
//! Description: Stop stream playback.
//! Arguments: None.
//! Returns: Nothing; stream stopped.
//! Notes:
//!  -Unlike the pause functions above, it is not possible to recover from a
//!   stopped player, and playback must be completely restarted.
//!  -This function stops DMA1 (and DMA2 for stereo files), but does NOT
//!   disable the audio hardware.
void ulc_StopPlayer(void);

//! ulc_UpdatePlayer()
//! Description: Decode stream samples.
//! Arguments: None.
//! Returns: Number of bytes decoded in this update.
//! Notes:
//!  -This function can be called at any time; sample decoding will only occur
//!   if State.nBufProc is non-zero (but note that this will only process ONE
//!   buffer per call, rather than all buffers inside a single call).
//!  -This function can be extremely long for long buffer sizes.
void ulc_UpdatePlayer(void);

/**************************************/

//! ulc_SetBlockTimer(SoundFile)
//! Description: Prepare timer 1 for block synchronization.
//! Arguments:
//!   SoundFile: Sound file to read BlockSize from.
//! Returns: Nothing; timer 1 is enabled for synchronization.
//! Notes:
//!  -A timer 1 interrupt still needs to be set up via IE and inside the
//!   interrupt master table; this only handles the timer hardware.
inline void ulc_SetBlockTimer(const struct ulc_FileHeader_t *SoundFile) {
	//! REG_TIMER1_L = -BlockSize
	//! REG_TIMER1_H = ENABLE | IRQ | SLAVE
	*(volatile uint32_t*)0x04000104 = 0xC50000 - SoundFile->BlockSize;
}

//! ulc_Sync()
//! ulc_Sync1ch()
//! ulc_Sync2ch()
//! Description: Synchronize audio DMA.
//! Arguments: None.
//! Returns: Nothing; DMA synchronized.
//! Notes:
//!  -These functions increment State->nBufProc.
//!  -These functions are only available without ULC_SINGLE_BUFFER.
//!  -ulc_Sync() and ulc_Sync2ch() are only available with ULC_STEREO_SUPPORT.
void ulc_Sync(void);
void ulc_Sync1ch(void);
void ulc_Sync2ch(void);




// added 2025/07/26 by akkera102
extern int32_t ulc_LappingBuffer[];




/**************************************/
#ifdef __cplusplus
}
#endif
/**************************************/
#endif
/**************************************/
//! EOF
/**************************************/
