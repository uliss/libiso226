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

#ifndef CS_PHON2SPL_C
#define CS_PHON2SPL_C

#include "csdl.h"
#include "iso226.h"

typedef struct  phon2spl_ {
    OPDS  h;
    MYFLT *out;/* output pointer  */
    MYFLT *in1, *in2; /* input pointers */
} PHON2SPL;

int phon2spl(CSOUND *csound, PHON2SPL *p)
{
    double res = 0.0;
    int r = 0;
    if((r = iso226_phon2spl(*(p->in1), *(p->in2), &res)) == 0) {
        *(p->out) = (MYFLT) res;
    }

    return OK;
}

typedef struct  spl2phon_ {
    OPDS  h;
    MYFLT *out;/* output pointer  */
    MYFLT *in1, *in2; /* input pointers */
} SPL2PHON;

int spl2phon(CSOUND *csound, SPL2PHON *p) {
    double res = 0.0;
    int r = 0;
    if((r = iso226_spl2phon(*(p->in1), *(p->in2), &res)) == 0) {
        *(p->out) = (MYFLT) res;
    }

    return OK;
}

static OENTRY localops[] = {
    { "phon2spli", sizeof(PHON2SPL), 0, 3, "i", "ii", (SUBR) phon2spl, (SUBR) phon2spl, NULL },
    { "phon2spl",  sizeof(PHON2SPL), 0, 3, "k", "kk", (SUBR) phon2spl, (SUBR) phon2spl, NULL },
    { "spl2phoni", sizeof(SPL2PHON), 0, 3, "i", "ii", (SUBR) spl2phon, (SUBR) spl2phon, NULL },
    { "spl2phon",  sizeof(SPL2PHON), 0, 3, "k", "kk", (SUBR) spl2phon, (SUBR) spl2phon, NULL }
};

LINKAGE

#endif // CS_PHON2SPL_C
