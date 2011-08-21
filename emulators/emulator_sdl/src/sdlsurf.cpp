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

SDLSurf::SDLSurf() {}

SDL_Surface* SDLSurf::OnLoad( std::string filename )
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	//Load the image
	loadedImage = IMG_Load( filename.c_str() );
	//If the image loaded
	if( loadedImage != NULL )
		{
			//Create an optimized image
			optimizedImage = SDL_DisplayFormat( loadedImage );
			//Free the old image
			SDL_FreeSurface( loadedImage );
		}
	else
		std::cerr<<"IMG_Load: "<<IMG_GetError( )<<std::endl;
	//Return the optimized image
	return optimizedImage;
}

bool SDLSurf::OnDraw( SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y )
{
	if( Surf_Dest == NULL || Surf_Src == NULL )
	{
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);
	return true;
}

bool SDLSurf::OnDraw( SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, SDL_Rect& Rect_Src )
{
	if( Surf_Dest == NULL || Surf_Src == NULL )
	{
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = Rect_Src.x;
	SrcR.y = Rect_Src.y;
	SrcR.w = Rect_Src.w;
	SrcR.h = Rect_Src.h;

	SDL_BlitSurface( Surf_Src, &SrcR, Surf_Dest, &DestR );

	return true;
}

bool SDLSurf::Transparent( SDL_Surface* Surf_Dest, Uint32 color)
{
	if( Surf_Dest == NULL )
	{
		return false;
	}

	SDL_SetColorKey( Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, color);

	return true;
}

SDL_Surface* SDLSurf::CopySurface( SDL_Surface* Surf_Src, Uint32 color)
{
	if( Surf_Src  == NULL )
		return false;

	Uint32 Amask = 0;
	SDL_Surface *dst = NULL;

	if( Surf_Src->flags & SDL_SRCCOLORKEY )
		Amask = 0;
	else
		Amask = Surf_Src->format->Amask;

	dst = SDL_CreateRGBSurface( SDL_SWSURFACE,
									Surf_Src->w,
									Surf_Src->h,
									Surf_Src->format->BitsPerPixel,
									Surf_Src->format->Rmask,
									Surf_Src->format->Gmask,
									Surf_Src->format->Bmask,
									Amask );
	if ( !dst )
	{
		std::cerr<<"CreateRGBSurface failed: "<<SDL_GetError()<<std::endl;
		return dst;
	}
	//Go through columns
	for( int x = 0; x < dst->w; x++ )
	{
		//Go through rows
		for( int y = 0; y < dst->h; y++ )
		{
			//Get pixel
			Uint32 pixel = getpixel( Surf_Src, x, y );;
			//Copy pixel
			if ( color != pixel)
				pixel = SDL_MapRGB( Surf_Src->format, 0xFF, 0, 0xFF );

			putpixel( dst, x, y, pixel );
		}
	}
	return dst;
}

bool SDLSurf::LockSurface( SDL_Surface* Surf_Src )
{
	if ( SDL_MUSTLOCK(Surf_Src) )
	{
		if ( SDL_LockSurface(Surf_Src) < 0 )
		{
			return false;
		}
	}
	return true;
}

bool SDLSurf::UnLockSurface( SDL_Surface* Surf_Src )
{
	if ( SDL_MUSTLOCK(Surf_Src) )
	{
		SDL_UnlockSurface(Surf_Src);
	}
	return true;
}

Uint32 SDLSurf::OnMouseOver( SDL_Surface* Surf_Src, int mX, int mY)
{
	Uint32 color;
	color = getpixel( Surf_Src, mX, mY );
	return color;
}
