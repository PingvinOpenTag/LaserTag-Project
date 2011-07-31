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

#ifndef __ANIMATION_H__
	#define __ANIMATION_H__
	#include "main.h"
	/**
	@class CAnimation
	Basic class to handle animation
	*/
	class CAnimation
	{
		private:
			int CurrentFrame;
			int FrameInc;
		public:
			int MaxFrames;

			CAnimation();
			void OnAnimate();
			void SetCurrentFrame(int Frame);
			int GetCurrentFrame();
	};
#endif
