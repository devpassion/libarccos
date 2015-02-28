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

#include "arccos/game/board.h"

using namespace arccos::game;
    
template<typename CoordType>
Board<CoordType>::Board(CoordType width, CoordType height) : width_( width ), height_( height ), board_(height)
{
    for( CoordType j = 0; j < width; j++ )
    {
        for( CoordType i = 0; i < height_; i++ )
        {
            board_[i].emplace_back( i, j );
        }
    }
}

template<typename CoordType>
Graph<const Case<CoordType>*, LinkType>& Board<CoordType>::getGraph() const
{
    if( !graph_builded )
    {
        for( CoordType j = 0; j < width_; j++ )
        {
            arccos::Logger::trace( "Build graph : j == ",static_cast<int>( j ) );
            for( CoordType i = 0; i < height_; i++ )
            {
                arccos::Logger::trace( "Build graph : i == ",static_cast<int>( i ) );
                g_.addNode( &getCase( i, j ) );
                if( i > 0 )
                {
                    // TODO : déplacer le défaut dans une autre structure
                    g_.addEdge( &getCase( i - 1, j ),&getCase( i, j ), Linktype::Default );
                    if( j > 0 )
                    {
                        // TODO : déplacer le défaut dans une autre structure
                        g_.addEdge( &getCase( i - 1, j - 1 ),&getCase( i, j ), Linktype::Default );
                    }

                }
                if( j > 0 )
                {
                    g_.addEdge( &getCase( i, j - 1 ), &getCase( i, j ), Linktype::Default );
                    if( i < height_ - 1 )
                    {
                        g_.addEdge( &getCase( i + 1, j - 1 ),&getCase( i, j ), Linktype::Default );
                    }
                }

            }
        }
        graph_builded = 1;
    }

    return g_;
}

template<typename CoordType>
Board<CoordType>::Board(const Board& other) = delete;

template<typename CoordType>
Board<CoordType>::~Board() {}

template<typename CoordType>
const Case<CoordType>& Board<CoordType>::getCase(CoordType x, CoordType y) const
{
    arccos::Logger::trace( "getCase, x == ",static_cast<int>( x ), ",y == ", static_cast<int>( y ) );
    assert( x >= 0 && x < width_ && y >= 0 && y < height_ );
    return board_[x][y];
}


template<typename CoordType>
bool Board<CoordType>::canPlaceWall( int x, int y, std::string orientation )
{

}

template<typename CoordType>
Board<CoordType>::addWall( int x, int y, std::string orientation )
{
    Wall::addWall(x, y, orientation, [](const Wall &wall)
    {
        switch (wall.orientation_)
        {
            case(Wall::Orientation::H):
            {
                g_.removeEdge(&getCase(x, y - 1), &getCase(x, y));
                g_.removeEdge(&getCase(x + 1, y - 1), &getCase(x + 1, y));
                break;
            }
            case(Wall::Orientation::V):
            {
                g_.removeEdge(&getCase(x - 1, y), &getCase(x, y));
                g_.removeEdge(&getCase(x - 1
                1, y + 1 ), &getCase(x - 1, y + 1)  );
                break;
            }
        }
    });

}
