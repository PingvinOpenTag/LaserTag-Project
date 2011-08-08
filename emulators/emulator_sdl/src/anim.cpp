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

CAnimation::CAnimation()
{
	CurrentFrame = 0;
	MaxFrames = 0;
	FrameInc = 1;
}

void CAnimation::OnAnimate()
{
	CurrentFrame += FrameInc;

	if ( CurrentFrame >= MaxFrames - 1 )
	{
		CurrentFrame = 0;
	}
}

void CAnimation::SetCurrentFrame( int Frame )
{
	if( Frame < 0 )
		Frame = MaxFrames - 1;
	if ( Frame >= MaxFrames ) 
		Frame = 0 ;

	CurrentFrame = Frame;
}

int CAnimation::GetCurrentFrame()
{
	return CurrentFrame;
}
