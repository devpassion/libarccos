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

#ifndef GE_NSPAIR_H
#define GE_NSPAIR_H

#include <unordered_set>

namespace ge
{
    /**
        * real Pair {a,b} (no sorted) 
        **/
    template<typename T>
    struct nsPair
    {
        std::unordered_set<T> p_;
        friend std::hash< nsPair< T > >;
    public:
        nsPair( T v1, T v2 ) : p_(2)
        { 
            p_.insert( v1 );
            p_.insert( v2 );
        };
        
        nsPair( T&& v1, T&& v2 ) : p_(2) 
        { 
            p_.insert( v1 );
            p_.insert( v2 );
            
        };
        
        nsPair( const nsPair<T>& other ) : p_(other.p_) { }
        
        nsPair( nsPair<T>&& other ) : p_(other.p_) { }
        
        nsPair<T>& operator=( const nsPair<T> other ) = delete;
        
        bool operator==(const nsPair<T>& other) const
        {
            return (p_ == other.p_ );
        };
        
        
        bool operator<( const nsPair<T>& other ) const
        {
            auto it = p_.begin();
            auto ito = other.p_.begin();
            if( *it < *ito ) return true;
            if( *it == *ito )
            {
                it++;ito++;
                return ( *it < *ito );
            }
            return false; 
        }
    };
    
    
    
}




#endif