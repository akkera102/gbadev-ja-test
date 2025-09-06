TXTFILES	= $(wildcard *.txt)
BINFILES	= $(wildcard *.bin)
BMPFILES	= $(wildcard *.bmp)
PNGFILES	= $(wildcard *.png)
HFILES	= $(wildcard *.h)

SFILES	= \
	$(TXTFILES:.txt=.s) \
	$(BINFILES:.bin=.s) \
	$(BMPFILES:.bmp=.s) \
	$(PNGFILES:.png=.s)

#=============================================================================
all: $(SFILES);

clean:
	rm -f $(SFILES) $(HFILES)

.SUFFIXES: .S .s .c .o .a .d .bmp .png .txt .bin

%.s: %.txt
	@echo \# Convert $<
	@bin2s $< > $@

%.s: %.bin
	@echo \# Convert $<
	@bin2s $< > $@

%.s: %.bmp
	@echo \# Convert $<
	@grit $< -ff$*.grit

%.s: %.png
	@echo \# Convert $<
	@grit $< -ff$*.grit
