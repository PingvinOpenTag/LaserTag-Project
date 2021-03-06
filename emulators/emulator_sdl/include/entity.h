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

#ifndef __ENTITY_H__
	#define __ENTITY_H__
	#include "main.h"
	/**
	@class CEntity
	Entity class
	*/

	class CEntity : public SDLObject
	{
		protected:
			CAnimation Anim_Control;

		public:
			int Width;
			int Height;

			int AnimState;

			CEntity();
			virtual ~CEntity();

			virtual bool OnLoad( std::string filename, int Width, int Height, int MaxFrames );
			virtual bool OnLoad( SDL_Surface* Surf_Src, int Width, int Height, int MaxFrames );

			virtual void OnLoop();
			virtual void OnRender( SDL_Surface* Surf_Display );

			virtual void NextFrame();
			virtual void PrevFrame();
			virtual void MoveFrame( int Frame );

			virtual CEntity* Center( );
			virtual CEntity* CenterX( );
			virtual CEntity* CenterY( );

			virtual Uint32 OnMouseOver( int mX, int mY, bool GetColor = false );
	};
#endif
