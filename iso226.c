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
#include "iso226_data.h"

#define MIN_FREQ 20
#define MAX_FREQ 12500

static int get_koefi(double freq, double * paf, double * pTf, double * pLu) {
    if(freq < MIN_FREQ || freq > MAX_FREQ)
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

static double calc_Bf(double spl, double af, double Tf, double Lu) {
    return pow(0.4 * pow(10, (spl + Lu)/10 - 9), af)
            - pow(0.4 * pow(10, (Tf + Lu) / 10 - 9), af)
            + 0.005135;
}

int iso226_spl2phon(double spl, double freq, double * phon) {
    if(phon == NULL)
        return ISO226_NULL_DEST;

    int r = 0;
    double af;
    double Tf;
    double Lu;
    r = get_koefi(freq, &af, &Tf, &Lu);
    if(r != 0)
        return r;

    double Bf = calc_Bf(spl, af, Tf, Lu);
    double Ln = 40 * log10(Bf) + 94;

    *phon = Ln;

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

