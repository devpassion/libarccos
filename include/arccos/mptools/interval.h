/*
 * this file is part of libarccos https://github.com/devpassion/libarccos 
 * Copyright (C) 2015 Emmanuel Lacourarie git@lacourarie.org
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

#ifndef MPLTOOLS_INTERVAL_H
#define MPLTOOLS_INTERVAL_H
#include <string>
#include <array>
#include <functional>

// DEBUG
#include <iostream>

#define PRINT_ARR(X) \
    for( auto a : X ) \
    { \
        static unsigned int i; \
        std::cout << #X << "[" << i++  << "] == " << a << std::endl; \
    }

namespace arccos
{
    namespace mptools
    {

        template<int... I>
        struct TList;

        template<int begin, int end, unsigned int step = 1>
        struct interval_size
        {
            static const unsigned int value = ( (end - begin ) / step ) + 1;
        };


        template<unsigned int step,int... I>
        struct interval;

        template<unsigned int step, int begin, int... I>
        struct interval<step, begin, I...>
        {
        private:

            template<typename R, template<int> class Functor, int... I_>
            struct ToArray_
            {
                static constexpr std::array<R, sizeof...(I_)> ARR{{ Functor<I_>::value... }};
            };

            template<typename R, typename Functor, int... I_>
            struct ToArray__
            {
                static constexpr std::array<R, sizeof...(I_)> ARR{{ Functor{}(I_)... }};
            };


            template<int... I_>
            struct GetArrayHelper_
            {
                template<typename FunctorType>
                static constexpr auto getArray(FunctorType Functor) -> std::array< decltype(Functor(0)), sizeof...(I_)>
                {
                    return {{ Functor(I_)... }};
                };
            };

            using GetArrayHelper = GetArrayHelper_<begin, I...>;

        public:


            template<typename FunctorType>
            static constexpr auto getArray(FunctorType Functor) -> std::array< decltype(Functor(0)), sizeof...(I) + 1>
            {
                return GetArrayHelper::getArray(Functor);
            };

    //         template<typename R>
    //         static constexpr auto getArray<std::function<R(int)>>(std::function<R(int)> Functor) -> std::array< R, sizeof...(I) + 1>
    //         {
    //             return GetArrayHelper::getArray(Functor);
    //         };

            static const unsigned int size = sizeof...(I) + 1;
            using succ = interval<step, begin, I..., begin + (sizeof...(I) + 1) * step >;

            template<typename R, template<int> class Functor>
            using ToStaticArray = ToArray_<R,Functor, begin,I... >;

            template<typename R, typename Functor>
            using ToConstexprArray = ToArray__<R, Functor, begin, I... >;

            static constexpr int correct(unsigned int value)
            {
                return value - begin;
            };

            using set = TList<begin, I...>;

        };



        template<typename T>
        struct recArray
        {
            T head;
            recArray<T> tail;
        };


        template<typename T>
        struct GetArrayHelper;

        template<template<int...> class U, int... I>
        struct GetArrayHelper<U<I...>>
        {
            template<typename FunctorType>
            static constexpr auto getArray(FunctorType Functor) -> std::array< decltype(Functor(0)), sizeof...(I) + 1>
            {
                return {{ Functor(I)... }};
            };
        };


    //     template<typename FunctorType>
    //     static constexpr auto getArrayFromInterval(int begin, int end, int step, FunctorType Functor) -> std::array< decltype(Functor(0)), sizeof...(I) + 1>
    //     {
    //         return {{ Functor(I)... }};
    //     };


        template<int begin, int end, unsigned int step = 1>
        struct make_interval
        {
            static_assert( (end - begin ) % step == 0, "La mesure de l'intervalle doit être un multiple de step" );
            static_assert( end >= begin, "Bornes incorrectes" );
            using type = typename make_interval<begin,end-step, step>::type::succ;
        };

        template<int begin, unsigned int step>
        struct make_interval<begin,begin, step>
        {
            using type = interval<step,begin>;
        };

       
        //static_assert( make_interval< -1, 9, 2 >::type ,"" );

    }

}

#endif
