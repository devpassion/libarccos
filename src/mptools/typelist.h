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


#ifndef MPLTOOLS_TYPELIST_H
#define MPLTOOLS_TYPELIST_H

#include <type_traits>

namespace mpltools
{
    template<typename... Types>
    struct Typelist;
    
    template<typename... Types>
    struct Cons;
    
    template<typename HEAD, typename... Tailtypes>
    struct Cons<HEAD, Typelist<Tailtypes...>>
    {
	using type = Typelist<HEAD, Tailtypes...>;
    };
    
    template<typename HEAD, typename... Tailtypes>
    struct Cons<Typelist<Tailtypes...>, HEAD>
    {
	using type = Typelist<Tailtypes..., HEAD>;
    };
    
    
    template<typename Typelist1>
    struct Merge;
    
    template<typename... Tailtypes1>
    struct Merge<Typelist<Tailtypes1...>>
    {
	template<typename Typelist2>
	struct MergeHelper;
	
	template<typename... Tailtypes2>
	struct MergeHelper<Typelist<Tailtypes2...>>
	{
	    using type = Typelist<Tailtypes1..., Tailtypes2 >;
	};
    };
    
    
    
    template<typename HEAD_, typename... TAIL_>
    struct Typelist<HEAD_, TAIL_...>
    {
	using HEAD = HEAD_;
	using TAIL = Typelist<TAIL_...>;
	
	enum { size = 1 + TAIL::size };
	
	template<typename T>
	using Contain = std::conditional<
			    std::conditional<
				std::is_same<T,HEAD>, 
				true_Type, 
				false_type
			    >::value || TAIL::Contain<T>::value,
			    std::true_Type, 
			    std::false_type
			>::type;
	
	using RemoveDuplicates = std::conditional<
			    TAIL::Contain<HEAD>,
			    TAIL::RemoveDuplicates,
			    Cons<HEAD, TAIL::RemoveDuplicates>::type
			>::type;
	
	template<typename T>
	using Erase = std::conditional<
			    std::is_same<T,HEAD>, 
			    TAIL::Erase<T>,
			    Cons<HEAD, TAIL::Erase<T>::type >
			>::type;
			
	template<typename T>
	using Index = std::conditional<
			    std::is_same<T,HEAD>, 
			    std::integral_constant<int, 0>,
			    std::integral_constant<int, 1 + TAIL::Index<T>::value>
			>::type;
	
	using Reverse = Cons<HEAD, TAIL::Reverse>::type;
	
	
	template<typename... Types>
	using AddQueue = Typelist<HEAD, TAIL_..., Types...>;
	
	template<typename... Types>
	using AddHead = Typelist<Types..., HEAD, TAIL_...>;
	
	template<typename Typelist2>
	struct Merge;
	
	template<typename... Types>
	struct Merge<Typelist<Types...>>
	{
	    using type = Typelist<HEAD, TAIL_..., Types...>;
	};
	
	
	template<typename Old, typename New>
	using Replace = std::conditional<
			    std::is_same<Old, HEAD>::value,
			    Cons<New, TAIL::Replace<Old, New> >::type,
			    Cons<HEAD, TAIL::Replace<Old, New> >::type
			>::type;
	
	
	template<template<class> Sorter>
	using Sort = ToImpl;
	
	
    private:
	
	
    };
    
    template<>
    struct Typelist<>
    {
	enum { size = 0 };
	
	template<typename T>
	using Contain = std::false_type;
	
	using RemoveDuplicates = Typelist<>;
	
	template<typename T>
	using Erase = Typelist<>;
	
	template<typename T>
	using Reverse = Typelist<>;
	
	template<typename Old, typename New>
	using Replace = Typelist<>;
	
	
	template<typename Typelist2>
	struct Merge;
	
	template<typename... Types>
	struct Merge<Typelist<Types...>>
	{
	    using type = Typelist<Types...>;
	};
	
	template<typename... Types>
	using AddQueue = Typelist<Types...>;
	
	template<typename... Types>
	using AddHead = Typelist<Types...>;
	
    };
    
    
    
}

#endif