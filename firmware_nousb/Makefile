include config.make

DEVICE = atmega168
AVRDUDE = avrdude -c ${TYPEPROG} -p m168

#COMPILE = avr-gcc -save-temps -Wall -Os -Iusbdrv -I. -mmcu=$(DEVICE)  -L/usr/i686-pc-linux-gnu/avr/lib #-DDEBUG_LEVEL=2
#COMPILE = avr-gcc -save-temps -Wall -Os -Iusbdrv -I. -mmcu=$(DEVICE)  -L/usr/x86_64-pc-linux-gnu/avr/lib #-DDEBUG_LEVEL=2
#COMPILE = avr-gcc -save-temps -Os -Wall -Iusbdrv -I. -mmcu=$(DEVICE)  
COMPILE = avr-gcc -Os -Wall -I. -I${USB_CMD_DIR} -mmcu=$(DEVICE)  
#COMPILE = avr-gcc -Os -Wall -I. -I${USB_CMD_DIR} -mmcu=$(DEVICE)  
OBJECTS = main.o timer.o logick.o sender.o

# symbolic targets:
all: config.make main.hex

config.make:
	@echo "# FIXME, add true rules!"             > config.make
	@echo "USB_CMD_DIR=../../Circuts/interface/" >> config.make
	@echo "TYPEPROG=stk500v2 -P avrdoper"        >> config.make
	@echo "#TYPEPROG=siprog -P /dev/ttyS1"       >> config.make
	@echo "I CREATE config.make file, please FIX IT and rerun me again!"
	false

logick.o:
	$(COMPILE) -c ../logick/ircoder.c -o $@

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -F -U flash:w:main.hex:i

k:	all
	$(AVRDUDE)

dis:
	avr-objdump -D main.bin| less


# Fuse low byte:
# 0xef = 1 1 1 0   1 1 1 1
#        ^ ^ \+/   \--+--/
#        | |  |       +------- CKSEL 3..0 (clock selection -> crystal @ 12 MHz)
#        | |  +--------------- SUT 1..0 (BOD enabled, fast rising power)
#        | +------------------ CKOUT (clock output on CKOUT pin -> disabled)
#        +-------------------- CKDIV8 (divide clock by 8 -> don't divide)
#
# Fuse high byte:
# 0xdb = 1 1 0 1   1 0 1 1
#        ^ ^ ^ ^   \-+-/ ^
#        | | | |     |   +---- RSTDISBL (disable external reset -> enabled)
#        | | | |     +-------- BODLEVEL 2..0 (brownout trigger level -> 2.7V)
#        | | | +-------------- WDTON (watchdog timer always on -> disable)
#        | | +---------------- SPIEN (enable serial programming -> enabled)
#        | +------------------ EESAVE (preserve EEPROM on Chip Erase -> not preserved)
#        +-------------------- DWEN (debug wire enable)
# 0x5b = 0 1 0 1   1 0 1 1
fuse_tiny2313:	# only needed for attiny2313
	$(AVRDUDE) -U hfuse:w:0xdb:m -U lfuse:w:0xef:m

# Fuse low byte:
# 0xef = 1 1 1 0   1 1 1 1 (at2313)
# 0xe7   1 1 1 0   0 1 1 1 
#        ^ ^ \+/   \--+--/
#        | |  |       +------- CKSEL 3..0 (clock selection -> crystal @ 12 MHz, FULL swing)
#        | |  +--------------- SUT 1..0 (BOD enabled, fast rising power)
#        | +------------------ CKOUT (clock output on CKOUT pin -> disabled)
#        +-------------------- CKDIV8 (divide clock by 8 -> don't divide)
#
# Fuse high byte:
# 0xdb = 1 1 0 1   1 0 1 1 (at2313)
# 0xdf   1 1 0 1   1 1 1 1
#        ^ ^ ^ ^   \-+-/ ^
#        | | | |     |   +---- (not, it at2313) RSTDISBL (disable external reset -> enabled)
#        | | | |     +-------- (not, it at2313) BODLEVEL 2..0 (brownout trigger level -> 2.7V)
#        | | | +-------------- (not, it at2313) WDTON (watchdog timer always on -> disable)
#        | | +---------------- (not, it at2313) SPIEN (enable serial programming -> enabled)
#        | +------------------ (not, it at2313) EESAVE (preserve EEPROM on Chip Erase -> not preserved)
#        +-------------------- (not, it at2313) DWEN (debug wire enable)
# 0x5b = 0 1 0 1   1 0 1 1

fuse_mega88:	# only needed for atmega88
	$(AVRDUDE) -U hfuse:w:0xdf:m -U lfuse:w:0xe7:m
	
fuse_mega168:	# only needed for atmega168
	$(AVRDUDE) -U hfuse:w:0xdf:m -U lfuse:w:0xe7:m
	
	#$(AVRDUDE) -U hfuse:w:0xdb:m -U lfuse:w:0xef:m


clean:
	rm -f main.hex main.lst main.obj main.cof main.list main.map main.eep.hex main.bin *.o usbdrv/*.o main.s usbdrv/oddebug.s usbdrv/usbdrv.s

# file targets:
main.bin:	$(OBJECTS)
	$(COMPILE) -o main.bin $(OBJECTS)

main.hex:	main.bin
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex
	./checksize main.bin
# do the checksize script as our last action to allow successful compilation
# on Windows with WinAVR where the Unix commands will fail.

disasm:	main.bin
	avr-objdump -Sd main.bin

cpp:
	$(COMPILE) -E main.c
