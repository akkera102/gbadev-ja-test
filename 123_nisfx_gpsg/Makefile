MAKEFLAGS	+= --no-print-directory

SHELL		= sh
NAME		= test
GAMECODE	= TEST
PREFIX		= arm-none-eabi-

AS			= $(PREFIX)as
CC 			= $(PREFIX)gcc
CPP			= $(PREFIX)g++
LD 			= $(PREFIX)g++
AR 			= $(PREFIX)ar
OBJCOPY	= $(PREFIX)objcopy
NM			= $(PREFIX)nm
COPY		= copy
GBAFIX	= gbafix

RESDIR		= res
RES_GBFS	= $(RESDIR)/test.gbfs

VGMCDIR	= tool/vgm2gba
VGMCBATCH = $(VGMCDIR)/_make_gpsg.bat
VGMCFILES	= $(VGMCDIR)/*.gpsg

OBJDIR		= _obj

BINDIR		= _bin
MAPFILE		= $(BINDIR)/$(NAME).map
NMFILE		= $(BINDIR)/$(NAME).nm
TARGET_ELF	= $(BINDIR)/$(NAME).elf
TARGET_BIN	= $(BINDIR)/$(NAME).bin
TARGET_ROM	= $(BINDIR)/$(NAME).gba

INCDIR	= ./lib .

SFILES	= \
	$(wildcard res/*.s) \
	$(wildcard snd/*.s) \
	$(wildcard lib/*.s) \
	$(wildcard src/*.s) \
	$(wildcard *.s) \

CFILES	= \
	$(wildcard res/*.c) \
	$(wildcard snd/*.c) \
	$(wildcard lib/*.c) \
	$(wildcard src/*.c) \
	$(wildcard *.c) \

VPATH = $(dir $(CFILES) $(SFILES))

#=============================================================================
# added. libgba

LIBS = -lgba
export LIBPATHS = $(foreach dir,$(DEVKITPRO)/libgba,-L$(dir)/lib)

INCDIR1 = $(foreach dir,$(INCDIR),-I$(dir))
INCDIR2 = $(foreach dir,$(DEVKITPRO)/libgba,-I$(dir)/include)

#=============================================================================

ASFLAGS = 
LDFLAGS = -Map $(MAPFILE) -Wall -specs=gba.specs -nostartfiles $(LIBS) $(LIBPATHS)
CFLAGS  = -g -O3 -mcpu=arm7tdmi -mtune=arm7tdmi -fomit-frame-pointer -ffast-math -Wall -W -Wshadow -Wno-unused-parameter -Wno-strict-aliasing $(INCDIR1) $(INCDIR2)
OFILES  = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SFILES) $(CFILES)))))
DFILES  = $(addprefix $(OBJDIR)/, $(addsuffix .d, $(basename $(notdir $(SFILES) $(CFILES)))))

#=============================================================================

.PHONY: all clean
all: 
	@make -C res
	@make $(RES_GBFS)
	@make $(TARGET_ROM);

quick:
	@echo \# packing $(RES_GBFS)
	gbfs $(RES_GBFS) $(VGMCFILES)
	@make -C res
	@make $(TARGET_ROM);

clean:
	@make clean -C res
	rm -f $(OFILES) $(DFILES) $(MAPFILE) $(NMFILE) $(RES_GBFS) $(TARGET_ELF) $(TARGET_BIN) $(TARGET_ROM)

$(TARGET_ROM): $(TARGET_BIN)
	@cat $(TARGET_BIN) $(RES_GBFS) > $(TARGET_ROM)
	@$(GBAFIX) $(TARGET_ROM) -tTest -cTest
	@padbin 256 $(TARGET_ROM)

$(TARGET_BIN): $(TARGET_ELF)
	@$(PREFIX)objcopy -v -O binary $< $@
	@$(GBAFIX) $@ -t$(NAME) -c$(GAMECODE)
	@padbin 256 $@

$(TARGET_ELF): $(OBJDIR) $(OFILES) $(BINDIR)  Makefile
	@echo \# Linking $@
	@echo > $(MAPFILE)
	@$(LD) -o $@ $(OFILES) -Wl,$(LDFLAGS)
	@$(NM) -n $@ > $(NMFILE)

$(RES_GBFS):
# 	@echo \# creating gPSG
# 	$(VGMCBATCH)
	@echo \# packing $(RES_GBFS)
	gbfs $(RES_GBFS) $(VGMCFILES)

$(OBJDIR) $(BINDIR):
	@[ -d $@ ] || mkdir -p $@

#=============================================================================

.SUFFIXES: .s .c .o .d

$(OBJDIR)/%.arm.o: %.arm.c
	@echo \# compiling $<
	@$(CC) -MMD -MP -MF $(OBJDIR)/$*.arm.d $(CFLAGS) -marm -c $< -o $@

$(OBJDIR)/%.o: %.c
	@echo \# compiling $<
	@$(CC) -MMD -MP -MF $(OBJDIR)/$*.d $(CFLAGS) -mthumb -c $< -o $@

$(OBJDIR)/%.o: %.s
	@echo \# assembling $<
	@$(CC) -MMD -MP -MF $(OBJDIR)/$*.d -x assembler-with-cpp $(ASFLAGS) -c $< -o $@

-include $(DFILES)
