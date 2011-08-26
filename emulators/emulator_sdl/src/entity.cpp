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

CEntity::CEntity()
{
	X = Y = 0.0f;
	Width = Height = 0;
	AnimState = 0;
	Visible = true;
}

CEntity::~CEntity() {}

bool CEntity::OnLoad( std::string filename, int Width, int Height, int MaxFrames )
{
	if ( ( Surf_Obj = SDLSurf::OnLoad( filename.c_str() ) ) == NULL )
	{
		return false;
	}

	Uint32 colorkey = GetSurfaceRGB( SDL_COLORKEY );
	SDLSurf::Transparent(Surf_Obj, colorkey);

	this->Width = Width;
	this->Height = Height;

	Anim_Control.MaxFrames = MaxFrames;

	return true;
}

bool CEntity::OnLoad( SDL_Surface* Surf_Src, int Width, int Height, int MaxFrames )
{
	if ( Surf_Src == NULL )
		return false;

	Surf_Obj = Surf_Src;

	Uint32 colorkey = GetSurfaceRGB( SDL_COLORKEY );
	SDLSurf::Transparent(Surf_Obj, colorkey);

	this->Width = Width;
	this->Height = Height;

	Anim_Control.MaxFrames = MaxFrames;

	return true;
}

void CEntity::OnLoop()
{
	Anim_Control.OnAnimate();
}

void CEntity::MoveFrame(int Frame)
{
	Anim_Control.SetCurrentFrame( Anim_Control.GetCurrentFrame( ) + Frame );
}

void CEntity::NextFrame()
{
	this->MoveFrame( 1 );
}

void CEntity::PrevFrame()
{
	this->MoveFrame( -1 );
}

CEntity* CEntity::Center( )
{
	this->CenterX();
	this->CenterY();
	return this;
}

CEntity* CEntity::CenterX( )
{
	this->X = this->X - this->Width/2;
	return this;
}

CEntity* CEntity::CenterY( )
{
	this->Y = this->Y - this->Height/2;
	return this;
}

void CEntity::OnRender(SDL_Surface* Surf_Display)
{
	if ( Surf_Obj == NULL || Surf_Display == NULL || !Visible ) return;

	SDL_Rect src;
	src.x = AnimState * Width;
	src.y = Anim_Control.GetCurrentFrame() * Height;
	src.w = Width;
	src.h = Height;

	SDLSurf::OnDraw( Surf_Display, Surf_Obj, X, Y, src );
}

Uint32 CEntity::OnMouseOver( int mX, int mY, bool GetColor )
{
	if ( Surf_Obj == NULL ) return 0;
	if ( ( mX < X || mY < Y ) || ( mX > X + Width || mY > Y + Height ) ) return 0;
	return GetColor?SDLSurf::OnMouseOver( Surf_Obj, mX - X + AnimState * Width, mY - Y + Anim_Control.GetCurrentFrame() * Height):
					1;
}
