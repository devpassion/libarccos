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

#ifndef ARCCOS_GRAPH_TRAIT_H
#define ARCCOS_GRAPH_TRAIT_H

namespace ge {

    template<typename NodeValueType_, typename EdgeType_>
    class Node;
    
    template<typename NodeValueType_, typename EdgeType_>
    class Path;
    
    template<typename NodeValueType_, typename EdgeType_>
    class NodeSet;
    
    
    
    template<typename NodeValueType_, typename EdgeType_>
    struct graph_trait
    {
        using PathType = Path<NodeValueType_, EdgeType_>;
        using NodeSetType = NodeSet<NodeValueType_, EdgeType_>;
        
        using NodeType = Node<NodeValueType_, EdgeType_>;
        using EdgeType = EdgeType_;
    };
}

#endif // ARCCOS_GRAPH_TRAIT_H
