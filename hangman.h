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

#ifndef _HANGMAN_H_
#define _HANGMAN_H_

#include <ncurses.h>

typedef struct _hangman hangman;
typedef struct _game Game;

struct _game {
        const char *word;
        unsigned int guesses;
        unsigned int misses;
};

struct _hangman {
        const char *title;
        WINDOW *hman;
        WINDOW *word;
        WINDOW *miss;
        WINDOW *guess;
        WINDOW *msg;

        Game *game;
};

/* Keys */
#define KEY_ESC 27

extern void quit(hangman *h);

#endif  /* _HANGMAN_H_ */
