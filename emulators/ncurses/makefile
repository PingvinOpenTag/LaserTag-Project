MAINLOGICK_DIR=../../logick
LOGICK_DIR=${MAINLOGICK_DIR}/asm-simple

all:
	make -C ${LOGICK_DIR}
	gcc -c -save-temps emu.c -I${LOGICK_DIR}
	gcc -c hardware.c -I${LOGICK_DIR}
	gcc emu.o hardware.o ${LOGICK_DIR}/gun.o -o main `ncurses5-config --libs`
	./main

WINCC="mingw32-gcc"

win:
	make -C ${LOGICK_DIR}
	${WINCC} -c -save-temps emu.c
	${WINCC} -c hardware.c -I${IFACE_DIR}
	${WINCC} emu.o hardware.o ${LOGICK_DIR}/gun.o -o main `ncurses5-config --libs`
	./main



all2:
	gcc -o main test.c `ncurses5-config --libs`
	./main

