#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <avr/power.h>

#include "timer.h"
#include "support.h"

int timer_on()
{

  return 0;
}

int frame_timer_load()
{   //FOR timer 1
    //power_timer1_enable();

    // 12 000 000 / 1024 / 2dc6 == 1 Hz
    TCCR2B=0x00;
    OCR2A=0x70;

    TCCR2A=0x02;
    TIMSK2=0x02;//COMPARE A
    TCCR2B=0x03;
    //TCCR0B
    // 0b??--1101
    //   ||   | 010 -- clk/8
    //   ||   \ 101 -- clk/1024
    //   ||FOC0B
    //   |FOC0A

    power_timer2_enable();

    //DDRBIT(D, 6, 1);//=0xFD;
  

  return 0;
}

int timer_load()
{
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

    DDRBIT(D, 6, 1);//=0xFD;
    //*/
    return 0;
}


int timer_off()
{

  return 0;
}
