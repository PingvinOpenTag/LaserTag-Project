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
  uint16_t ammons;
  uint16_t health;
  uint8_t  life;

  uint8_t group;
  uint8_t pid;
  uint8_t power;
};

extern struct T_gun_status gun_status;

/* Initizliae logick model (when power on)
 */
int E_init();
/* Shoot key pressed, it function call if 
 * ammo non blocked. (see function H_block_ammo())*/
int E_shoot();

/*! 
 * group -- number of command
 * pid -- Player ID
 * power -- power of GUN
 * loc -- location of
 */
int E_hitting(int group, int pid, int power, int loc);

///////////////////////////////////////////
/* HOOKS -- need realizate in out logick */
/* Произведён выстрел из пистолета. В качестве параметров
 * указываются все параметры стрелявшего.
 * (в том числе номер передатчика)
 */
int H_shoot(int group, int pid, int power, int loc);

/* Сменить стату игрока. Это может быть состояние игрока,
 * может быть смена команды,
 * (из-за чего firmware дожна сменить цвесть светодиодов)
 */
int H_setstatus(int name, int value);

/* Сменить статус игрока. Мертв он или жив.
 */
int H_switch_to_life(); 
int H_switch_to_dead(); 

/* Функция указывает на то, что пистлет пустой.
 * Как правило прошивка должна реадировать на это
 * каким-нибудь звуком или марганием соотвествующим
 * светодиодом.
 */
int H_empty_gun();

/* Функция указывает на то, что нельзя использовать
 * функцию E_shoot в течении usecond секунд.
 */
int H_block_ammo(int usecond); // 
