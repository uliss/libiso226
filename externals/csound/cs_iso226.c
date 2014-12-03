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
} phon2spl;

int phon2spl_init(CSOUND *csound, phon2spl *p) {
    double res = 0.0;
    int r = 0;
    if((r = iso226_phon2spl(*(p->in1), *(p->in2), &res)) == 0) {
        *(p->out) = (MYFLT) res;
    }

    return OK;
}

int phon2spl_process_control(CSOUND * csound, phon2spl *p) {
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
} spl2phon;

int spl2phon_init(CSOUND *csound, spl2phon *p) {
    double res = 0.0;
    int r = 0;
    if((r = iso226_spl2phon(*(p->in1), *(p->in2), &res)) == 0) {
        *(p->out) = (MYFLT) res;
    }

    return OK;
}

int spl2phon_process_control(CSOUND * csound, spl2phon *p) {
    double res = 0.0;
    int r = 0;
    if((r = iso226_spl2phon(*(p->in1), *(p->in2), &res)) == 0) {
        *(p->out) = (MYFLT) res;
    }

    return OK;
}

static OENTRY localops[] = {
    {
        "phon2spl", sizeof(phon2spl), 0, 3, "k", "kk",
        (SUBR) phon2spl_init,
        (SUBR) phon2spl_process_control,
        NULL
    },
    {
        "phon2spl", sizeof(phon2spl), 0, 3, "i", "ii",
        (SUBR) phon2spl_init,
        (SUBR) phon2spl_process_control,
        NULL
    },
    {
        "spl2phon", sizeof(spl2phon), 0, 3, "k", "kk",
        (SUBR) spl2phon_init,
        (SUBR) spl2phon_process_control,
        NULL
    },
    {
        "spl2phon", sizeof(spl2phon), 0, 3, "i", "ii",
        (SUBR) spl2phon_init,
        (SUBR) spl2phon_process_control,
        NULL
    }
};

LINKAGE

#endif // CS_PHON2SPL_C
