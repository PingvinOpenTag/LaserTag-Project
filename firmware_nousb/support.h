/*
 * support.h  - Support maros
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
