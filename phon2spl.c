/***************************************************************************
 *   Copyright (C) 2014 by Serge Poltavski                                 *
 *   serge.poltavski@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program. If not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "iso226.h"

static const char * PROGRAMM_NAME = 0;

static struct option long_options[] = {
    {"help",  no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
    {0, 0, 0, 0}
};

static const char * short_options = "hV";

static void usage() {
    puts ("Converts PHON volume to SPL in db, according to ISO 226 equal-loudness level contours.");
    printf("    Usage: %s PHON FREQUENCY\n", PROGRAMM_NAME);
}

static void parse_options(int argc, char * argv[]) {
    PROGRAMM_NAME = argv[0];
    int c = 0;
    int option_index = 0;

    while (1) {
        c = getopt_long (argc, argv, short_options, long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
        case 'h':
            usage();
            exit(0);
            break;
        case 'V':
            printf("Version: %s\n", ISO226_LIBRARY_VERSION);
            exit(EXIT_SUCCESS);
            break;
        case '?':
            usage();
            exit(EXIT_FAILURE);
            break;
        }
    }

    if(argc != 3) {
        usage();
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char * argv[]) {
    double fon = 0;
    double freq = 0;
    double res = 0;
    int ret;

    parse_options(argc, argv);

    fon = strtod(argv[1], NULL);
    freq = strtod(argv[2], NULL);

    ret = iso226_phon2spl(fon, freq, &res);

    if(ret != 0) {
        fputs(iso226_strerror(ret), stderr);
        return ret;
    }

    printf("%f\n", res);

    return EXIT_SUCCESS;
}

