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

#ifndef ISO226_H
#define ISO226_H

#ifdef __GNUC__
#define ISO226_EXPORT __attribute__((visibility("default")))
#elif _MSC_VER
#define ISO226_EXPORT
#endif

#define ISO226_LIBRARY_VERSION "0.1"
#define ISO226_VERSION "2009"

#ifdef __cplusplus
extern "C" {
#endif

ISO226_EXPORT int iso226_phon2spl(double phon, double freq, double * spl);
ISO226_EXPORT int iso226_spl2phon(double spl, double freq, double * phon);

enum ISO226_ERROR {
    ISO226_INVALID_FREQUENCY = 2,
    ISO226_INVALID_PHON,
    ISO226_NULL_DEST,
    ISO226_ERROR_MAX
};

ISO226_EXPORT const char * iso226_strerror(int c);

#ifdef __cplusplus
}
#endif

#endif // ISO226_H
