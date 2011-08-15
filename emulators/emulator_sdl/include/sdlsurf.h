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
				SDLSurf();

			public:
				static SDL_Surface* OnLoad( std::string );
				static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
				static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
				static bool Transparent( SDL_Surface* Surf_Dest, Uint32 color );
				static Uint32 OnMouseOver( SDL_Surface* Surf_Src, int mX, int mY, int X2, int Y2, int W, int H );
		};
#endif
