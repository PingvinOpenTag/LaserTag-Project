/* Name: main.c
 * Project: IrReceiver
 * Author: Leonid Myravjev
 * Creation Date: 2011-05-08
 */

#define F_CPU 12000000UL 

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <avr/power.h>

#include "../logick/ircoder.h"

#define DDRBIT(port, num, s) DDR##port=((DDR##port & (~(1<<num))) | ((s?1:0)<<num));
#define BIT(port, num, s) PORT##port=((PORT##port & (~(1<<num))) | ((s?1:0)<<num));
#define SETBIT(port, num, s) port=((port & (~(1<<num))) | ((s?1:0)<<num));

int  write=0;
unsigned char IRbytes[200];

uint32_t time=0;
#define IRBYTE1    !(PINB&2)
#define DELAYBIT	 _delay_us(50)
#define MAX_DELAY  0xff

// GOOD
/*
#define T0_ON()  TCCR0B=0x0a;
#define T0_OFF() TCCR0B=0x00;
*/
// BAD
//#define T0_ON()   DDRBIT(D, 6, 0)
//#define T0_OFF()  DDRBIT(D, 6, 1)
// BAD
#define T0_ON()  power_timer0_enable()
#define T0_OFF() power_timer0_disable()

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
    
    DDRB=0xFD;
		PORTB=0xFF;
    DDRC=0xFF;
    PORTC=0;
    DDRBIT(D, 6, 1);//=0xFD;
    DDRBIT(D, 5, 1);//=0xFD;

    //// 8 bit timer programming....
    // Diver 8 (20000 kHZ / 8 => 2500 kHz)
    //  needed 36 kHz.
    // 2500 / 36.0 => 69.444 (0x45)
    //
    // TCCR0A
    //  7 - COMOA1
    //  6 - COMOA0
    //  5 - COMOB1
    //  4 - COMOB0
    //  3,2
    //  1 - WGMO1
    //  0 - WGMO0
    // 0b000100
    
    // for TCCR0A --
    // 0b01000011 -- TIMER 0 (OC0A in toggle mode), TIMER 1 is off 
    //         ||- WGM00 == 1 -- it needed ;-)
    //         |- WGM01 == 0 TOP <-> BOTTOM
    //                     1 BOTTOM <-> TOP
    // for
    //         | WGM02 == 1 -- its toggle OC0A it comapre match
    //
    //
    // // DDR must be set (its set)
    //*
    TCCR0A=0x43;
    //TCCR0B
    // 0b??--1101
    //   ||   | 010 -- clk/8
    //   ||   \ 101 -- clk/1024
    //   ||FOC0B
    //   |FOC0A
    TCCR0B=0x0a;//0b00001010
    TIMSK0=0x00;//no needed interrupt
    OCR0A=20;//0x29;
    power_timer0_enable();
    //*/
   
    sei();
    BIT(B, 2, 1);
   uint8_t msg[8];
   uint32_t st;
   uint8_t  *code   = (uint8_t*)  &st;
   st=0xbeef;
   code2ir_shot(code, msg, 16);

   uint8_t a=0;
   uint8_t c=7;
    for(;;){    /* main event loop */
			time++;

      if((msg[a]>>c)&1){
        T0_ON();
      }else{
        T0_OFF();
      }
      _delay_us(600);
      if(c--==0){
        if(++a>=7){
          a=0;
          T0_OFF();
          power_timer0_disable();
          _delay_ms(100);
          power_timer0_enable();
        }
        c=7;
      }//*/
    }
    return 0;
}


