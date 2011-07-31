/* Name: main.c
 * Project: IrReceiver
 * Author: Leonid Myravjev
 * Creation Date: 2011-05-08
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

// INTERRUPTS!
ISR(TIMER2_COMPA_vect )
{
  static char aa=0;
  TIFR2=0;
  TCNT2=0;
  aa++;

  // XXX: don't change "4", revicer using many constants for
  //  valid work.
  if(!(aa%4)){ // division by 4.
    send_iteration();
  }
  recv_iteration();
}

//////////////////////////////
int i=0;
int main(void)
{
    wdt_disable();
    cli();

    DDRB=0xff;
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
   /// CODER
    sei();
    do{
      cli();
      if(send_is_freely()==0){
        sei();
        _delay_ms(1000);
        cli();
        send_set_message(msg, 8);
      }
      sei();
    }while(1);
    return 0;
}


