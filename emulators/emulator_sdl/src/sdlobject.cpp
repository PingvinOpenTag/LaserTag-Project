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

#include "main.h"

SDLObject::SDLObject( )
{
	Surf_Obj = NULL;
	X = Y = 0.0f;
	Visible = true;
}

SDLObject::~SDLObject( ) {};

void SDLObject::OnCleanup( )
{
	if ( Surf_Obj )
	{
		SDL_FreeSurface( Surf_Obj );
	}

	Surf_Obj = NULL;
}

void SDLObject::NextFrame() {};
void SDLObject::PrevFrame() {};
void SDLObject::MoveFrame( int Frame ) {};

SDLObject* SDLObject::SetVisible( )
{
	Visible = !Visible;
	return this;
}

SDLObject* SDLObject::SetVisible( bool Visible )
{
	this->Visible = Visible;
	return this;
}

SDLObject* SDLObject::MoveTo( int X, int Y )
{
	this->X = X;
	this->Y = Y;
	return this;
}

SDLObject* SDLObject::fMoveTo( float X, float Y )
{
	this->X = X;
	this->Y = Y;
	return this;
}

SDL_Surface* SDLObject::GetSurface( )
{
	return Surf_Obj;
}

Uint32 SDLObject::GetSurfaceRGB( SDL_Surface* Surf_Src, const SDL_Color& color )
{
	return SDL_MapRGB( Surf_Src->format, color.r, color.g, color.b );
}

Uint32 SDLObject::GetSurfaceRGB( SDL_Surface* Surf_Src, Uint8 r, Uint8 g, Uint8 b )
{
	return SDL_MapRGB( Surf_Src->format, r, g, b );
}

Uint32 SDLObject::GetSurfaceRGB( const SDL_Color& color )
{
	return GetSurfaceRGB( Surf_Obj, color );
}

Uint32 SDLObject::GetSurfaceRGB( Uint8 r, Uint8 g, Uint8 b )
{
	return GetSurfaceRGB( Surf_Obj, r, g, b );
}

bool SDLObject::LockSurface( )
{
	return SDLSurf::LockSurface( Surf_Obj );
}

bool SDLObject::UnLockSurface( )
{
	return SDLSurf::UnLockSurface( Surf_Obj );
}
