MAKEFLAGS	+=--no-print-directory

SHELL		= sh
NAME		= lsdj2log
PREFIX		= 

AS			= $(PREFIX)as
CC 			= $(PREFIX)g++
CPP			= $(PREFIX)g++
LD 			= $(PREFIX)g++
AR 			= $(PREFIX)ar
OBJCOPY		= $(PREFIX)objcopy
NM			= $(PREFIX)nm

OBJDIR		= obj
MAPFILE		= $(NAME).map
NMFILE		= $(NAME).nm
TARGET_ELF	= $(NAME).elf
TARGET_BIN	= $(NAME).exe

INCDIR	= . ./lib

SFILES	= \
	$(wildcard *.s) \

CFILES	= \
	$(wildcard *.cpp) \

VPATH = $(dir $(CFILES) $(SFILES))

#=============================================================================

ASFLAGS = 
LDFLAGS = -Map $(MAPFILE) -Wall
CFLAGS  = -g -O3 -Wall -W -Wshadow -Wno-unused-parameter -Wno-enum-compare -Wno-switch
OFILES  = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SFILES) $(CFILES)))))
DFILES  = $(addprefix $(OBJDIR)/, $(addsuffix .d, $(basename $(notdir $(SFILES) $(CFILES)))))

#=============================================================================

.PHONY: all clean
all: 
	@make $(TARGET_BIN);

clean:
	rm -f $(OFILES) $(DFILES) $(MAPFILE) $(NMFILE) $(TARGET_ELF) $(TARGET_BIN)

$(TARGET_BIN): $(TARGET_ELF)
	@$(PREFIX)objcopy -v $< $@

$(TARGET_ELF): $(OBJDIR) $(OFILES)  Makefile
	@echo \# Linking $@
	@echo > $(MAPFILE)
	@$(LD) -o $@ $(OFILES) -Wl,$(LDFLAGS)
	@$(NM) -n $@ > $(NMFILE)

$(OBJDIR):
	@[ -d $@ ] || mkdir -p $@

#=============================================================================

.SUFFIXES: .cpp

$(OBJDIR)/%.o: %.cpp
	@echo \# compiling $<
	@$(CC) -MMD -MP -MF $(OBJDIR)/$*.d $(CFLAGS) -c $< -o $@


-include $(DFILES)
