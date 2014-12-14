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

#include <m_pd.h>
#include "iso226.h"

typedef struct phon2sone_ {
    t_object xobj;
    t_float sone;
    t_outlet * outlet;
} t_phon2sone;

void phon2sone_setup();

t_class * phon2sone_class;

void * phon2sone_new()
{
    t_phon2sone * res = (t_phon2sone*) pd_new(phon2sone_class);
    res->outlet = outlet_new(&res->xobj, &s_symbol);
    return (void*) res;
}

static void phon2sone_bang(t_phon2sone * x)
{
    outlet_float(x->outlet, x->sone);
}

static void phon2sone_float(t_phon2sone * x, t_float phon)
{
    int r = 0;
    double sone = 0.0;

    if((r = iso226_phon2sone(phon, &sone)) != 0) {
        const char * err_str = iso226_strerror(r);
        error("[iso226] error: %s", err_str);
        return;
    }

    x->sone = sone;
    outlet_float(x->outlet, x->sone);
}

ISO226_EXPORT void phon2sone_setup()
{
    phon2sone_class = class_new(gensym("phon2sone"),
                              (t_newmethod) phon2sone_new,
                               0,
                               sizeof(t_phon2sone),
                               CLASS_DEFAULT,
                               A_DEFFLOAT,
                               0);

    class_addbang(phon2sone_class, phon2sone_bang);
    class_addfloat(phon2sone_class, phon2sone_float);
}


