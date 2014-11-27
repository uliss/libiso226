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

#include <cmath>

#define CATCH_CONFIG_MAIN
#include "catch/include/catch.hpp"
#include "iso226.h"

bool cmp(double d1, double d2) {
    if(abs(d1 - d2) < 0.02)
        return true;
    return false;
}

TEST_CASE( "phon2spl", "phon2spl test" )
{
    double res = 0;
    REQUIRE(iso226_phon2spl(80, 1000, &res) == 0);
    CHECK(cmp(res, 80));

    REQUIRE(iso226_phon2spl(70, 1000, &res) == 0);
    CHECK(cmp(res, 70));

    REQUIRE(iso226_phon2spl(60, 1000, &res) == 0);
    CHECK(cmp(res, 60));

    REQUIRE(iso226_phon2spl(50, 1000, &res) == 0);
    CHECK(cmp(res, 50));

    REQUIRE(iso226_phon2spl(40, 1000, &res) == 0);
    CHECK(cmp(res, 40));

    REQUIRE(iso226_phon2spl(30, 1000, &res) == 0);
    CHECK(cmp(res, 30));

    REQUIRE(iso226_phon2spl(20, 1000, &res) == 0);
    CHECK(cmp(res, 20));

    for(int freq = 20; freq <= 12500; freq++) {
        REQUIRE(iso226_phon2spl(20, freq, &res) == 0);
    }

    for(int freq = -20; freq < 20; freq++) {
        REQUIRE_FALSE(iso226_phon2spl(20, freq, &res) == 0);
    }

    for(int freq = 12501; freq < 13000; freq++) {
        REQUIRE_FALSE(iso226_phon2spl(20, freq, &res) == 0);
    }
}

