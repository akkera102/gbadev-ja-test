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
	@echo \# converting $<
	@bin2s $< > $@

%.s: %.bin
	@echo \# converting $<
	@bin2s $< > $@

%.s: %.bmp
	@echo \# converting $<
	@grit $< -ff$*.grit

%.s: %.png
	@echo \# converting $<
	@grit $< -ff$*.grit
