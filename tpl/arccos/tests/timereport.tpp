/*
 * libarccos
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

#include "arccos/test/timereport.h"

using namespace arccos::test;

template<typename... FunctorTypes>
TimeReport<FunctorTypes...>::TimeReport( std::function<void(FunctorTypes...)> functor ) : functor_(functor) {}


template<typename... FunctorTypes>
void TimeReport<FunctorTypes...>::start( std::ostream& os )
{

}

template<typename... FunctorTypes>
void TimeReport<FunctorTypes...>::kill(  )
{

}



