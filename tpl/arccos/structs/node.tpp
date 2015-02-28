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

#include <cassert>

#include "arccos/logging/metalogging.h"

#include "arccos/structs/graph.h"


using namespace arccos::structs;
    
    template<typename NodeValueType_, typename EdgeType_>
    int Node< NodeValueType_, EdgeType_ >::Counter = 0;
    
    template<typename NodeValueType_, typename EdgeType_>
    typename NodeSet< NodeValueType_, EdgeType_ >::const_iterator Node< NodeValueType_, EdgeType_ >::getNeigthbours() const
    {
        return graph_->edges_.at(value_).begin();
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    typename NodeSet< NodeValueType_, EdgeType_ >::const_iterator Node< NodeValueType_, EdgeType_ >::neigthboursEnd() const
    {
        return graph_->edges_.at(value_).end();
    }


    template<typename NodeValueType_, typename EdgeType_>
    Node< NodeValueType_, EdgeType_ >::Node( const Graph<NodeValueType_, EdgeType_>*  graph, const NodeValueType_& value) : value_(value), graph_(graph), id(Counter++)
    {
        arccos::Logger::debug( "construct Node with value : ", value_ , ", id == ", id);
    }

    template<typename NodeValueType_, typename EdgeType_>
    inline bool Node< NodeValueType_, EdgeType_ >::operator<(const Node& other) const
    {
        return value_ < other.value_;
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    const NodeValueType_& Node< NodeValueType_, EdgeType_ >::getValue() const
    {
        return value_;
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    std::vector< Path< NodeValueType_, EdgeType_ > > Node< NodeValueType_, EdgeType_ >::getShortestPathsTo ( const Node& other ) const
    {
//        if( graph_
    }


