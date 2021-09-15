IDIR=include
CC=gcc
CFLAGS=`sdl2-config --libs --cflags` -Wall -I$(IDIR) 

ODIR=obj
LDIR=lib

LIBS=

_DEPS = chip8.h mem.h display.h cpu.h sound.h font.h debug.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = chip8.o mem.o display.o cpu.o sound.o font.o debug.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

chip8: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CC_SDL) $(LIBS)

$(OBJ): $(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 