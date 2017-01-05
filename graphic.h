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

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#define GRAPHIC_ROWS 10
#define GRAPHIC_COLS 14

char *graphic_start[] = {
        "/==-----+     ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||============"
};

char *graphic_stage_1[] = {
        "/==-----+     ",
        "||      |     ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||============",
};

char *graphic_stage_2[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||============",
};

char *graphic_stage_3[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||      -     ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||============",
};

char *graphic_stage_4[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||      -     ",
        "||      |     ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||============",
};

char *graphic_stage_5[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||      -     ",
        "||     /|     ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||============",
};


char *graphic_stage_6[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||      -     ",
        "||     /|\\   ",
        "||            ",
        "||            ",
        "||            ",
        "||            ",
        "||============",
};

char *graphic_stage_7[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||      -     ",
        "||     /|\\   ",
        "||      ^     ",
        "||            ",
        "||            ",
        "||            ",
        "||============",
};

char *graphic_stage_8[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||      -     ",
        "||     /|\\   ",
        "||      ^     ",
        "||     /      ",
        "||            ",
        "||            ",
        "||============",
};

char *graphic_end[] = {
        "/==-----+     ",
        "||      |     ",
        "||      O     ",
        "||      -     ",
        "||     /|\\   ",
        "||      ^     ",
        "||     / \\   ",
        "||            ",
        "||            ",
        "||============",
};

#endif  /* _GRAPHIC_H_ */
