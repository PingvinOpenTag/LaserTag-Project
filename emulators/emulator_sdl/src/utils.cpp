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
