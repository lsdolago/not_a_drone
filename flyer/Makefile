PROJECT=not_a_drone_flyer

PART=TM4C123GH6PM
TARGET=TM4C123_RB2

PREFIX	= arm-none-eabi-
CC		= $(PREFIX)gcc
SIZE	= $(PREFIX)size

# Set the compiler CPU/FPU options.
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=hard

CFLAGS=-mthumb ${CPU} ${FPU} -ffunction-sections -fdata-sections -MD -std=c99
CFLAGS+=-O2 -Wall -pedantic -DPART_${PART} -DTARGET_IS_${TARGET}
CFLAGS+=-lc -lgcc -lm
CFLAGS+=-I.

LDFLAGS=-Wl,--gc-sections --data-sections -Tlinker.ld

OBJECTS=$(patsubst %.c,%.o,$(wildcard driverlib/*.c))
OBJECTS+=$(patsubst %.c,%.o,$(wildcard *.c))

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: ${OBJECTS}
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(PROJECT).elf
	${SIZE} ${PROJECT}.elf

prog:
