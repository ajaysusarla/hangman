/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _WINDOW_H
#define _WINDOW_H

#include <ncurses.h>

#include "hangman.h"

void window_draw_box(WINDOW *win,
                     int y, int x,
                     int height, int width,
                     chtype box, chtype border);

void window_draw_edge(WINDOW *win,
                      int y, int x,
                      int height, int width,
                      chtype box, chtype border);

void window_clear(hangman *h);

#endif /* _WINDOW_H */
