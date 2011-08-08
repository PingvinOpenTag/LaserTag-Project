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

	#include <string>
	#include <vector>
	#include <SDL.h>
	#include <SDL_image.h>
	
	#ifdef WIN32
		#include <windows.h>
		#include <io.h>
	#endif
	
	#include "sdlapp.h"
	#include "sdlevent.h"
	#include "sdlsurf.h"
	#include "anim.h"
	#include "timer.h"
	#include "entity.h"
	#include "utils.h"
#endif
