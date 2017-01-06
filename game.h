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

#ifndef _GAME_H_
#define _GAME_H_

#include "hangman.h"

#define CTRL_KEY(c) ((c) & 0x1F)
#define ALT_KEY(c)  ((c) | 0xA0)

Game * game_new(void);
void game_free(Game *game);
void game_loop(hangman *h);

void draw_graphic(WINDOW *w, char g[][53]);

#endif  /* _GAME_H_ */
