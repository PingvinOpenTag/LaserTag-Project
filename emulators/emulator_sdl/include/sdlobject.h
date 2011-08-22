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

#ifndef __SDLOBJECT_H__
	#define __SDLOBJECT_H__
	#include "main.h"
	/**
	@class SDLObject
	Entity class
	*/

	class SDLObject
	{
		public:
			static std::vector<SDLObject*> ObjectList;

		protected:
			bool Visible;
			SDL_Surface* Surf_Obj;

		public:
			float X;
			float Y;

			SDLObject( );

			virtual ~SDLObject( );

			virtual void OnLoop( ) = 0;
			virtual void OnRender( SDL_Surface* Surf_Display ) = 0;
			virtual void OnCleanup( );

			virtual void NextFrame();
			virtual void PrevFrame();
			virtual void MoveFrame( int Frame );

			virtual SDLObject* SetVisible( );
			virtual SDLObject* SetVisible( bool Visible );
			virtual SDLObject* MoveTo( int X, int Y );
			virtual SDLObject* fMoveTo( float X, float Y );
			virtual SDLObject* Center( ) = 0;
			virtual SDLObject* CenterX( ) = 0;
			virtual SDLObject* CenterY( ) = 0;

			virtual SDL_Surface* GetSurface( );
			virtual Uint32 GetSurfaceRGB( const SDL_Color& color );
			virtual Uint32 GetSurfaceRGB( Uint8 r, Uint8 g, Uint8 b );
			virtual Uint32 GetSurfaceRGB( SDL_Surface* Surf_Src, const SDL_Color& color );
			virtual Uint32 GetSurfaceRGB( SDL_Surface* Surf_Src, Uint8 r, Uint8 g, Uint8 b );

			virtual bool LockSurface( );
			virtual bool UnLockSurface( );

			virtual Uint32 OnMouseOver( int mX, int mY, bool GetColor = false ) {return 0;};
	};
#endif
