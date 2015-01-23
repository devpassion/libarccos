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

#include "intervaltest.h"
#include <cppunit/TestCaller.h>

namespace arccos
{
    namespace mptools
    {
        CppUnit::TestSuite* IntervalTestFixture::suite()
        {
            CppUnit::TestSuite* suite = new CppUnit::TestSuite("IntervalTestFixture");
            suite->addTest(new CppUnit::TestCaller<IntervalTestFixture>("StaticInterval", &IntervalTestFixture::testStaticInterval));
            return suite;
        };

        void IntervalTestFixture::testStaticInterval()
        {
            //std::array<int, interval_size<0,8,1>::value> ARR = make_interval< 0, 8, 1 >::type::ToConstexprArray<int, constexprFunctor>::ARR;


            auto lambda = [](int i){
                return i + 2;
            };

            auto A = make_interval<0,8,1>::type::getArray( [](int i){
                return i + 2;
            } );




            constexpr auto myF = constexprFunctor{};

            auto B = make_interval<0,8,1>::type::getArray( myF );



            auto C = GetArrayHelper<make_interval<0,8,1>::type::set>::getArray(myF);
            auto D = GetArrayHelper<make_interval<0,8,1>::type::set>::getArray(lambda);

            
            
            
            auto F = make_interval<0,10,2>::type::ToStaticArray<double,StaticFunctor>::ARR;
            
            PRINT_ARR( (F) );
            
            CPPUNIT_ASSERT(( B[0] == 1 ));
            CPPUNIT_ASSERT(( B[8] == 9 ));
            CPPUNIT_ASSERT(( C[0] == 1 ));
            CPPUNIT_ASSERT(( C[8] == 9 ));

            CPPUNIT_ASSERT(( A[0] == 2 ));
            CPPUNIT_ASSERT(( A[8] == 10 ));
            CPPUNIT_ASSERT(( D[0] == 2 ));
            CPPUNIT_ASSERT(( D[8] == 10 ));

            for(int k = 0; k <= 5; k++)
            {
                CPPUNIT_ASSERT(( F[k] == 2*k+1 ));
            }

        };
    }
}
