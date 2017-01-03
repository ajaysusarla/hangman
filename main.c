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

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <aspell.h>

#define _ASPELL_DICT_LANG "en_US"

#include "hangman.h"
#include "graphic.h"
#include "window.h"

#define BOARD_WIDTH  60
#define BOARD_HEIGHT 30

void print_graphic(char **g)
{
        int i;

        for (i = 0; i < GRAPHIC_ROWS; i++) {
                printf("%s\n", g[i]);
        }

}


/* toggle cursor display */
static void _hide_cursor(int state)
{
        if (state == TRUE)
                curs_set(0);
        else if (state == FALSE)
                curs_set(1);
        else
                printf("interface_hide_cursor: Invalid state\n");
}

static int screen_init(void)
{
        /* ncurses initialisation */
        if (!initscr()) {
                return -1;
        }

        if (getmaxx(stdscr) < 65 || getmaxy(stdscr) < 40) {
                endwin();
                fprintf(stderr, "Screensize less than 140x40 [current:%dx%d].\n",
                        getmaxx(stdscr), getmaxy(stdscr));
                return -1;
        }

        keypad(stdscr, TRUE);  /* Enable keypad for the user's terminal */
        nodelay(stdscr, TRUE); /* non-blocking mode*/
        cbreak();              /* Read single input chars, without waiting for \n*/
        noecho();              /* Don't echo input */

        _hide_cursor(TRUE);

        return 0;
}


static void screen_fin(void)
{
        /* Delete windows */
        endwin();
}

static void termination_handler(int sig)
{
        screen_fin();
        exit(EXIT_SUCCESS);
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

        do {
                ch = getch();

                if (ch == KEY_ESC || ch == 'q' || ch == 'Q') {
                        printf("quitting mate!!!\n");
                        break;
                }
        } while (1);

        nodelay(stdscr, FALSE);
}

void draw_board(hangman *h)
{
        int xpos, ypos;

        window_clear(h);

        /* the board at the center of the screen */
        xpos = (getmaxx(stdscr) - BOARD_WIDTH) / 2;
        ypos = (getmaxy(stdscr) - BOARD_HEIGHT) / 2;

        h->board = newwin(BOARD_HEIGHT, BOARD_WIDTH, ypos, xpos);
        keypad(h->board, TRUE);

        wattrset(h->board, A_NORMAL);
        wbkgdset(h->board, A_NORMAL & A_COLOR);

        touchwin(h->board);
        wnoutrefresh(h->board);

}

int main(void)
{
        hangman h;

        signal(SIGINT, termination_handler);

        if (screen_init() != 0) {
                exit(EXIT_FAILURE);
        }

        h.title = "Hangman";
        h.game = game_new();

        draw_board(&h);

        refresh();

        game_loop(&h);

        screen_fin();

        game_free(h.game);

        exit(EXIT_SUCCESS);
}
