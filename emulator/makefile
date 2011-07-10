
all:
	gcc -c emu.c
	gcc -c hardware.c -I../interfaces
	gcc emu.o hardware.o ../logick/gun.o -o main `ncurses5-config --libs`
	./main

all2:
	gcc -o main test.c `ncurses5-config --libs`
	./main

