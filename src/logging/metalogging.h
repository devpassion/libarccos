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
 
#ifndef METALOGGING
#define METALOGGING

#include <iostream>
#include <type_traits>

#define UNUSED(expr) do { (void)(expr); } while (0)

#ifndef LOGLEVEL
#define LOGLEVEL 2
#endif


#define PRINT( LEVEL ) template<typename... Args> \
	static void LEVEL(Args... args) \
	{ \
	Logger_<Level::LEVEL>::log( "[" #LEVEL "]", args...); \
	}; 


 namespace arccos
 {
 
    /*
     * Niveaux de log
     **/	
    enum Level : int
    {
        error = 0,
        warning = 1,
        info = 2,
        debug = 3,
        trace = 4
    };

    
    class LoggerHandler;
    
    class Logger
    {
		
		template<Level L >
		class Logger_
		{
			struct PrintLogger
			{
				template<typename Arg, typename... Args>
				void operator()(Arg arg, Args... args)
				{
					std::clog << arg << ' ';
					operator()(args...);
				};
				
				template<typename Arg>
				void operator()(Arg arg)
				{
					std::clog << arg << std::endl;
				};
			};
			
			struct NoPrintLogger
			{
			
			template<typename Arg, typename... Args>
			void operator()(Arg arg, Args... args)
			{
				UNUSED( arg );
				operator()(args...);
			};
			
			template<typename Arg>
			void operator()(Arg arg)
			{
				UNUSED( arg );
			};
			};
			
			enum { logLevel = LOGLEVEL };
			
			using PrinterType = typename std::conditional< (L <= static_cast<Level>( logLevel )) , PrintLogger, NoPrintLogger >::type;
			
		public:
			
			template<typename... Args>
			static inline void log(Args... args)
			{
				PrinterType{}(args...);
			};
		};
	    
	public:
	    PRINT( error )
	    PRINT( warning )
	    PRINT( info )
	    PRINT( debug )
	    PRINT( trace )
	    
		friend LoggerHandler;
	    
    };
	
    
 }
 
 #endif