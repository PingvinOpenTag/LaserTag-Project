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

/* Redirect I/O on Windows to a file.  We would not need to do this in a console app. */
#ifdef WIN32
	void redirect_stdio(void)
	{
		/* We must freopen stderr to get it to have a valid fd before we can
		dup it to stdout.  This creates a file on disk, which we then delete. */
		freopen("stdout.txt", "w", stdout);
		freopen("stderr.txt", "w", stderr);
		if (_dup2(_fileno(stdout), _fileno(stderr)) != 0)
			fprintf(stdout, "_dup2 failed!\n");
		DeleteFile("stderr.txt");
	}
#endif

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	// Here p is the address to the pixel we want to set
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp)
	{
		case 1:/* Assuming 8-bpp */
			*p = pixel;
			break;
		case 2:/* Probably 15-bpp or 16-bpp */
			*(Uint16 *)p = pixel;
			break;
		case 3:/* Slow 24-bpp mode, usually not used */
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:/* Probably 32-bpp */
			*(Uint32 *)p = pixel;
		break;
	}
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
		return 0;       /* shouldn't happen, but avoids warnings */
	} // switch
}

int hit_head( void *arg )
{
	printf("Head\n");
	return 0;
}

int hit_chest( void *arg )
{
	printf("Chest\n");
	return 0;
}
