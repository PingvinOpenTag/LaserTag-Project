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

uint8_t recv[2*8]; // 2 -- bytes on messag; 8 -- IR sensors
uint8_t cur_bit[8];

enum{
  CUR_NONE,
  CUR_ONES,
  CUR_ZERO
};

uint8_t curstate[8];//CUR_NONE;
uint8_t curones[8];
uint8_t curzeros[8];

// INTERRUPTS!
ISR(TIMER2_COMPA_vect )
{
  static char aa=0;
  TIFR2=0;
  TCNT2=0;
  aa++;

  if(!(aa%4)){ // division by 2.
    send_iteration();
  }
  //  BIT(D, 6,  aa    &1);
  //  BIT(B, 4, (aa>>1)&1);
    uint8_t i;
    PORTB=(PORTB & (~(7<<1))) | (0<<1);

    for(i=0;i<8;i++){
    //i=0;

        char bit;
        PORTB=((PORTB & (~(7<<1))) | (i<<1));
        //_delay_us(10);
        //bit=!((PINB>>5)&1);
        bit=!((PINB>>5)&1);
        switch(curstate[i]){
          case CUR_NONE:
            if(bit==1){
              curones[i]=1;
              curzeros[i]=0;
              curstate[i]=CUR_ONES;
            }
            break;
          case CUR_ONES:
            if(bit==0){
              curzeros[i]=1;
              curstate[i]=CUR_ZERO;
            }else{
              curones[i]++;
              if(curones>=9){
                BIT(B, 0, 1);
                cur_bit[i]=0;
                recv[i*2]=0;
                recv[i*2+1]=0;
              }
            }
            break;
          case CUR_ZERO:
            if(bit==1){
              if(cur_bit[i]>=16){
                // BIT(B, 0, 1);
                //false
              }else{
                if(curzeros[i]>=7){
                 // BIT(B, 0, 1);
                  if(cur_bit[i]<8){
                    recv[i*2]   |= (1<<(7 -cur_bit[i]));
                  }else{
                    recv[i*2+1] |= (1<<(15-cur_bit[i]));
                  }
                }else{
                 // BIT(B, 0, 0);
                }
                cur_bit[i]++;
              }
              curzeros[i]=0;
              curones[i]=1;
              curstate[i]=CUR_ONES;
            }else{
              curzeros[i]++;
              if(curzeros[i]>15){
                cur_bit[i]=16;
                BIT(B, 0, 0);
              }
            }
            break;
        }
    }
   //*/

  BIT(B, 4,  aa    &1);
}

//////////////////////////////

int  write=0;
unsigned char IRbytes[200];
uint32_t time=0;

/*
 * Parsing IR channel
 * support function.
 *
 * Get package lenght of "0" or "1".
 */
uint16_t count_bit(uint8_t type, uint8_t trigger)
{
	uint16_t count=0;
	uint8_t trig=trigger;
	uint8_t res;
	//cli();
	while(1){
		DELAYBIT; // 
		//_delay_us(delay); // it eating 3000 kbytes ;-)
		res = IRBYTE1;
		if(res!=type){
			if(trig--==0) break;
		}else trig=trigger;
		count++;
		if(count>MAX_DELAY){
			goto bad_work;
			count=0;
		}
	}
bad_work:
	//sei();
	return count;
}

/*
 * Parsing IR channel
 */
int ir_parse()
{
			char res = IRBYTE1; 
      BIT(D, 6, res);
  		if((res == 1)){//
				uint16_t head_nuls;
				uint16_t head_ones=0;
				// ALL IR DU start on 0xffffff or more (2 ms or more)
				head_ones = count_bit(1, 2);
				head_nuls = count_bit(0, 2) + 2;
#define NEC_RETRY			10
#define NEC_PACKAGE		11
#define PANASONIC		  12
#define DONT_KNOWN		127
				IRbytes[0]=head_ones;
				IRbytes[1]=head_nuls;
				char package_done=1;
				if(head_ones>40){
          /// PROTOCOL DETECT
					IRbytes[2]=DONT_KNOWN;
					if( (head_ones>160) ){//&& (head_ones<833) ){ // Скорее всего NEC
						if( (head_nuls>35) && (head_nuls<46) ){ // Это RETRY пакет NEC
							IRbytes[2]=NEC_RETRY;
							int i=0;
							for(i=0;i<0xff;i++){
								PORTC=(!(i%2))<<3;
								_delay_us(100);
							}
						}else
						 if( (head_nuls>80) ){// && (head_nuls<86) ){ // Это PAKCGE NEC
							IRbytes[2]=NEC_PACKAGE;
							package_done=0;
						}
					}else if( (head_ones>64) && (head_ones<=70) ){
						if( (head_nuls>30) && (head_nuls<35) ){
							IRbytes[2]=PANASONIC;
							package_done=0;
						}
					}
				  write=3;
				}
				uint8_t bytenum=0;
				while(package_done!=1){
						uint8_t ones=2+count_bit(1, 2);
						uint8_t null=count_bit(0, 2);
						if(null==0)
							package_done=1;
						else
							null+=2;
						if( (ones+5)>null){
							IRbytes[write+bytenum/8] &= ~(1<<bytenum%8);
						}else{
							IRbytes[write+bytenum/8] |=  (1<<bytenum%8);
						}
						bytenum++;
						PORTC=(!(bytenum%2))<<3;
						if(bytenum > 100) break;
			}
			write+=bytenum/8+!(!(bytenum%8));
		 }
  return 0;
}


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
    curstate[0]=CUR_NONE;
    curstate[1]=CUR_NONE;
    curstate[2]=CUR_NONE;
    curstate[3]=CUR_NONE;
    curstate[4]=CUR_NONE;
    curstate[5]=CUR_NONE;
    curstate[6]=CUR_NONE;
    curstate[7]=CUR_NONE;

    
    DDRBIT(B, 5, 0);
    char b=0;
   /// CODER (user, gid, gun, CRC)
   //         00111 011  0000 1010
   uint32_t st;
   st=0x3b0a;
   uint8_t msg[8];
   msg[3]=msg[4]=msg[5]=msg[6]=msg[7]=0;
   uint8_t  *code   = (uint8_t*)  &st;
   //send_set_message()
   code2ir_shot(code, msg, 16);
   /// CODER
 //   return 0;
    sei();
    do{
      cli();
      if(send_is_freely()==0){
        sei();
        _delay_ms(1000);
        cli();
        send_set_message(msg, 8);
      }
      //BIT(B, 5, b++&1);
      sei();
      //asm(      " sbr 
    }while(1);
    return 0;
}


