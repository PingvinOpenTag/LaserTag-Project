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

#ifndef __SDLAPP_H__
	#define __SDLAPP_H__
	#include "main.h"
	#include "sdlevent.h"
	#include "entity.h"
	#include "utils.h"
	/**
	@class SDLApp
	Main class to work with SDL
	*/
	class SDLApp: public SDLEvent
	{
		private:
			///App state
			bool running;
			///Display surface
			SDL_Surface* Surf_Display;
			///Image surface
			SDL_Surface* Surf_Image;
			///Target sprite
			CEntity target;
			///Zones sprite
			CEntity zone;
			///Rotation direction
			int r_direction;
			///Zones list
			std::map<Uint32, T_HitZone> zone_list;
			///Current zone
			T_pHitZone CurrentZone;
		public:
			SDLApp( );
			int OnExecute( );

			bool OnInit( );
			void OnEvent( SDL_Event* Event );
			void OnExit( );

			void OnKeyUp( SDLKey sym, SDLMod mod, Uint16 unicode);
			void OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode);

			void OnMouseMove( int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle );
			void OnLButtonUp( int mX, int mY );

			void OnLoop( );
			void OnRender( );
			void OnCleanup( );
	};
#endif
