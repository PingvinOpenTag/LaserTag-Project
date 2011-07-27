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

#include "usbdrv.h"
#include "oddebug.h"

#include "usb_commands.h"

#define DDRBIT(port, num, s) DDR##port=((DDR##port & (~(1<<num))) | ((s?1:0)<<num));
#define BIT(port, num, s) PORT##port=((PORT##port & (~(1<<num))) | ((s?1:0)<<num));
#define SETBIT(port, num, s) port=((port & (~(1<<num))) | ((s?1:0)<<num));

int  write=0;
unsigned char IRbytes[200];

uint32_t time=0;
USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
	usbRequest_t    *rq = (void *)data;
	static uchar    replyBuf[10];

	usbMsgPtr = replyBuf;
	switch(rq->bRequest){
		//case 0:
		case PKG_GETTIME:
			{
				*((uint32_t*) &replyBuf)=time;
				return sizeof(uint32_t);
			}
		case PKG_IRDEB:
		{
			usbMsgPtr = IRbytes;
			int res=write; // + ((write%8) != 0);
			write=0;
			return res;
		}
		case PKG_SETPORT:
		{
				//*((uint32_t*) &replyBuf)=time;
			uint8_t num,val;
			num = rq->wValue.bytes[0];
			val = rq->wIndex.bytes[0];
			if(num==100)
			{
				//LedON=val;
				replyBuf[0]=val; 
				return 1;
			}
			replyBuf[0]=val+10; 
			return 1;
		}
	}
  return 0;
}

#define IRBYTE1    !(PINB&2)
#define DELAYBIT	 _delay_us(50)
#define MAX_DELAY  0xff

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
    
    DDRB=0xFD;
		PORTB=0xFF;
    DDRC=0xFF;
    PORTC=0;
    DDRBIT(D, 6, 1);//=0xFD;
   
   // USB INIT /////////
    cli();
    usbInit();
    usbDeviceDisconnect();
//    while(--i){
        _delay_ms(1000);
//    }
    usbDeviceConnect();
    sei();
    BIT(B, 2, 1);
    _delay_ms(3000);
   //// END USB INIT /// 
    for(;;){    /* main event loop */
			time++;
		 // usbPoll();

      _delay_us(127);
      BIT(B, 2, time%2);

      //ir_parse();
    }
    return 0;
}

