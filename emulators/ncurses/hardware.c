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
#include <stdio.h>

int poweron(){
	printw("Initialization....\n");
	printw("Gun is on\n");

	return 0;
}

int H_switch_to_life()
{
	printw("Switch to life\n");

	return 0;
}

int H_switch_to_dead()
{
	printw("Switch to dead\n");

	return 0;
}

int H_block_ammo(int ms)
{
	printw("Block ammo %i ms\n", ms);

	return 0;
}

int H_shoot(int group, int pid,int power, int loc){
 printw("SHOT: %i, %i, %i, %i\n", group, pid, power, loc); 
 return 0;
}

// HOOKS

hook_you_dead(){
  printw("you are dead\n");
}
hook_empty_gun(){
  printw("NO AMO!\n");
}

hook_hitstat_overflow(){
  printw("HIT STAT overflow\n");
}
