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

#ifndef HEXA_H
#define HEXA_H
#include <ios>
#include <iomanip>
#include <algorithm>
#include <sstream>

namespace arccos
{

    class hexatools
    {
    
        static void printIndex( std::ostream& os, size_t lenght )
        {
            for(unsigned int i = 0; i < lenght;i++)
            {
                os << std::hex << std::setw(2) << std::setfill('0') << i << " ";
            }
            os << '\n';
        }
        
    public:
        template<typename T>
        static void hexadump( std::ostream& os, const T* raw, size_t lenght  )
        {
            const unsigned char* d = reinterpret_cast<const unsigned char*>( raw );

            printIndex(os, lenght + 1);

            for(unsigned int i = 0; i < lenght;i++)
            {
                os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(d[i]) << " ";
            }
            os << '\n';
            for(unsigned int i = 0; i < lenght;i++)
            {
                os << std::hex << std::setw(2) << std::setfill(' ') << ( ( d[i] >=32 && d[i] <= 126) ?  static_cast<char>(d[i]) : '.' ) << " ";
            }

        }
        
        template<typename CharType>
        static void hexadump( std::ostream& os, std::basic_string<CharType> str )
        {
            printIndex(os, str.length());
            
            std::for_each(str.begin(), str.end(),
                [&os]( CharType c ) {
                    const unsigned char* d = reinterpret_cast<const unsigned char*>( &c );
                    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(  *d ) << " ";
                }
            );
            os << '\n';
            std::for_each(str.begin(), str.end(),
                          [&os]( CharType c ) {
                              os << std::hex << std::setw(2) << std::setfill(' ') << ( ( c >=32 && c <= 126) ?  static_cast<CharType>(c) : '.' ) << " ";
                          }
            );
            
            
        }
        
        
        template<typename CharType>
        static std::string getHexadump( std::basic_string<CharType> str )
        {
            std::ostringstream oss;
            hexadump(oss, str);
            return oss.str();
        }
        
        template<typename T>
        static std::string getHexadump( const T* str, size_t lenght )
        {
            std::ostringstream oss;
            hexadump(oss, str, lenght);
            return oss.str();
        }
        
        template<typename T>
        static std::string getMemDump(const T* str, size_t lenght)
        {
            std::ostringstream oss;
            memDump(oss, str, lenght);
            return oss.str();
        }
        
        template<typename T>
        static void memDump(std::ostream& os, const T* str, size_t length)
        {
            for(const T* b = str; b != str + length;b++)
            {
                os << (void*) b << " : " << std::flush; 
                os << std::hex << *b << std::flush;
                os << std::endl;
            }
        }
        
        
        
    };
    
}

#endif // HEXA_H
