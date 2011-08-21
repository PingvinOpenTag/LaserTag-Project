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

#ifndef __SDLSURF_H__
	#define __SDLSURF_H__
		#include "main.h"
		/**
		@class SDLSurf
		Class for work with surfaces
		*/
		class SDLSurf
		{
			public:
				///Do nothing
				SDLSurf();

			public:
				/**
				Load surface from file
				@param filename file name to load
				@return pointer to SDL_Surface structure
				*/
				static SDL_Surface* OnLoad( std::string filename );

				/**
				Draw surface
				@param Surf_Dest* destination surface
				@param Surf_Src* source surface
				@param X X coord
				@param Y Y coord
				@return true if everything good, false otherwise
				*/
				static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

				/**
				Draw part of surface
				@param Surf_Dest* destination surface
				@param Surf_Src* source surface
				@param X X coord
				@param Y Y coord
				@param Rect_Src part of surface to draw
				@return true if everything good, false otherwise
				*/
				static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, SDL_Rect& Rect_Src);

				/**
				Set transparent color on surface
				@param Surf_Dest* source surface
				@param color transparent color
				@return true if everything good, false otherwise
				*/
				static bool Transparent( SDL_Surface* Surf_Dest, Uint32 color );

				/**
				Lock surface for low-level pixel manipulations
				@param Surf_Src* surface to lock
				@return true if everything good, false otherwise
				*/
				static bool LockSurface( SDL_Surface* Surf_Src );

				/**
				UnLock surface
				@param Surf_Src* surface to unlock
				@return true if everything good, false otherwise
				*/
				static bool UnLockSurface( SDL_Surface* Surf_Src );

				/**
				Copy surface by color mask
				@param Surf_Src* surface to copy
				@param color_mask color to copy
				@return pointer to new SDL_Surface
				*/
				static SDL_Surface* CopySurface( SDL_Surface* Surf_Src, Uint32 color_mask);

				/**
				Handle MouseOver events
				@param Surf_Src* to check
				@param mX X coord on surface
				@param mY Y coord on surface
				@return color under coords
				*/
				static Uint32 OnMouseOver( SDL_Surface* Surf_Src, int mX, int mY);
		};
#endif
