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

#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "iso226.h"

static int f[] = {
    20, 25, 31.5, 40, 50,
    63, 80, 100, 125, 160,
    200, 250, 315, 400, 500,
    630, 800, 1000, 1250, 1600,
    2000, 2500, 3150, 4000, 5000,
    6300, 8000, 10000, 12500
};

static const size_t f_size = sizeof(f) / sizeof(f[0]);

static double af[] = {
    0.532, 0.506, 0.480, 0.455, 0.432,
    0.409, 0.387, 0.367, 0.349, 0.330,
    0.315, 0.301, 0.288, 0.276, 0.267,
    0.259, 0.253, 0.250, 0.246, 0.244,
    0.243, 0.243, 0.243, 0.242, 0.242,
    0.245, 0.254, 0.271, 0.301
};

static double Lu[] = {
    -31.6, -27.2, -23.0, -19.1, -15.9,
    -13.0, -10.3, -8.1, -6.2, -4.5,
    -3.1, -2.0, -1.1, -0.4, 0.0,
    0.3, 0.5, 0.0, -2.7, -4.1,
    -1.0, 1.7, 2.5, 1.2, -2.1,
    -7.1, -11.2, -10.7, -3.1
};

static double Tf[] = {
    78.5, 68.7, 59.5, 51.1, 44.0,
    37.5, 31.5, 26.5, 22.1, 17.9,
    14.4, 11.4, 8.6, 6.2, 4.4,
    3.0, 2.2, 2.4, 3.5, 1.7,
    -1.3, -4.2, -6.0, -5.4, -1.5,
    6.0, 12.6, 13.9, 12.3
};

static int get_koefi(double freq, double * paf, double * pTf, double * pLu) {
    if(freq < 20 || freq > 12500)
        return ISO226_INVALID_FREQUENCY;

    int i;
    for(i = 0; i < f_size; i++) {
        if(f[i] == freq) {
            *paf = af[i];
            *pTf = Tf[i];
            *pLu = Lu[i];
            break;
        }

        if(f[i] < freq && freq < f[i+1]) {
            // lineal interpolation
            double k = (freq - f[i]) / (f[i+1] - f[i]);
            *paf = (af[i+1] - af[i]) * k + af[i];
            *pTf = (Tf[i+1] - Tf[i]) * k + Tf[i];
            *pLu = (Lu[i+1] - Lu[i]) * k + Lu[i];
            break;
        }
    }

    return 0;
}

static double calc_Af(double phon, double af, double Tf, double Lu) {
    return 4.47 / 1000 * (pow(10, (0.025*phon)) - 1.15)
           + pow((0.4*pow(10, (((Tf+Lu)/10)-9 ))), af);
}

static int range_check(double phon, double freq) {
    if(phon > 90)
        return ISO226_INVALID_PHON;

    if(phon < 10)
        return ISO226_INVALID_PHON;

    if(freq < 20 || freq > 12500)
        return ISO226_INVALID_FREQUENCY;

    if(phon > 80 && freq > 4000)
        return ISO226_INVALID_PHON;

    return 0;
}

int iso226_phon2spl(double phon, double freq, double *spl) {
    if(spl == NULL)
        return ISO226_NULL_DEST;

    int r;

    r = range_check(phon, freq);
    if(r != 0)
        return r;

    double af;
    double Tf;
    double Lu;
    r = get_koefi(freq, &af, &Tf, &Lu);
    if(r != 0)
        return r;

    double Af = calc_Af(phon, af, Tf, Lu);
    double Lp = ((10/af)*log10(Af)) - Lu + 94;
    *spl = Lp;

    return 0;
}

static const char * iso226_errors[] = {
    "",
    "",
    "Invalid frequency: shoud be in range [20,12500]\n",
    "Invalid phon volume value\n",
    "Null output argument\n"
};

const char * iso226_strerror(int c) {
    const size_t num_errors = sizeof(iso226_errors) / sizeof(iso226_errors[0]);
    if(c < 0 || c >= num_errors)
        return "";

    return iso226_errors[c];
}

