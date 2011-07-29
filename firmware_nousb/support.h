
#define IRBYTE1    !(PINB&2)
#define DELAYBIT	 _delay_us(50)
#define MAX_DELAY  0xff

// GOOD
//*
#define T0_ON()  TCCR0B=0x0a;
#define T0_OFF() {\
  TCCR0B=0x00;    \
  BIT(D, 6, 0);   \
}
//*/
// BAD
//#define T0_ON()   DDRBIT(D, 6, 0)
//#define T0_OFF()  DDRBIT(D, 6, 1)
// BAD
//#define T0_ON()  power_timer0_enable()
//#define T0_OFF() power_timer0_disable()

#if 0 // FIXME add _AVR_ flag or anower

//#define BIT(port) \


#else //FIXME 
#define DDRBIT(port, num, s) DDR##port=((DDR##port & (~(1<<num))) | ((s?1:0)<<num));
#define BIT(port, num, s) PORT##port=((PORT##port & (~(1<<num))) | ((s?1:0)<<num));
#define SETBIT(port, num, s) port=((port & (~(1<<num))) | ((s?1:0)<<num));
#endif
