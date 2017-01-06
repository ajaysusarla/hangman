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

#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "graphic.h"

void draw_graphic(WINDOW *w, char g[][GRAPHIC_COLS])
{
        int i, j;
        int xpos, ypos;

        for (i = 0; i < GRAPHIC_ROWS; i++) {
                for (j = 0; j < GRAPHIC_COLS; j++) {
                        xpos = j + 1;
                        ypos = i + 1;
                        mvwaddch(w, ypos, xpos, g[i][j]);
                }
        }
        wnoutrefresh(w);
}

Game * game_new(void)
{
        Game *game;

        game = (Game *)malloc(sizeof(Game));
        if (game == NULL) {
                fprintf(stderr, "Memory allocation failure\n");
                return NULL;
        }

        return game;
}

void game_free(Game *game)
{
        if (game != NULL) {
                free(game);
                game = NULL;
        }
}

void game_loop(hangman *h)
{
        int ch = 0;

        nodelay(stdscr, FALSE);

        draw_graphic(h->hman, graphic[0]);
        refresh();

        do {
                ch = getch();

                switch(ch) {
                case KEY_ESC:
                case CTRL_KEY('Q'):
                        quit(h);
                        break;
                default:
                        break;
                }

                h->game->guesses++;
                h->game->misses++;

                if (h->game->misses == GRAPHIC_MAX) {
                        refresh();
                        sleep(1);
                        break;
                }

                draw_graphic(h->hman, graphic[h->game->misses]);
                refresh();

        } while (1);

        nodelay(stdscr, FALSE);
}

