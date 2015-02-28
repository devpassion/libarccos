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

#include "typelisttest.h"
#include <cppunit/TestCaller.h>

#include "arccos/mptools/typelist.h"

#include "arccos/test/static.h"


using namespace arccos;
using namespace mpltools;





void TypelistTest::testTypelist()
{
	SASSERT( (Typelist<int, double>::size == 2 ) );
	SASSERT( Typelist<>::size == 0 );
	
    SASSERT( ( Typelist<int, double>::TAIL::size == 1 ) );
    SASSERT( ( Typelist<int, double, short, int>::size == 4 ) );

    SASSERT( ( Typelist<int, double>::Equal<int, double>::value ) );
    SASSERT( ( Typelist<>::Equal<>::value ) );
    
    SASSERT( (! Typelist<int, double>::Equal<int, short, double>::value) );
	
    
    SASSERT((  ! Typelist<int, short, double>::Equal<>::value  ));
    
    
    SASSERT((  Typelist<int, short, double>::Erase<double>::Equal<int, short>::value  ));
    
    SASSERT((  Typelist<int, short, double>::AddQueue<float, std::string>::Equal<int, short, double, float, std::string>::value  ));
    
    SASSERT((  Typelist<int, short, double>::AddHead<std::string, float>::Equal<std::string, float, int, short, double>::value  ));
    
    SASSERT((  Typelist<int, short, double, double, float>::Replace<double, float>::Equal<int, short, float, float, float>::value  ));
    
    SASSERT((  Typelist<int, short, double, double, float>::Replace<double, float>::Equal<int, short, float, float, float>::value  ));
    
    SASSERT(( Typelist<int, float>::Merge<Typelist<>>::Equal<int, float>::value ));
    
    SASSERT(( Typelist<int, float>::Merge<Typelist<double, double>>::Equal<int, float, double, double>::value ));
    
    
    SASSERT(( Typelist<int, float, double>::SortedInsert<SizeSorter, double>::Equal<int, float, double, double>::value ));
    
    SASSERT(( Typelist<int, double, short>::Sort<SizeSorter>::Equal<short, int, double>::value ));
    
    
}


CppUnit::TestSuite* TypelistTest::suite()
{
	CppUnit::TestSuite* suite = new CppUnit::TestSuite("TypelistTest");
    suite->addTest(new CppUnit::TestCaller<TypelistTest>("testLogging", &TypelistTest::testTypelist));
    return suite;
}
