/*
 * =====================================================================================
 *
 *       Filename:  gun.c
 *
 *    Description:  Gun firmware
 *
 *        Version:  1.0
 *        Created:  07/11/2011 12:29:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myravyev Leonid (ASM), asm@asm.pp.ru
 *        Company:  MaSaM, Moscow
 *
 * =====================================================================================
 */

#include <hardware.h>
#include "gun.h"

// FIXME -- move it for hell
#define HITSIZE 10

struct T_gun_status gun_status;

struct T_hitting{
  uint64_t time;
  int group;
  int pid;
  int power;
  int loc;
};

struct T_hitting hitstat[HITSIZE];

int hitstat_cur;
/*! Default init 
 */

int hitstat_clean()
{
  hitstat_cur=0;
  return 0;
}

int init(){
	gun_status.amons=100;
	gun_status.health=100;
  gun_status.life=1;
	switch_to_life();
	return 0;
}

int shoot(){
  if(gun_status.life==0){
    hook_you_dead();
    return 1;
  }
	if(gun_status.amons==0){
    hook_empty_gun();
    return 2;
  }

	gun_status.amons--;
	block_amo(500); // 0.5 second
	return 0;
}
/*! 
 * group -- number of command
 * pid -- Player ID
 * power -- power of GUN
 * loc -- location of
 */

int hitting(int group, int pid, int power, int loc)
{
  if(gun_status.life == 0) 
    return 1;

	//FIXME save groput, pid, power, loc
	if(--gun_status.health==0){
    gun_status.health=0;
    gun_status.life=0;
		switch_to_dead();
	}
  if(hitstat_cur<HITSIZE){
    hitstat[hitstat_cur].time=0;
    hitstat[hitstat_cur].group=group;
    hitstat[hitstat_cur].pid=pid;
    hitstat[hitstat_cur].power=power;
    hitstat[hitstat_cur].loc=loc;
    hitstat_cur++;
  }else{
    hook_hitstat_overflow();
  }

	return 0;
}
