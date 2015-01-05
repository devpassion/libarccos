/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  tim288 <email>
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

#ifndef LOGGINGTEST_H
#define LOGGINGTEST_H
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>


namespace arccos
{

    class LoggingTest : public CppUnit::TestFixture
    {
    public:
	static CppUnit::TestSuite* suite();

	void testLogging();
    };

}

#endif // LOGGINGTEST_H
