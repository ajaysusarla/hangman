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
#include <time.h>
#include <unistd.h>
#include <errno.h>

#ifdef LINUX
#include <aspell.h>

#define _ASPELL_DICT_LANG "en_US"
#endif

#include "hangman.h"
#include "game.h"
#include "display.h"
#include "util.h"

volatile sig_atomic_t fatal_error_in_progress = 0;

static void termination_handler(int sig)
{
        if (fatal_error_in_progress)
                raise(sig);

        fatal_error_in_progress = 1;

        display_fin();

        signal(sig, SIG_DFL);
        raise(sig);
}

void quit(hangman *h)
{
        display_fin();
        exit(EXIT_SUCCESS);
        printf("Number of guesses: %d\n", h->game->guesses);
        game_free(h->game);

}

int main(void)
{
        hangman h;

        signal(SIGINT, termination_handler);
        signal(SIGKILL, termination_handler);
        signal(SIGTERM, termination_handler);

        if (access(WORDS, F_OK) != 0) {
                fprintf(stderr, "Failed to open file `%s`", WORDS);
                perror(" ");
                exit(EXIT_FAILURE);
        }

       /* Initialise random number generator. */
        srand((unsigned int)getpid() + (unsigned int)time(NULL));

        if (display_init() != 0) {
                exit(EXIT_FAILURE);
        }

        h.title = "Hangman";
        h.game = game_new();

        draw_board(&h);

        refresh();

        game_loop(&h);

        quit(&h);
}
