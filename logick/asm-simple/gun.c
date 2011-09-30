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

int E_init(){
	gun_status.ammons=100;
	gun_status.health=100;
  gun_status.life=1;
	H_switch_to_life();
	return 0;
}

int E_shoot(){
  if(gun_status.life==0){
    //hook_you_dead();
    return 1; // FIXME you are dead
  }
	if(gun_status.ammons==0){
    //hook_empty_gun();
    return 2; // FIXME gun is emtpy
  }

	gun_status.ammons--;
  H_shoot(gun_status.group,
          gun_status.pid,
          gun_status.power,0);

	H_block_ammo(500); // 0.5 second
	return 0;
}

int E_hitting(int group, int pid, int power, int loc)
{
  if(gun_status.life == 0) 
    return 1;

	//FIXME save groput, pid, power, loc
	if(--gun_status.health==0){
    gun_status.health=0;
    gun_status.life=0;
		H_switch_to_dead();
	}
  if(hitstat_cur<HITSIZE){
    hitstat[hitstat_cur].time=0;
    hitstat[hitstat_cur].group=group;
    hitstat[hitstat_cur].pid=pid;
    hitstat[hitstat_cur].power=power;
    hitstat[hitstat_cur].loc=loc;
    hitstat_cur++;
  }else{
    //H_hook_hitstat_overflow();
    //FIXME -- think about overflow exeptions.
  }

	return 0;
}
