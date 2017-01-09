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
#include <string.h>

#include "util.h"

unsigned int get_num_words_in_dict(void)
{
        unsigned int words = 0;
        FILE *f;

        f = fopen(WORDS, "r");
        if (f == NULL) {
                fprintf(stderr, "fopen: Unable to open file `%s`.\n", WORDS);
                return -1;
        }

        for (;;) {
                char buf[2] = { 0 };
                size_t n = fread(buf, 1, 1, f);

                if (n < 1) {
                        break;
                }
                if (strncmp(buf, "\n", 1) == 0) {
                        words++;
                }
        }

        if (fclose(f) != 0) {
                fprintf(stderr, "Unable to close file `%s`.\n", WORDS);
        }

        return words;
}

/* From: http://www.azillionmonkeys.com/qed/random.html */
#define RS_SCALE (1.0 / (1.0 + RAND_MAX))

double drand(void)
{
    double d;

    do {
            d = (((rand () * RS_SCALE) + rand ()) * RS_SCALE + rand ()) * RS_SCALE;
    } while (d >= 1); /* Round off */

    return d;
}
