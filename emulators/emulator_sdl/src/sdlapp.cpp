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

bool SDLApp::OnInit( )
{
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		return false;
	}

	if ( ( Surf_Display = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF) ) == NULL )
	{
		return false;
	}

	if(	!target.OnLoad("./resources/man.png", 125, 440, 8) )
	{
		return false;
	}
	if(	!zone.OnLoad("./resources/zone.png", 125, 440, 8) )
	{
		return false;
	}
	T_HitZone tmp[] = { {hit_head, "Head"}, {hit_chest, "Chest"} };
	zone_list[0xFF00] = tmp[0];
	zone_list[0xFF0000] = tmp[1];
	CurrentZone = NULL;

	target.X = SCREEN_WIDTH/2 - 62.5f;
	zone.X = SCREEN_WIDTH/2 - 62.5f;
	zone.SetVisible(false);

	CEntity::EntityList.push_back(&target);
	CEntity::EntityList.push_back(&zone);

    return true;
}

void SDLApp::OnEvent(SDL_Event* Event)
{
	SDLEvent::OnEvent(Event);
}

void SDLApp::OnExit()
{
	running = false;
}

void SDLApp::OnLButtonUp( int mX, int mY )
{
	if ( CurrentZone )
		CurrentZone->func(NULL);
}

void SDLApp::OnMouseMove( int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle )
{
	Uint32 color = zone.OnMouseOver( mX, mY );
	CurrentZone = NULL;
	if ( zone_list.count(color) )
		CurrentZone = &zone_list[color];
}

void SDLApp::OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode)
{
	switch (sym)
	{
		case SDLK_q:
			OnExit( );
		break;

		case SDLK_a:
			r_direction = ROTATE_RIGHT;
		break;

		case SDLK_d:
			r_direction = ROTATE_LEFT;
		break;
	}
}

void SDLApp::OnKeyUp( SDLKey sym, SDLMod mod, Uint16 unicode)
{
	switch (sym)
	{
		case SDLK_q:
			OnExit( );
		break;

		case SDLK_a:
		case SDLK_d:
			r_direction = ROTATE_NONE;
		break;
	}
}

void SDLApp::OnLoop( )
{
	for ( int i = 0;i < CEntity::EntityList.size();i++ )
	{
		if ( !CEntity::EntityList[i] ) continue;
			switch ( r_direction )
			{
				case ROTATE_LEFT:
					CEntity::EntityList[i]->NextFrame( );
				break;
				case ROTATE_RIGHT:
					CEntity::EntityList[i]->PrevFrame( );
				break;
			}
	}
}

void SDLApp::OnRender()
{
	SDL_FillRect(Surf_Display, NULL, 0x000000);
	for( int i = 0;i < CEntity::EntityList.size();i++ )
	{
		if( !CEntity::EntityList[i] ) continue;
		CEntity::EntityList[i]->OnRender( Surf_Display );
	}
    SDL_Flip(Surf_Display);
}

void SDLApp::OnCleanup()
{
	for( int i = 0;i < CEntity::EntityList.size();i++ )
	{
		if( !CEntity::EntityList[i] ) continue;
		CEntity::EntityList[i]->OnCleanup();
	}
	CEntity::EntityList.clear();

	SDL_FreeSurface(Surf_Display);
	SDL_Quit();
}

SDLApp::SDLApp()
{
	Surf_Display = NULL;
	Surf_Image = NULL;
	running = true;
}

int SDLApp::OnExecute()
{
	if( !OnInit() )
		return -1;

	SDL_Event Event;
	Timer fps;
	int cap = 1;

	while( running )
	{
		fps.start();

		while( SDL_PollEvent( &Event ) )
		{
			OnEvent(&Event);
		}
		OnLoop();
		OnRender();
		//If we want to cap the frame rate
		if ( ( cap == 1 ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
		{
			//Sleep the remaining frame time
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}

	OnCleanup();

	return 0;
}
