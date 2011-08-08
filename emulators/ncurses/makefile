
all:
	make -C ../logick
	gcc -c -save-temps emu.c
	gcc -c hardware.c -I../interfaces
	gcc emu.o hardware.o ../logick/gun.o -o main `ncurses5-config --libs`
	./main

WINCC="mingw32-gcc"

win:
	make -C ../logick
	${WINCC} -c -save-temps emu.c
	${WINCC} -c hardware.c -I../interfaces
	${WINCC} emu.o hardware.o ../logick/gun.o -o main `ncurses5-config --libs`
	./main



all2:
	gcc -o main test.c `ncurses5-config --libs`
	./main

