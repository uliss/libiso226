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
#include <cstdlib>

#define CATCH_CONFIG_MAIN
#include "catch/include/catch.hpp"
#include "iso226.h"

bool cmp(double d1, double d2, double delta = 0.02) {
    if(abs(d1 - d2) < delta)
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

TEST_CASE( "spl2phon", "spl2phon test" ) {
    double res = 0;
    REQUIRE(iso226_spl2phon(80, 1000, &res) == 0);
    CHECK(cmp(res, 80));
    REQUIRE(iso226_spl2phon(70, 1000, &res) == 0);
    CHECK(cmp(res, 70));
    REQUIRE(iso226_spl2phon(60, 1000, &res) == 0);
    CHECK(cmp(res, 60));
    REQUIRE(iso226_spl2phon(50, 1000, &res) == 0);
    CHECK(cmp(res, 50));
    REQUIRE(iso226_spl2phon(40, 1000, &res) == 0);
    CHECK(cmp(res, 40));
    REQUIRE(iso226_spl2phon(30, 1000, &res) == 0);
    CHECK(cmp(res, 30));
    REQUIRE(iso226_spl2phon(20, 1000, &res) == 0);
    CHECK(cmp(res, 20));
}

TEST_CASE( "<=>", "<=> test" ) {
    double res0 = 0;
    double res1 = 0;
    REQUIRE(iso226_phon2spl(80, 1000, &res0) == 0);
    REQUIRE(iso226_spl2phon(res0, 1000, &res1) == 0);
    CHECK(cmp(res0, res0));

    for(int freq = 20; freq <= 12500; freq += 2) {
        for(int phon = 20; phon <= 80; phon += 2) {
            REQUIRE(iso226_phon2spl(phon, freq, &res0) == 0);
            REQUIRE(iso226_spl2phon(res0, freq, &res1) == 0);
            CHECK(cmp(res0, res0, 0.015));
        }
    }
}

TEST_CASE( "error", "error test" ) {
    for(int i = -1; i < 8; i++) {
        CHECK(iso226_strerror(i) != NULL);
    }
}

TEST_CASE( "phon2sone", "phon2sone test" ) {
    double sone;
    REQUIRE(iso226_phon2sone(40, &sone) == 0);
    CHECK(cmp(sone, 1));
    REQUIRE(iso226_phon2sone(50, &sone) == 0);
    CHECK(cmp(sone, 2));
    REQUIRE(iso226_phon2sone(60, &sone) == 0);
    CHECK(cmp(sone, 4));
    REQUIRE(iso226_phon2sone(70, &sone) == 0);
    CHECK(cmp(sone, 8));
    REQUIRE(iso226_phon2sone(80, &sone) == 0);
    CHECK(cmp(sone, 16));
    REQUIRE(iso226_phon2sone(90, &sone) == 0);
    CHECK(cmp(sone, 32));

    REQUIRE_FALSE(iso226_phon2sone(40, 0) == 0);
    REQUIRE_FALSE(iso226_phon2sone(10, &sone) == 0);
}

TEST_CASE( "sone2phon", "sone2phon test" ) {
    double phon;
    REQUIRE(iso226_sone2phon(1, &phon) == 0);
    CHECK(cmp(phon, 40));
    REQUIRE(iso226_sone2phon(2, &phon) == 0);
    CHECK(cmp(phon, 50));
    REQUIRE(iso226_sone2phon(4, &phon) == 0);
    CHECK(cmp(phon, 60));
    REQUIRE(iso226_sone2phon(8, &phon) == 0);
    CHECK(cmp(phon, 70));
    REQUIRE(iso226_sone2phon(16, &phon) == 0);
    CHECK(cmp(phon, 80));
    REQUIRE(iso226_sone2phon(32, &phon) == 0);
    CHECK(cmp(phon, 90));

    REQUIRE_FALSE(iso226_sone2phon(1, 0) == 0);
    REQUIRE_FALSE(iso226_sone2phon(0, &phon) == 0);
}

