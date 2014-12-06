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

typedef struct spl2phon_ {
    t_object xobj;
    t_float spl;
    t_float freq;
    t_inlet * freq_inlet;
    t_outlet * outlet;
} t_spl2phon;

void spl2phon_setup();

t_class * spl2phon_class;

void * spl2phon_new(t_float freq)
{
    t_spl2phon * res = (t_spl2phon*) pd_new(spl2phon_class);
    res->spl = 0;
    res->freq = freq;

    res->outlet = outlet_new(&res->xobj, &s_symbol);
    res->freq_inlet = floatinlet_new(&res->xobj, &res->freq);

    return (void*) res;
}

static void spl2phon_bang(t_spl2phon * x)
{
    double res = 0.0;
    int r = 0;
    if((r = iso226_spl2phon(x->spl, x->freq, &res)) != 0) {
        const char * err_str = iso226_strerror(r);
        error("[iso226] error: %s", err_str);
        return;
    }

    t_float out = res;
    outlet_float(x->outlet, out);
}

static void spl2phon_float(t_spl2phon * x, t_float spl)
{
    x->spl = spl;
    spl2phon_bang(x);
}

static void spl2phon_list(t_spl2phon * x, t_symbol *s, int argc, t_atom *argv)
{
    if(argc >= 2) {
        x->spl = atom_getfloat(argv);
        x->freq = atom_getfloat(argv + 1);
    }

    spl2phon_bang(x);
}

ISO226_EXPORT void spl2phon_setup()
{
    spl2phon_class = class_new(gensym("spl2phon"),
                              (t_newmethod) spl2phon_new,
                               0,
                               sizeof(t_spl2phon),
                               CLASS_DEFAULT,
                               A_DEFFLOAT,
                               0);

    class_addbang(spl2phon_class, spl2phon_bang);
    class_addfloat(spl2phon_class, spl2phon_float);
    class_addlist(spl2phon_class, spl2phon_list);
}
