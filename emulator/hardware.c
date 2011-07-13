/*
 * =====================================================================================
 *
 *       Filename:  hardware.c
 *
 *    Description:  Main function for GUN.
 *
 *        Version:  1.0
 *        Created:  07/11/2011 12:32:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myravyev Leonid (ASM), asm@asm.pp.ru
 *        Company:  MaSaM, Moscow
 *
 * =====================================================================================
 */
#include "hardware.h"
#include <stdio.h>

int poweron(){
	printw("Initialization....\n");
	printw("Gun is on\n");

	return 0;
}

int switch_to_life()
{
	printw("Switch to life\n");

	return 0;
}

int switch_to_dead()
{
	printw("Switch to dead\n");

	return 0;
}

int block_amo(int ms)
{
	printw("Block amo %i ms\n", ms);

	return 0;
}


// HOOKS

hook_you_dead(){
  printw("you are dead\n");
}
hook_empty_gun(){
  printw("NO AMO!\n");
}
