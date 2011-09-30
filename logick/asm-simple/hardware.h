/*
 * =====================================================================================
 *
 *       Filename:  hardware.h
 *
 *    Description:  Hardware for GUN.
 *
 *        Version:  1.0
 *        Created:  07/11/2011 12:34:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myravyev Leonid (ASM), asm@asm.pp.ru
 *        Company:  MaSaM, Moscow
 *
 * =====================================================================================
 */

/* Signal switch on GUN */
int poweron();

int switch_to_life();
int switch_to_dead();
int block_amo(int ms);
