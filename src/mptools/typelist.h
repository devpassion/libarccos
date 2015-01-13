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
    
    
    /****** Typelist Cons ******/
    
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
    
    
    
        
    
    template<typename HEAD_, typename... TAIL_>
    struct Typelist<HEAD_, TAIL_...>
    {
        
        private:
        /****** Merge helpers ******/
    
        template<typename Typelist1>
        struct MergeHelper;
        
        template<typename... Tailtypes1>
        struct MergeHelper<Typelist<Tailtypes1...>>
        {
            template<typename Typelist2>
            struct MergeHelper2;
            
            template<typename... Tailtypes2>
            struct MergeHelper2<Typelist<Tailtypes2...>>
            {
                using type = Typelist<Tailtypes1..., Tailtypes2... >;
            };
        };
        
        
    public:
        
        using HEAD = HEAD_;
        using TAIL = Typelist<TAIL_...>;
        
        enum { size = 1 + TAIL::size };

        template<typename T>
        using Contain = typename std::conditional<
                        std::conditional<
                            std::is_same<T,HEAD>::value, 
                            std::true_type, 
                            std::false_type
                        >::type::value || TAIL::template Contain<T>::value,
                        std::true_type, 
                        std::false_type
                    >::type;
	
        using RemoveDuplicates = typename std::conditional<
                                            TAIL::template Contain<HEAD>::value,
                                            typename TAIL::RemoveDuplicates,
                                            typename Cons<HEAD, typename TAIL::RemoveDuplicates>::type
                                        >::type;

        template<typename T>
        using Erase = typename std::conditional<
                                std::is_same<T,HEAD>::value, 
                                typename TAIL::template Erase<T>,
                                typename Cons<HEAD, typename TAIL::template Erase<T> >::type
                            >::type;
	
        template<typename T>
        using Index = typename std::conditional<
                            std::is_same<T,HEAD>::value, 
                            std::integral_constant<int, 0>,
                            
                            typename std::conditional<
                                TAIL::size != 0,
                                std::integral_constant<int, 1 + TAIL::template Index<T>::value>,
                                std::integral_constant<int,-1>
                            >::type
                        >::type;
        
        using Reverse = typename Cons<HEAD, typename TAIL::Reverse>::type;
        
        template<typename... Types>
        using Equal = typename std::conditional<
                        std::is_same< Typelist<HEAD_, TAIL_...>, Typelist<Types...>  >::value,
                        std::true_type,
                        std::false_type
                        >::type;
        
        
        template<typename... Types>
        using AddQueue = Typelist<HEAD, TAIL_..., Types...>;
        
        
        
        template<typename... Types>
        using AddHead = Typelist<Types..., HEAD, TAIL_...>;
        
        
    
        
        template<typename Old, typename New>
        using Replace = typename std::conditional<
                                    std::is_same<Old, HEAD>::value,
                                    typename Cons<New, typename TAIL::template Replace<Old, New> >::type,
                                    typename Cons<HEAD, typename  TAIL::template Replace<Old, New> >::type
                                >::type;
        
        template<typename TypelistToAdd>
        using Merge = typename MergeHelper<Typelist<HEAD, TAIL_...>>::template MergeHelper2<TypelistToAdd>::type;
        
        
        /*
        template<template<class> Sorter>
        using Sort = ToImpl;
        */
	
    
    
        
        /*******************************/
	
	
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
    using Index = std::integral_constant<int, -1>;
    
	using Reverse = Typelist<>;
	
	template<typename Old, typename New>
	using Replace = Typelist<>;
	
    
    template<typename... Types>
    using Equal = typename std::conditional<
                    sizeof...(Types) == 0,
                    std::true_type,
                    std::false_type
                    >::type;
	
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