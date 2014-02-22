/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  tim288 <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LIBARCCOS_MPTOOLSTESTS_INTERVALTEST
#define LIBARCCOS_MPTOOLSTESTS_INTERVALTEST

#include <array>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include "../../../src/mptools/interval.h"


namespace arccos
{
    namespace mptools
    {
        template<int I>
        struct StaticFunctor
        {
            static const int value = I + 1;
        };

        template<unsigned int step, int begin, int end>
        struct IntervalTest
        {
            static constexpr int func(int i) { return i + 1; };

            using type = typename make_interval< begin, end, step >::type;

            static constexpr std::array<int, type::size > ARR = type::getArray(func);

            static_assert( type::size == interval_size<begin, end, step>::value , "Taille de l'intervalle incorrecte" );
            //static_assert( type::template ToConstexprArray<int, myFunctor>::ARR[0] == myFunctor(0), "DEBUG1" );
            //static_assert( type::template ToStaticArray<int, StaticFunctor>::ARR[0] == StaticFunctor<0>::value, "DEBUG2" );

        };

        template struct IntervalTest<1,-1,9>;
        template struct IntervalTest<2,0,8>;


        class IntervalTestFixture : public CppUnit::TestFixture
        {
            struct constexprFunctor
            {
                constexpr int operator()(int i) const
                {
                    return i + 1;
                };
            };

        public:
            static CppUnit::TestSuite* suite();

            void testStaticInterval();
        };
    }
}

#endif // LIBARCCOS_MPTOOLSTESTS_INTERVALTEST

