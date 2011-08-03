/*
 * main.c  - Main of firmware
 * Creation Date: 2011-05-08
 *
 * Copyright (C) 2011 Leonid Myravjev (asm@asm.pp.ru)
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define F_CPU 12000000UL 

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <avr/power.h>

#include "../logick/ircoder.h"

#include "support.h"
#include "timer.h"

#include "sender.h"
#include "reciver.h"

#include "../logick/gun.h"

//////// HOOKS


int hook_you_dead(){
  return 0;
}
int hook_empty_gun(){
  return 0;
}

int hook_hitstat_overflow(){
  return 0;
}

/////////////////////////
uint16_t audi=0;

// INTERRUPTS!
ISR(TIMER2_COMPA_vect )
{
  static char aa=0;
  static char bb=0;
  TIFR2=0;
  TCNT2=0;
  aa++;

  if(audi){
    if(aa==0){
      audi--;
    }
    BIT(C, 3, (aa>>bb++)&1);
  }

  bb=bb%8;
  // XXX: don't change "4", revicer using many constants for
  //  valid work.
  if(!(aa%4)){ // division by 4.
    send_iteration();
  }
  recv_iteration();
}
////////////////////////////////
        // D3 -- STROBE, D4 -- DATA, D5 -- CLC
int led_code(uint8_t num)
{
  cli(); // FIXME need drop it
  BIT(D, 3, 0);
  //_delay_us(1000);
  int i=8;
  //for(i=0; i<8;i++){
  while(i--){
    BIT(D, 4, (num>>i)&1);
    BIT(D, 5, 0);
  sei(); // FIXME need del it
    _delay_us(5);
  cli(); // FIXME need del it
    BIT(D, 5, 1);
  }
  BIT(D, 3, 1);
  sei();
  return 0;
}


//////////////////////////////
int main(void)
{
    wdt_disable();
    cli();

    DDRB=0xff;
    DDRC=0xff;
    // 36 kHz -- FIXME need normal name for this function.
    timer_load();//it used PORTD -- BIT 6

    // 200-600 us -- FIXME need nomral name for this function.
    frame_timer_load();
    recv_initialize();

   /// CODER (user, gid, gun, CRC)
   //         00111 011  0000 1010
   uint32_t st;
   st=0x3b0a;
   uint8_t msg[8];
   msg[3]=msg[4]=msg[5]=msg[6]=msg[7]=0;
   uint8_t  *code   = (uint8_t*)  &st;

   code2ir_shot(code, msg, 16);
   hitting(1,2,3,4);
   int i;
   /// CODER
    sei();
    do{
      //led_code(0x00);
      cli();
      if(send_is_freely()==0){
        sei();
        led_code(i++);
        _delay_ms(500);
        audi=3;
        cli();
        send_set_message(msg, 8);
      }
      sei();
    }while(1);
    return 0;
}


