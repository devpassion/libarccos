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

#ifndef ARCCOS_BOARD_H
#define ARCCOS_BOARD_H

#include <cassert>

#include "structs/graph.h"


namespace arccos
{
    namespace game
    {
        template<typename CoordType, typename LinkType>
        class Board
        {
            static_assert( std::is_enum<LinkType>::value )
            CoordType width_;
            CoordType height_;

            std::vector <std::vector<Case < CoordType>>>
            board_;

            Graph<const Case<unsigned char> *, LinkType> g_;

            mutable unsigned char graph_builded = 0;

        public:
            Board(CoordType width, CoordType height);

            Board(const Board &other) = delete;

            Board(Board &&other) = delete;

            ~Board();

            const Case <CoordType> &getCase(CoordType x, CoordType y) const;

            Graph<const Case <CoordType> *, LinkState> &getGraph() const;

            Board &operator=(const Board &other) = delete;

            bool operator==(const Board &other) const = delete;
        };
    }
}



#endif // ARCCOS_BOARD_H
