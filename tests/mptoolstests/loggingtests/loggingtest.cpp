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

#include <fstream>
#include <cppunit/TestCaller.h>


#include "loggingtest.h"
#include "logging/metalogging.h"
#include "logging/hexa.h"


namespace arccos
{
    
    
    class X
    {
        const int x_;
    public:
        
        X( int x ) : x_(x) {}
        X( const X& other) = delete;
        X& operator=( const X& other) = delete;
        X( X&& other ) : x_(other.x_) { }
        
        friend std::ostream& operator<<( std::ostream& os, const X& x )
        {
            return os << x.x_ << std::endl;
        }
    };

    class Y
    {
        const int y_;
    public:
        
        Y( int y ) : y_(y) {}
        Y( const Y& other) = delete;
        Y& operator=( const X& other) = delete;
        Y( Y&& other ) = delete;
        
        friend std::ostream& operator<<( std::ostream& os, const Y& y )
        {
            return os << y.y_ << std::endl;
        }
    };
    
    
    CppUnit::TestSuite* LoggingTest::suite()
    {
        CppUnit::TestSuite* suite = new CppUnit::TestSuite("LoggingTest");
        suite->addTest(new CppUnit::TestCaller<LoggingTest>("testLogging", &LoggingTest::testLogging));
        return suite;
    }
  
    void LoggingTest::testLogging()
    {
	
        std::stringbuf buf ;
        auto oldBuf = std::clog.rdbuf( &buf	);
        Logger::error("Err", "or", 42);
        Logger::warning("Warn", "ing", 42);
        Logger::info("In", "fo", 42);
        Logger::debug("Deb", "ug", 42);
        Logger::trace("Tra", "ce", 42);
        
        
        X x(0);
        Logger::trace(x);
        Logger::trace(X(1));
        
        Y y(0);
        Logger::trace(y);
        
        Logger::trace(Y(1));
        
        std::clog.rdbuf( oldBuf );
    

        
        // for debug purpose
        // hexatools::hexadump(std::cout, buf.str() );
        
        
        CPPUNIT_ASSERT( buf.str() == "[error] Err or 42\n[warning] Warn ing 42\n[info] In fo 42\n" );
	
    }

}