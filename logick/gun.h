/*
 * =====================================================================================
 *
 *       Filename:  gun.h
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

/*! Default init 
 */
#include <stdint.h>

struct T_gun_status {
  uint16_t amons;
  uint16_t health;

  uint8_t life;
};

extern struct T_gun_status gun_status;

int init();
int shoot();
int hitting(int group, int pid, int power, int loc);
