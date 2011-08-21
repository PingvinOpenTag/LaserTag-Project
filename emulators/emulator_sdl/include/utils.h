/* emulator_sdl -- SDL emulator for LaserTag project
 *
 * Copyright (C) 2011  Pavel Andreev <pasha132@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __UTILS_H__
	#include "main.h"
	#define __UTILS_H__
	#ifdef WIN32
		void redirect_stdio(void);
	#endif

	/**
	@function putpixel
	Set the pixel at (x, y) to the given value
	@warning The surface must be locked before calling this!
	@param surface surface
	@param x x coord
	@param y y coord
	@param pixel pixel color
	*/
	 void putpixel( SDL_Surface *surface, int x, int y, Uint32 pixel );

	/**
	@function getpixel
	Return the pixel value at (x, y)
	@warning The surface must be locked before calling this!
	@param surface surface
	@param x x coord
	@param y y coord
	@return pixel color at given coords
	*/
	Uint32 getpixel( SDL_Surface *surface, int x, int y );

	int hit_head( void *arg );
	int hit_chest( void *arg );
	int hit_weapon( void *arg );

#endif
