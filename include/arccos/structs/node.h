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


#ifndef ARCCOS_GRAPH_H
#error "Please just include graph.h (not node.h or nodeset.h)"
#endif

#ifndef ARCCOS_NODE_H
#define ARCCOS_NODE_H


#include <vector>

#include "arccos/logging/metalogging.h"


namespace arccos
{
    namespace structs
    {

        template<typename NodeValueType_, typename EdgeType_>
        class Graph;

        template<typename NodeValueType_, typename EdgeType_>
        class Path;

        template<typename NodeValueType_, typename EdgeType_>
        class NodeSet;

        template<typename NodeValueType_, typename EdgeType_>
        class Node
        {
            static int Counter;

            const NodeValueType_ value_;

            const Graph<NodeValueType_, EdgeType_> *graph_;

            const int id;


            //Node( const Graph<NodeValueType_, EdgeType_>* graph, NodeValueType_ value );


            friend Graph<NodeValueType_, EdgeType_>;


            //friend NodeSet<NodeValueType_, EdgeType_>;

            mutable NodeSet<NodeValueType_, EdgeType_> *neigthboursCache_;

            void updateCache();

        public:

            Node(const Graph <NodeValueType_, EdgeType_> *graph, const NodeValueType_ &value);

            Node( const Node& other) = delete;

            // TODO : implémenter
            Node( Node&& other) = delete;

            Node(const Graph <NodeValueType_, EdgeType_> *graph, NodeValueType_ &&value);


            // TODO : renvoyer un iterateur
            // Une fois les voisins calculés, mettre en cache puis renvoyer un iterateur
            typename NodeSet<NodeValueType_, EdgeType_>::const_iterator getNeigthbours() const;

            typename NodeSet<NodeValueType_, EdgeType_>::const_iterator neigthboursEnd() const;

            // TODO : updater quand le noeud est concerné (dans le graphe)
            void update() const;

            bool operator<(const Node &other) const;

            bool operator==(const Node &other) const
            {
                return value_ == other.value_;
            }

            bool operator==(const NodeValueType_ &other) const
            {
                return value_ == other;
            }


            const NodeValueType_ &getValue() const;

            std::vector<Path<NodeValueType_, EdgeType_>> getShortestPathsTo(const Node &other) const;


            friend std::ostream &operator<<(std::ostream &os, const Node<NodeValueType_, EdgeType_> &node)
            {
                return os << node.getValue() << std::flush;
            }

            ~Node()
            {
                arccos::Logger::trace("destruct node, id == ", id);
            }
        };
    }
}

namespace std
{
    template<typename NodeValueType_, typename EdgeType_>
    struct hash<arccos::structs::Node<NodeValueType_, EdgeType_>>
    {
        size_t operator()(const arccos::structs::Node<NodeValueType_, EdgeType_> &node) const
        {
            return hash<NodeValueType_>{}(node.getValue());
        }
    };
}

#endif // ARCCOS_NODE_H
