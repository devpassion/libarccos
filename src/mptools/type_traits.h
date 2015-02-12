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

#ifndef ARCCOS_TYPE_TRAITS_H
#define ARCCOS_TYPE_TRAITS_H

#include <type_traits>

namespace std 
{
    
    
    
    template<template<class> class A, template<class> class B>
    struct is_same_tpl : false_type
    {
    };
    
    template<template<class> class A>
    struct is_same_tpl<A,A> : true_type
    {
    };
    
    
};

namespace arccos 
{
    
    template<typename T>
    struct ValuePrinter
    {
        template<T value>
        struct printValue;
    };
    
    template<typename T>
    struct PrintType;
    
    template<typename T>
    struct BestParameterType
    {
        using type = typename std::conditional<
                            (sizeof(T) <= sizeof(void*)),
                            T, 
                            typename std::add_const<
                                        typename std::add_lvalue_reference<T>::type
                                    >::type
                            >::type;
    };
   
}

#endif // ARCCOS_TYPE_TRAITS_H
