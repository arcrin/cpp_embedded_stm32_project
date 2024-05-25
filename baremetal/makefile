CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0
LDFLAGS= -nostdlib -T linker.ld -Wl,-Map=final.map

all: main.o led.o startup.o final.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^
	
led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o: startup.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf: main.o led.o startup.o 
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf

load:
	openocd -f board/stm32f4discovery.cfg