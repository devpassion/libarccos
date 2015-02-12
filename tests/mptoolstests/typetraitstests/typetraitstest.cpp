/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
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

#include "typetraitstest.h"
#include <cppunit/TestCaller.h>

#include "../../../src/mptools/type_traits.h"



using namespace arccos;

#define SASSERT(x) static_assert( (x), #x );


template<typename T>
    struct tpl1
    {
    };
    
    template<typename T>
    struct tpl2
    {
    };

void TypetraitsTest::testTypetraits()
{
	// TODO ou placer ce test?
    SASSERT( ( ! std::is_same_tpl<tpl1, tpl2>::value ) );
    SASSERT( ( std::is_same_tpl<tpl2, tpl2>::value ) );
    SASSERT( ( std::is_same_tpl<tpl1, tpl1>::value ) );
    
    
    //Print<sizeof(void*)>();
    //Print<sizeof(long double)>();
    //PrintType<BestParameterType<long double>::type>();
    
    SASSERT(( !std::is_same<BestParameterType<long double>::type,const long double&>::value  ));
    SASSERT(( std::is_same<BestParameterType<unsigned char>::type,unsigned char>::value  ));
    
	//static_assert( false, "fail on test end");
}


CppUnit::TestSuite* TypetraitsTest::suite()
{
	CppUnit::TestSuite* suite = new CppUnit::TestSuite("TypetraitsTest");
    suite->addTest(new CppUnit::TestCaller<TypetraitsTest>("testLogging", &TypetraitsTest::testTypetraits));
    return suite;
}
