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

std::vector<SDLObject*> SDLObject::ObjectList;

bool SDLApp::OnInit( )
{
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		std::cerr<<"Unable to init SDL: "<<SDL_GetError()<<std::endl;
		return false;
	}

	if ( ( Surf_Display = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF) ) == NULL )
	{
		std::cerr<<"Unable to set video mode: "<<SDL_GetError()<<std::endl;
		return false;
	}

	if( TTF_Init() < 0 )
	{
		std::cerr<<"Unable to init TTF: "<<TTF_GetError()<<std::endl;
		return false;
	}

	SDL_WM_SetCaption( "Emulator SDL", NULL );

	CEntity* tmp_entity = NULL;

	tmp_entity = new CEntity();

	if(	!tmp_entity->OnLoad("man.png", 125, 440, 8) )
		return false;
	else
		target = tmp_entity;

	tmp_entity = new CEntity();
	if(	!tmp_entity->OnLoad("zone.png", 125, 440, 8) )
		return false;
	else
		zone = tmp_entity;

	T_HitZone tmp[] = { {"Head", NULL, zone->GetSurfaceRGB( 0x00, 0xFF, 0x00 ), hit_head},
						{"Chest", NULL, zone->GetSurfaceRGB( 0xFF, 0x00, 0x00 ), hit_chest},
						{"Weapon", NULL, zone->GetSurfaceRGB( 0x00, 0x00, 0xFF ), hit_weapon} };

	zone->LockSurface( );
	for ( int i = 0; i < 3; i++ )
	{
		tmp_entity = new CEntity();
		if ( !tmp_entity->OnLoad( SDLSurf::CopySurface( zone->GetSurface(), tmp[i].color ), 125, 440, 8 ) )
			return false;
		tmp_entity->fMoveTo( SCREEN_WIDTH/2, 0 )->CenterX( )->SetVisible( false );
		tmp[i].zone = tmp_entity;
		zone_list[tmp[i].color] = tmp[i];
	}
	zone->UnLockSurface( );

	target->fMoveTo( SCREEN_WIDTH/2, 0 )->CenterX( );
	zone->fMoveTo( SCREEN_WIDTH/2, 0 )->CenterX( )->SetVisible( false );

	SDLObject::ObjectList.push_back( target );
	SDLObject::ObjectList.push_back( zone );

	for ( int i = 0; i < 3; i++ )
		SDLObject::ObjectList.push_back( tmp[i].zone );

	font = new SDLFont();
	if ( !font->OnLoad( "main.ttf", 16 ) )
		return false;

	SDLObject::ObjectList.push_back( font );

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
	{
		CurrentZone->func(NULL);
		Uint8 r, g, b;
		SDL_GetRGB(CurrentZone->color, zone->GetSurface()->format, &r, &g, &b);
		SDL_Color color = { r, g, b};

		std::ostringstream os;
		os << SDL_GetTicks()/1000 << " Target: " << CurrentZone->zone_name << std::endl;

		font->SetFontColor( color )->AppendText( os.str( ) );
	}
}

void SDLApp::OnMouseMove( int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle )
{
	if ( CurrentZone )
	{
		CurrentZone->zone->SetVisible( false );
		CurrentZone = NULL;
	}
	if ( zone->LockSurface( ) )
	{
		Uint32 color = zone->OnMouseOver( mX, mY, true );
		if ( zone_list.count(color) )
		{
			CurrentZone = &zone_list[color];
			CurrentZone->zone->SetVisible( true );
		}
	}

	zone->UnLockSurface( );
}

void SDLApp::OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if ( CurrentZone )
	{
		CurrentZone->zone->SetVisible( false );
		CurrentZone = NULL;
	}
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

		default:
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

		default:
			break;
	}
}

void SDLApp::OnLoop( )
{
	for ( unsigned int i = 0; i < SDLObject::ObjectList.size(); i++ )
	{
		if ( !SDLObject::ObjectList[i] ) continue;
			switch ( r_direction )
			{
				case ROTATE_LEFT:
					SDLObject::ObjectList[i]->NextFrame( );
				break;
				case ROTATE_RIGHT:
					SDLObject::ObjectList[i]->PrevFrame( );
				break;
			}
	}
}

void SDLApp::OnRender()
{
	SDL_FillRect(Surf_Display, NULL, 0x000000);
	for( unsigned int i = 0;i < SDLObject::ObjectList.size();i++ )
	{
		if( !SDLObject::ObjectList[i] ) continue;
		SDLObject::ObjectList[i]->OnRender( Surf_Display );
	}
    SDL_Flip(Surf_Display);
}

void SDLApp::OnCleanup()
{
	for( unsigned int i = 0; i < SDLObject::ObjectList.size(); i++ )
	{
		if( !SDLObject::ObjectList[i] )
			continue;

		SDLObject::ObjectList[i]->OnCleanup();
		delete SDLObject::ObjectList[i];
	}
	SDLObject::ObjectList.clear();

	SDL_FreeSurface(Surf_Display);
	TTF_Quit();
	SDL_Quit();
}

SDLApp::SDLApp()
{
	Surf_Display = Surf_Image = NULL;
	zone = target = NULL;
	CurrentZone = NULL;
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
