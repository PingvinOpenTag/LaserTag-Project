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

#ifndef __SDLFONT_H__
	#define __SDLFONT_H__
	#include "main.h"
	/**
	@class SDLFont
	Basic class to handle fonts
	*/
	class SDLFont : public SDLObject
	{
		public:
			unsigned int max_lines;

		protected:
			TTF_Font *font;
			SDL_Color fnt_color;
			std::string text;
			std::deque<SDL_Surface*> rendered;
		public:
			SDLFont();
			virtual ~SDLFont();

			virtual bool OnLoad( std::string fontname, int ptsize );

			virtual void OnLoop();
			virtual void OnRender( SDL_Surface* Surf_Display );
			virtual void OnCleanup();

			virtual SDLFont* AppendText( std::string text );
			virtual SDLFont* SetText( std::string text );
			virtual SDLFont* SetFontColor( SDL_Color color );
			virtual SDLFont* SetFontColor( Uint8 r, Uint8 g, Uint8 b );

			virtual SDLFont* Center( );
			virtual SDLFont* CenterX( );
			virtual SDLFont* CenterY( );

			virtual std::string GetText( );
	};
#endif
