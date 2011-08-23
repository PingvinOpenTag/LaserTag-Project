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

#ifndef __MAIN_H__
	#define __MAIN_H__

	#include <iostream>
	#include <sstream>
	#include <string>
	#include <deque>
	#include <vector>
	#include <map>

	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>

	#ifdef WIN32
		#include <windows.h>
		#include <io.h>
	#endif

	//Resources dir
	const std::string DIR_RESOURCES = "./resources";

	//Screen attributes
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;

	//The frames per second
	const int FRAMES_PER_SECOND = 15;

	//Rotation direction
	const int ROTATE_NONE = 0;
	const int ROTATE_LEFT = 1;
	const int ROTATE_RIGHT = -1;

	//Colorkey
	const SDL_Color SDL_COLORKEY = {0xFF, 0, 0xFF};

	#include "timer.h"
	#include "utils.h"

	#include "sdlobject.h"
	#include "anim.h"
	#include "entity.h"
	//Hit zone data
	typedef struct _HitZone
	{
		std::string zone_name;
		CEntity* zone;
		Uint32 color;
		int (*func)(void* parms);
	} T_HitZone, *T_pHitZone;

	#include "sdlevent.h"
	#include "sdlsurf.h"
	#include "sdlfont.h"

	#include "sdlapp.h"

#endif
