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

#ifndef __SDLEVENT_H__
	#define __SDLEVENT_H__
	#include "main.h"
	/**
	@class SDLEvent
	Main class to handle SDL events
	*/

	class SDLEvent
	{
		public:
			SDLEvent();
			virtual ~SDLEvent();

			virtual void OnEvent( SDL_Event* Event );
			virtual void OnInputFocus();
			virtual void OnInputBlur();
			virtual void OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode );
			virtual void OnKeyUp( SDLKey sym, SDLMod mod, Uint16 unicode );
			virtual void OnMouseFocus();
			virtual void OnMouseBlur();
			virtual void OnMouseMove( int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle );
			virtual void OnMouseWheel( bool Up, bool Down );  //Not implemented
			virtual void OnLButtonDown( int mX, int mY );
			virtual void OnLButtonUp( int mX, int mY );
			virtual void OnRButtonDown( int mX, int mY );
			virtual void OnRButtonUp( int mX, int mY );
			virtual void OnMButtonDown( int mX, int mY );
			virtual void OnMButtonUp( int mX, int mY );
			virtual void OnJoyAxis( Uint8 which, Uint8 axis, Sint16 value );
			virtual void OnJoyButtonDown( Uint8 which, Uint8 button );
			virtual void OnJoyButtonUp( Uint8 which, Uint8 button );
			virtual void OnJoyHat( Uint8 which, Uint8 hat, Uint8 value );
			virtual void OnJoyBall( Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel );
			virtual void OnMinimize();
			virtual void OnRestore();
			virtual void OnResize( int w,int h );
			virtual void OnExpose();
			virtual void OnExit();
			virtual void OnUser( Uint8 type, int code, void* data1, void* data2 );
	};

#endif
