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

bool SDLSurf::OnDraw( SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H )
{
	if( Surf_Dest == NULL || Surf_Src == NULL )
	{
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

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
