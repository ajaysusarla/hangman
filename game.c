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

void draw_graphic(WINDOW *w, char **g)
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

        draw_graphic(h->hman, graphic_start);
        refresh();

        do {
                ch = getch();

                if (ch == KEY_ESC || ch == 'Q') {
                        printf("quitting mate!!!\n");
                        break;
                }

                h->game->guesses++;
                h->game->misses++;

                if (h->game->misses == 1)
                        draw_graphic(h->hman, graphic_stage_1);
                else if (h->game->misses == 2)
                        draw_graphic(h->hman, graphic_stage_2);
                else if (h->game->misses == 3)
                        draw_graphic(h->hman, graphic_stage_3);
                else if (h->game->misses == 4)
                        draw_graphic(h->hman, graphic_stage_4);
                else if (h->game->misses == 5)
                        draw_graphic(h->hman, graphic_stage_5);
                else if (h->game->misses == 6)
                        draw_graphic(h->hman, graphic_stage_6);
                else if (h->game->misses == 7)
                        draw_graphic(h->hman, graphic_stage_7);
                else if (h->game->misses == 8)
                        draw_graphic(h->hman, graphic_stage_8);
                else if (h->game->misses == 9) {
                        draw_graphic(h->hman, graphic_end);
                        refresh();
                        sleep(1);
                        break;
                }

                refresh();

        } while (1);

        nodelay(stdscr, FALSE);
}

