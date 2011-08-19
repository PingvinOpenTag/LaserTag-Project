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

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity()
{
	Surf_Entity = NULL;
	X = Y = 0.0f;
	Width = Height = 0;
	AnimState = 0;
	Visible = true;
}

CEntity::~CEntity() {}

bool CEntity::OnLoad( std::string filename, int Width, int Height, int MaxFrames )
{
	if ( ( Surf_Entity = SDLSurf::OnLoad( filename.c_str() ) ) == NULL )
	{
		return false;
	}

	SDLSurf::Transparent(Surf_Entity, SDL_MapRGB( Surf_Entity->format, 0xFF, 0, 0xFF ));

	this->Width = Width;
	this->Height = Height;

	Anim_Control.MaxFrames = MaxFrames;

	return true;
}

bool CEntity::OnLoad( SDL_Surface* Surf_Src, int Width, int Height, int MaxFrames )
{
	if ( Surf_Src == NULL )
		return false;

	Surf_Entity = Surf_Src;

	SDLSurf::Transparent(Surf_Entity, SDL_MapRGB( Surf_Entity->format, 0xFF, 0, 0xFF ));

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

void CEntity::SetVisible( )
{
	Visible =!Visible;
}

void CEntity::SetVisible( bool Visible )
{
	this->Visible = Visible;
}

void CEntity::MoveTo( int X, int Y )
{
	this->X = X;
	this->Y = Y;
}

void CEntity::fMoveTo( float X, float Y )
{
	this->X = X;
	this->Y = Y;
}

void CEntity::Center( )
{
	this->CenterX();
	this->CenterY();
}

void CEntity::CenterX( )
{
	this->X = this->X - this->Width/2;
}

void CEntity::CenterY( )
{
	this->Y = this->Y - this->Height/2;
}

void CEntity::OnRender(SDL_Surface* Surf_Display)
{
	if ( Surf_Entity == NULL || Surf_Display == NULL || !Visible ) return;

	SDLSurf::OnDraw( Surf_Display, Surf_Entity, X, Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height );
}

void CEntity::OnCleanup()
{
	if ( Surf_Entity )
	{
		SDL_FreeSurface( Surf_Entity );
	}

	Surf_Entity = NULL;
}

Uint32 CEntity::OnMouseOver( int mX, int mY, bool GetColor )
{
	if ( Surf_Entity == NULL ) return 0;
	if ( ( mX < X || mY < Y ) || ( mX > X + Width || mY > Y + Height ) ) return 0;
	return GetColor?
					SDLSurf::OnMouseOver( Surf_Entity, mX - X, mY - Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height):
					1;
}

bool CEntity::LockSurface( )
{
	return SDLSurf::LockSurface( Surf_Entity );
}

bool CEntity::UnLockSurface( )
{
	return SDLSurf::UnLockSurface( Surf_Entity );
}

SDL_Surface* CEntity::GetSurface( )
{
	return Surf_Entity;
}
