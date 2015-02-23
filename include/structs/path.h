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

#ifndef ARCCOS_PATH_H
#define ARCCOS_PATH_H

#include <type_traits>
#include <vector>
#include <ext/new_allocator.h>

#include "node.h"
#include "recpath.h"

namespace arccos
{
    namespace structs
    {
        template<typename NodeValueType_, typename EdgeType_>
        class Graph;

        template<typename NodeValueType_, typename EdgeType_>
        class Path
        {

            const Graph<NodeValueType_, EdgeType_> *graph_;

            std::vector<const Node<NodeValueType_, EdgeType_> *> nodes_;

            friend Graph<NodeValueType_, EdgeType_>;
            friend __gnu_cxx::new_allocator<Path<NodeValueType_, EdgeType_>>;

            Path(const Graph <NodeValueType_, EdgeType_> *graph) : graph_(graph)
            {
            }

            Path(const Graph <NodeValueType_, EdgeType_> *graph, const Node<NodeValueType_, EdgeType_> *node)
                    : graph_(graph), nodes_{node}
            {
            }


        public:


            Path(const Graph <NodeValueType_, EdgeType_> *graph,
                    const std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>> beginPath,
                    const std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>>
                    endPath
            ) :
                    graph_(graph)
            {
                arccos::Logger::debug(" Path, ctr...");

                std::vector<const Node<NodeValueType_, EdgeType_> *> toReverse;

                for (auto it = beginPath; it; it = it->getTail())
                {
                    arccos::Logger::trace("it->size == ", it->size());
                    arccos::Logger::debug("\t it == ", it->getHead()->getValue());
                    toReverse.push_back(it->getHead());

                    arccos::Logger::trace("loopend ");
                }

                nodes_.assign(toReverse.rbegin(), toReverse.rend());

                for (auto it = endPath->getTail(); it; it = it->getTail())
                {
                    nodes_.push_back(it->getHead());
                }
                arccos::Logger::debug(" Path, ctr... OK");
            }



            Path(const Path &&other) : graph_(other.graph_), nodes_(std::move(other.nodes_))
            {
                // TODO: graph assignation
            }

            size_t size() const
            {
                return nodes_.size();
            }

            void addNode(const NodeValueType_ &node)
            {
                nodes_.emplace_back(graph_, node);
            }

            bool contains(const NodeValueType_ &node) const;


            friend std::ostream& operator<<(std::ostream& os, const Path<NodeValueType_, EdgeType_>& path)
            {
                os << "{[Path] (" << path.nodes_.size() << " nodes): ";
                for (auto it = path.nodes_.begin(); it != path.nodes_.end(); it++)
                {
                    os << (*it)->getValue() << ", ";
                }
                return os << std::endl;
            }

        };
    }
}


#endif