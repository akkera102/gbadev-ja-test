MAKEFLAGS	+=--no-print-directory

SHELL	= sh
NAME	= test
GAMECODE= TEST
PREFIX	= arm-none-eabi-

AS		= $(PREFIX)as
CC 		= $(PREFIX)gcc
CPP		= $(PREFIX)g++
LD 		= $(PREFIX)g++
AR 		= $(PREFIX)ar
OBJCOPY	= $(PREFIX)objcopy
NM		= $(PREFIX)nm

INCDIR	= .

AFILES	= 

SFILES	= \
	$(wildcard res/*.s) \
	$(wildcard snd/*.s) \
	$(wildcard libgba/*.s) \
	$(wildcard libmy/*.s) \
	$(wildcard *.s)

CFILES	= \
	$(wildcard res/*.c) \
	$(wildcard snd/*.c) \
	$(wildcard libgba/*.c) \
	$(wildcard libmy/*.c) \
	$(wildcard *.c)


VPATH =  $(dir $(CFILES) $(SFILES) $(AFILES))

#=============================================================================

ASFLAGS	= -mthumb-interwork --fatal-warnings
CFLAGS	= -mthumb-interwork -nostdlib -fverbose-asm -fpeephole -mtune=arm7tdmi -mcpu=arm7tdmi $(foreach incdir,$(INCDIR),-I$(incdir) ) -Wall -W -Wshadow -Wno-unused-parameter -Wno-strict-aliasing

OBJDIR  = obj
CFLAGS_THUMB= $(CFLAGS) -mthumb -O3
CFLAGS_ARM	= $(CFLAGS) -marm -O3

OFILES      = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SFILES) $(CFILES) $(AFILES)))))
DFILES      = $(addprefix $(OBJDIR)/, $(addsuffix .d, $(basename $(notdir $(CFILES)))))

MAPFILE		= $(NAME).map
NMFILE      = $(NAME).nm
TARGET_ELF	= $(NAME).elf
TARGET_BIN	= $(NAME).gba

LDFLAGS		= -Map $(MAPFILE) -Wall -lstdc++ -mthumb-interwork -specs=gba.specs -nostartfiles

#=============================================================================

.PHONY: all clean
all: 
	@make -C res
	@make $(TARGET_BIN) ;

clean:
	@make clean -C res
	rm -f $(OFILES) $(DFILES) $(MAPFILE) $(NMFILE) $(TARGET_ELF) $(TARGET_BIN)


$(TARGET_BIN): $(TARGET_ELF)
	@$(PREFIX)objcopy -v -O binary $< $@
	@gbafix $@ -t$(NAME) -c$(GAMECODE)
	@padbin 256 $@

$(TARGET_ELF): $(OBJDIR) $(OFILES) $(AFILES) Makefile
	@echo \# Linking $@
	@echo > $(MAPFILE)
	@$(LD) -o $@ $(OFILES) $(AFILES) -Wl,$(LDFLAGS)
	@$(NM) -n $@ > $(NMFILE)

$(OBJDIR):
	@[ -d $@ ] || mkdir -p $@

#=============================================================================

.SUFFIXES: .S .s .cpp .c .o .a .d

$(OBJDIR)/%_arm.o: %_arm.c
	@echo \# compiling $<
	@$(CC) -MMD $(CFLAGS_ARM) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@echo \# compiling $<
	@$(CC) -MMD $(CFLAGS_THUMB) -c $< -o $@

$(OBJDIR)/%_arm.o: %_arm.cpp
	@echo \# compiling $<
	@$(CPP) -MMD $(CFLAGS_ARM) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	@echo \# compiling $<
	@$(CPP) -MMD $(CFLAGS_THUMB) -c $< -o $@

$(OBJDIR)/%.o: %.s
	@echo \# assembling $<
	@$(AS) $(ASFLAGS) $< -o $@

$(OBJDIR)/%.o: %.S
	@echo \# assembling $<
	@$(AS) $(ASFLAGS) $< -o $@

-include $(DFILES)
