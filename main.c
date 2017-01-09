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

static void termination_handler(int sig)
{
        switch(sig) {
        case SIGINT:
        case SIGHUP:
                display_fin();
                break;
        default:
                break;
        }

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
        struct sigaction sa;
        hangman h;
        unsigned int words, word_location;

        words = get_num_words_in_dict();
        /* Initialise random number generator. */
        srand((unsigned int)getpid() + (unsigned int)time(NULL));
        word_location = irand(words);

        /* Setup termination signal handler */
        sa.sa_handler = &termination_handler;
        sa.sa_flags = SA_RESTART;
        sigfillset(&sa.sa_mask);

        if (sigaction(SIGHUP, &sa, NULL) == -1) {
                perror("sigaction - SIGHUP");
        }

        if (sigaction(SIGINT, &sa, NULL) == -1) {
                perror("sigaction - SIGNINT");
        }

        if (access(WORDS, F_OK) != 0) {
                fprintf(stderr, "Failed to open file `%s`", WORDS);
                perror(" ");
                exit(EXIT_FAILURE);
        }

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
