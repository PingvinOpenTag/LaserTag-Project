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

#ifndef __TIMER_H__
	#define __TIMER_H__
	#include "main.h"
	/**
	@class Timer
	Timer class to sync animation
	*/
	class Timer
	{
		private:
			///The clock time when the timer started
			int startTicks;

			///The ticks stored when the timer was paused
			int pausedTicks;

			/// @name The timer status
			/// @{
			bool paused;
			bool started;
			/// @}

		public:
			///Initializes variables
			Timer();

			/// @name The various clock actions
			/// @{

			/// Start timer
			void start();
			/// Stop timer
			void stop();
			/// Pause timer
			void pause();
			/// Unpause timer
			void unpause();

			/// @}

			///Gets the timer's time
			int get_ticks();

			/// @name Checks the status of the timer
			/// @{
			bool is_started();
			bool is_paused();
			/// @}
	};
#endif
