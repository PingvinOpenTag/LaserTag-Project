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

SDLFont::SDLFont()
{
	max_lines = 3;
	font = NULL;
	Surf_Obj = NULL;
	X = Y = 0.0f;
	Visible = true;
	fnt_color.r = 0;
	fnt_color.g = 0;
	fnt_color.b = 0;
	text.clear();
}

SDLFont::~SDLFont()
{
	TTF_CloseFont( font );
}

bool SDLFont::OnLoad( std::string fontname, int ptsize )
{
	std::string path = DIR_RESOURCES + "/fonts/" + fontname;
	font = TTF_OpenFont( path.c_str(), ptsize );
	if( !font )
	{
		std::cerr<<"TTF_OpenFont: "<<TTF_GetError()<<std::endl;
		return false;
	}
	return true;
}

void SDLFont::OnLoop() {}

void SDLFont::OnRender( SDL_Surface* Surf_Display )
{
	if ( Surf_Display == NULL || font == NULL || !Visible ) return;

	if ( Surf_Obj == NULL )
	{
		int sum_h = 0, max_w = 0;
		for( unsigned int i = 0; i < rendered.size(); i++ )
		{
			sum_h += rendered[i]->h;
			max_w = rendered[i]->w>max_w?rendered[i]->w:max_w;
		}

		if ( !( Surf_Obj = SDLSurf::CreateSurface( Surf_Display->format, Surf_Display->flags, max_w, sum_h ) ) )
			return;

		SDLSurf::Transparent( Surf_Obj, GetSurfaceRGB( SDL_COLORKEY ) );

		float sX = 0, sY = 0;
		for( unsigned int i = 0; i < rendered.size(); i++ )
		{
			SDLSurf::OnDraw( Surf_Obj, rendered[i], sX, sY );
			sY += rendered[i]->h;
		}
	}
	SDLSurf::OnDraw( Surf_Display, Surf_Obj, X, Y );
}

void SDLFont::OnCleanup()
{
	for( unsigned int i = 0; i < rendered.size(); i++ )
		SDL_FreeSurface( rendered[i] );
	rendered.clear( );

	SDLObject::OnCleanup( );
}

SDLFont* SDLFont::AppendText( std::string text )
{
	SDLObject::OnCleanup( );

	if ( font == NULL )
		return this;

	std::string out = "";
	std::vector<std::string> text_lines;
	std::string::iterator it;
	for ( it = text.begin(); it < text.end(); it++)
	{
		if ( *it == '\n' )
		{
			text_lines.push_back( out );
			out = "";
			continue;
		}
		out += *it;
	}
	if ( !out.empty() )
		text_lines.push_back( out );

	for( unsigned int i = 0; i < text_lines.size(); i++ )
	{
		SDL_Surface* render;
		render = TTF_RenderText_Blended( font, text_lines[i].c_str(), fnt_color );

		if ( render == NULL )
		{
			std::cerr<<"TTF_RenderText_Blended failed: "<<TTF_GetError()<<std::endl;
			return this;
		}

		SDLSurf::Transparent( render, GetSurfaceRGB( render, SDL_COLORKEY ) );

		rendered.push_back( render );
		if ( rendered.size( ) > max_lines )
		{
			SDL_FreeSurface( rendered.front( ) );
			rendered.pop_front( );
		}
	}

	return this;
}

SDLFont* SDLFont::SetText( std::string text )
{
	this->text.clear();
	AppendText(text);
	return this;
}

SDLFont* SDLFont::SetFontColor( SDL_Color color )
{
	fnt_color.r = color.r;
	fnt_color.g = color.g;
	fnt_color.b = color.b;
	return this;
}

SDLFont* SDLFont::SetFontColor( Uint8 r, Uint8 g, Uint8 b )
{
	fnt_color.r = r;
	fnt_color.g = g;
	fnt_color.b = b;
	return this;
}

std::string SDLFont::GetText( )
{
	return text;
}

SDLFont* SDLFont::Center( ) {return this;}
SDLFont* SDLFont::CenterX( ) {return this;}
SDLFont* SDLFont::CenterY( ) {return this;}
