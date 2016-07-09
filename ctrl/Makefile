PROJECT=not_a_drone_ctrl
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

PREFIX		= msp430-elf-
CC      	= $(PREFIX)gcc
SIZE		= $(PREFIX)size
GDB     	= $(PREFIX)gdb
DEVICE  	= msp430g2553
MSPDEBUG	= mspdebug rf2500

CFLAGS = -mmcu=$(DEVICE) -O2

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT).out
	$(SIZE) $(PROJECT).out

debug: all
	$(GDB) $(PROJECT).out

prog: all
	$(MSPDEBUG) "prog $(PROJECT).out"

reset: all
	$(MSPDEBUG) reset

clean:
	rm -rf *.o *.out
