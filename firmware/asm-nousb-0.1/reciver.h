/*
 * reciver.h  - Reciver for IR sensors
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

int recv_iteration();
int recv_initialize();

// Max of length message (bytes)
#define MSGMAXLEN 2
// Max of IR sensors count
#define SENSORS   8

extern uint8_t recv[MSGMAXLEN*SENSORS]; // 2 -- bytes on messag; 8 -- IR sensors
extern uint8_t recv_mask[MSGMAXLEN];
