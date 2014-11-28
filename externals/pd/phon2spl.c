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

#include "phon2spl.h"

typedef struct phon2spl_ {
    t_object xobj;
    t_float phon;
    t_float freq;
    t_inlet * freq_inlet;
    t_outlet * outlet;
} t_phon2spl;

void phon2spl_setup();

t_class * phon2spl_class;

void * phon2spl_new(t_float freq)
{
    t_phon2spl * res = (t_phon2spl*) pd_new(phon2spl_class);
    res->phon = 0;
    res->freq = freq;

    res->outlet = outlet_new(&res->xobj, &s_symbol);
    res->freq_inlet = floatinlet_new(&res->xobj, &res->freq);

    return (void*) res;
}

static void phon2spl_bang(t_phon2spl * x)
{
    double res = 0.0;
    int r = 0;
    if((r = iso226_phon2spl(x->phon, x->freq, &res)) != 0) {
        const char * err_str = iso226_strerror(r);
        error("[iso226] error: %s", err_str);
        return;
    }

    t_float out = res;
    outlet_float(x->outlet, out);
}

static void phon2spl_float(t_phon2spl * x, t_float phon)
{
    x->phon = phon;
    phon2spl_bang(x);
}

static void phon2spl_list(t_phon2spl * x, t_symbol *s, int argc, t_atom *argv)
{
    if(argc >= 2) {
        x->phon = atom_getfloat(argv);
        x->freq = atom_getfloat(argv + 1);
    }

    phon2spl_bang(x);
}

void phon2spl_setup()
{
    phon2spl_class = class_new(gensym("phon2spl"),
                              (t_newmethod) phon2spl_new,
                               0,
                               sizeof(t_phon2spl),
                               CLASS_DEFAULT,
                               A_DEFFLOAT,
                               0);

    class_addbang(phon2spl_class, phon2spl_bang);
    class_addfloat(phon2spl_class, phon2spl_float);
    class_addlist(phon2spl_class, phon2spl_list);
}


