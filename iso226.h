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

/**
\mainpage ISO226 library documentation.

This library converts loudness units: phon, db (SPL) and sone.
More info can be found:
    - http://en.wikipedia.org/wiki/Phon
    - http://en.wikipedia.org/wiki/Sone
    - http://en.wikipedia.org/wiki/Sound_pressure_level

ISO 226 standard defines equal loudness curves.
    @see http://en.wikipedia.org/wiki/Equal-loudness_contour
*/

#ifdef __GNUC__
#define ISO226_EXPORT __attribute__((visibility("default")))
#elif _MSC_VER
#define __declspec(dllexport)
#endif

#define ISO226_LIBRARY_VERSION "0.1"
#define ISO226_VERSION "2009"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * Converts loudness value from 'phons' to dB (SPL) at specified pure tone frequency.
  * @param phon - value in phon (shoud be in range [10, 90])
  * @param freq - tone frequency (shoud be in range [20, 12500] for phon <= 80 and
  *     [20, 4000] for phon > 80)
  * @param spl - pointer to result in db (SPL)
  * @return - 0 on success or ISO226_ERROR otherwise
  * @see iso226_spl2phon()
  */
ISO226_EXPORT int iso226_phon2spl(double phon, double freq, double * spl);

/**
  * Converts loudness value from db (SPL) to phons at specified frequency.
  * @param spl - loudness in db
  * @param freq - tone frequency
  * @param phon - pointer to result in phon
  * @return - 0 on success or ISO226_ERROR on error
  * @see iso226_phon2spl()
  */
ISO226_EXPORT int iso226_spl2phon(double spl, double freq, double * phon);

/**
  * Converts loudness from phon values to sone.
  * @param phon - value in phon (should be >= 40)
  * @param sone - pointer to result in sone
  * @return 0 on success, or ISO226_ERROR on error
  */
ISO226_EXPORT int iso226_phon2sone(double phon, double * sone);

/**
  * Converts loudness from sone values to phon.
  * @param sone - value in sone (should be >= 1)
  * @param phon - pointer to result in phon
  * @return 0 on success, or ISO226_ERROR on error
  */
ISO226_EXPORT int iso226_sone2phon(double sone, double * phon);

enum ISO226_ERROR {
    ISO226_INVALID_FREQUENCY = 2,
    ISO226_NULL_DEST,
    ISO226_INVALID_PHON,
    ISO226_INVALID_SONE,
    _ISO226_ERROR_MAX
};

/**
  * Returns string error description by given error code
  * @param c - error code
  * @return pointer to static string
  */
ISO226_EXPORT const char * iso226_strerror(int c);

#ifdef __cplusplus
}
#endif

#endif // ISO226_H
