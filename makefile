IDIR=include
CC=gcc
CFLAGS=`sdl2-config --libs --cflags` -Wall -I$(IDIR)

ODIR=obj
LDIR=lib

LIBS=-lm

_DEPS = chip8.h mem.h display.h cpu.h sound.h font.h debug.h input.h timer.h file.h settings.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = chip8.o mem.o display.o cpu.o sound.o font.o debug.o input.o timer.o file.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

chip8: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CC_SDL) $(LIBS)

$(OBJ): $(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 