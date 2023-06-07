MAKEFLAGS	+=--no-print-directory

SHELL		= sh
NAME		= test
GAMECODE	= TEST
PREFIX		= arm-none-eabi-

AS			= $(PREFIX)as
CC 			= $(PREFIX)gcc
CPP			= $(PREFIX)g++
LD 			= $(PREFIX)g++
AR 			= $(PREFIX)ar
OBJCOPY		= $(PREFIX)objcopy
NM			= $(PREFIX)nm

OBJDIR		= obj
MAPFILE		= $(NAME).map
NMFILE		= $(NAME).nm
TARGET_ELF	= $(NAME).elf
TARGET_BIN	= $(NAME).gba

INCDIR	= . ./lib

SFILES	= \
	$(wildcard res/*.s) \
	$(wildcard snd/*.s) \
	$(wildcard lib/*.s) \
	$(wildcard *.s) \

CFILES	= \
	$(wildcard res/*.c) \
	$(wildcard snd/*.c) \
	$(wildcard lib/*.c) \
	$(wildcard *.c) \

VPATH = $(dir $(CFILES) $(SFILES))

#=============================================================================

ASFLAGS = 
LDFLAGS = -Map $(MAPFILE) -Wall -specs=gba.specs -nostartfiles -nostdlib
CFLAGS  = -g -O3 -mcpu=arm7tdmi -mtune=arm7tdmi -fomit-frame-pointer -ffast-math -Wall -W -Wshadow -Wno-unused-parameter -Wno-strict-aliasing $(foreach incdir,$(INCDIR),-I$(incdir))
OFILES  = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SFILES) $(CFILES)))))
DFILES  = $(addprefix $(OBJDIR)/, $(addsuffix .d, $(basename $(notdir $(SFILES) $(CFILES)))))

#=============================================================================

.PHONY: all clean
all: 
	@make -C res
	@make $(TARGET_BIN);

clean:
	@make clean -C res
	rm -f $(OFILES) $(DFILES) $(MAPFILE) $(NMFILE) $(TARGET_ELF) $(TARGET_BIN)

$(TARGET_BIN): $(TARGET_ELF)
	@$(PREFIX)objcopy -v -O binary $< $@
	@gbafix $@ -t$(NAME) -c$(GAMECODE)
	@padbin 256 $@

$(TARGET_ELF): $(OBJDIR) $(OFILES)  Makefile
	@echo \# Linking $@
	@echo > $(MAPFILE)
	@$(LD) -o $@ $(OFILES) -Wl,$(LDFLAGS)
	@$(NM) -n $@ > $(NMFILE)

$(OBJDIR):
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
