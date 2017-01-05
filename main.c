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

#define WORDS "/usr/share/dict/words"

#include "hangman.h"
#include "window.h"
#include "game.h"

#define BOARD_WIDTH  60
#define BOARD_HEIGHT 37
#define MSG_BOX_WIDTH 60
#define MSG_BOX_HEIGHT 7

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


void draw_board(hangman *h)
{
        int xpos, ypos;

        window_clear(h);

        /* the hangman area at the top of the screen */
        xpos = (getmaxx(stdscr) - BOARD_WIDTH) / 2;
        ypos = (getmaxy(stdscr) - BOARD_HEIGHT) / 5;

        h->hman = newwin(BOARD_HEIGHT, BOARD_WIDTH, ypos, xpos);
        window_draw_box(h->hman, 0, 0, BOARD_HEIGHT, BOARD_WIDTH,
                        A_NORMAL, A_NORMAL);
        keypad(h->hman, TRUE);

        wattrset(h->hman, A_NORMAL);
        wbkgdset(h->hman, A_NORMAL & A_COLOR);

        touchwin(h->hman);
        wnoutrefresh(h->hman);

        /* The word area */
        //h->word = newwin();

        /* The misses area */
        //h->miss = newwin();

        /* A message box */
        xpos = (getmaxx(stdscr) - MSG_BOX_WIDTH) / 2;
        ypos = (getmaxy(stdscr) - MSG_BOX_HEIGHT);
        h->msg = newwin(MSG_BOX_HEIGHT, MSG_BOX_WIDTH, ypos, xpos);

        window_draw_edge(h->msg,
                         0, 0,
                         MSG_BOX_HEIGHT, MSG_BOX_WIDTH,
                         A_BOLD, A_NORMAL);

        wattrset(h->msg, A_NORMAL);
        wbkgdset(h->msg, A_NORMAL & A_COLOR);

        touchwin(h->msg);
        wnoutrefresh(h->msg);


        /* Box to display total number of gueses  */
        //h->guess = newwin();
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

        printf("Number of guesses: %d\n", h.game->guesses);
        game_free(h.game);

        exit(EXIT_SUCCESS);
}
