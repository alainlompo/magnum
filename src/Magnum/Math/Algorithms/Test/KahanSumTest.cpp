/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <numeric>
#include <Corrade/TestSuite/Tester.h>

#include "Magnum/Magnum.h"
#include "Magnum/Math/Algorithms/KahanSum.h"

namespace Magnum { namespace Math { namespace Algorithms { namespace Test {

struct KahanSumTest: TestSuite::Tester {
    explicit KahanSumTest();

    void testFloat();
    void testDouble();
    void testInteger();
    void iterative();
};

KahanSumTest::KahanSumTest() {
    addTests({&KahanSumTest::testFloat,
              &KahanSumTest::testDouble,
              &KahanSumTest::testInteger,
              &KahanSumTest::iterative});
}

void KahanSumTest::testFloat() {
    std::vector<Float> data(10000000, 0.1f);

    CORRADE_COMPARE(kahanSum(data.begin(), data.end()), 1.0e6f);
    CORRADE_COMPARE(std::accumulate(data.begin(), data.end(), 0.0f), 1.087937e6f);
}

void KahanSumTest::testDouble() {
    std::vector<Double> data(10000000, 0.0001);

    CORRADE_COMPARE(kahanSum(data.begin(), data.end()), 1000.0);
    CORRADE_COMPARE(std::accumulate(data.begin(), data.end(), 0.0), 999.999999820615);
}

void KahanSumTest::testInteger() {
    std::vector<Int> data(10000000, 1);

    CORRADE_COMPARE(kahanSum(data.begin(), data.end()), 10000000);
    CORRADE_COMPARE(std::accumulate(data.begin(), data.end(), 0), 10000000);
}

void KahanSumTest::iterative() {
    std::vector<Float> data(10000000, 0.1f);

    Float sum{}, sumKahan{}, c{};
    for(Float d: data) {
        sum += d;
        sumKahan = kahanSum(&d, &d + 1, sumKahan, &c);
    }

    CORRADE_COMPARE(sumKahan, 1.0e6f);
    CORRADE_COMPARE(sum, 1.087937e6f);
}

}}}}

CORRADE_TEST_MAIN(Magnum::Math::Algorithms::Test::KahanSumTest)
