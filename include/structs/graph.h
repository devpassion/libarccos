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
#define ARCCOS_GRAPH_H

#include <utility>
#include <unordered_map>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>


#include "nspair.h"
#include "node.h"
#include "path.h"
#include "nodeset.h"


namespace arccos
{

    namespace structs
    {

        template<typename NodeValueType_, typename EdgeType_>
        class Graph
        {

        private:


            std::unordered_map<NodeValueType_, Node< NodeValueType_, EdgeType_>> nodes_;

            // TODO : Should not be mutable
            mutable std::unordered_map<NodeValueType_, NodeSet < NodeValueType_, EdgeType_>> edges_;

            mutable std::unordered_map<NodeValueType_, unsigned int> connexesComposants_;

            std::unordered_map<std::pair<NodeValueType_, NodeValueType_>, EdgeType_> edgesTypes_;

            friend Path<NodeValueType_, EdgeType_>;
            friend Node<NodeValueType_, EdgeType_>;
            friend NodeSet<NodeValueType_, EdgeType_>;

            mutable std::unordered_map<
                    std::pair<NodeValueType_, NodeValueType_>,
                    std::vector<
                            arccos::structs::Path <
                                    NodeValueType_, EdgeType_
                            >
                    > >  pathCache_;


            void balance(std::vector<arccos::structs::Path<NodeValueType_, EdgeType_>>& ret,
                    std::unordered_map<NodeValueType_, std::shared_ptr< const arccos::structs::RecPath<NodeValueType_, EdgeType_>>>& leftMap,
            const std::unordered_map<NodeValueType_, std::shared_ptr< const RecPath<NodeValueType_, EdgeType_>>>& rightMap,
            std::unordered_set<const NodeValueType_ *>& visiteds,
            std::unordered_set<const NodeValueType_ *>& addeds ,
            std::unordered_map<NodeValueType_, std::shared_ptr< const RecPath<NodeValueType_, EdgeType_>>>& newLeftMap
            ) const;

        public:

            void updateCC() const;

            void updatePathCache() const;

            Graph() {
            }

            Graph(const Graph &other) = delete;

            Graph(const Graph &&other);

            ~Graph() {
            }

            Graph &operator=(const Graph &other) = delete;

            bool operator==(const Graph &other) const = delete;

            NodeSet<NodeValueType_, EdgeType_> newNodeSet() const;

            NodeSet<NodeValueType_, EdgeType_> allNodeSet() const;


            const Node <NodeValueType_, EdgeType_> &getNode(const NodeValueType_ &nodeValue) const {
                return nodes_.at(nodeValue);
            }

            void addNode(const NodeValueType_ &nodeValue);

            void addNode(NodeValueType_ &&nodeValue);

            void removeNode(NodeValueType_ &nodeValue);

            void removeNode(NodeValueType_ &&nodeValue);


            void addEdge(typename std::add_lvalue_reference<NodeValueType_>::type node1,
                    typename std::add_lvalue_reference<NodeValueType_>::type node2, EdgeType_ edgeValue);

            void addEdge(typename std::add_rvalue_reference<NodeValueType_>::type node1,
                    typename std::add_rvalue_reference<NodeValueType_>::type node2, EdgeType_ edgeValue);

            void removeEdge(NodeValueType_ &node1, NodeValueType_ &node2);

            void removeEdges(EdgeType_ edgeValue);

            size_t size() const;


            /**********/

            bool areSameCC(const NodeValueType_ &node1, const NodeValueType_ &node2) const;


            // TODO : déplacer ?
            const std::unordered_set<NodeValueType_> &getNearNodes(const NodeValueType_ &node1, std::function<bool(EdgeType_)> pred) const;


            Path<NodeValueType_, EdgeType_> getBestPath(const NodeValueType_ &node1, const NodeValueType_ &node2, std::function<bool(EdgeType_)> pred) const;

            Path<NodeValueType_, EdgeType_> getBestPath(const NodeValueType_ &node1, const NodeValueType_ &node2) const;


            std::vector<arccos::structs::Path<NodeValueType_, EdgeType_>> getBestPathes(const NodeValueType_& node1, const NodeValueType_& node2) const;

            friend std::ostream &operator<<(std::ostream &os, const Graph<NodeValueType_, EdgeType_> &graph) {
                os << "{[graph] ";
                for (auto it = graph.edges_.begin(); it != graph.edges_.end(); it++) {
                    os << it->first << " => " << it->second << ", ";
                }
                os << "}" << std::endl;
                return os;
            }

        };
    }
}




#include "../../tpl/structs/graph.cpp"
#include "../../tpl/structs/node.cpp"
#include "../../tpl/structs/recpath.cpp"
#include "../../tpl/structs/nodeset.cpp"
#include "../../tpl/structs/path.cpp"

#endif // ARCCOS_STRUCTS_GRAPH_H


// IMPLEMENTATION ZONE



