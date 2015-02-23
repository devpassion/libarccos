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

#ifndef ARCCOS_NODESET_H
#define ARCCOS_NODESET_H


#include <type_traits>
#include <unordered_set>
#include <stddef.h>
#include <functional>
#include <utility>
#include <unordered_map>


#include "graph_trait.h"
#include "node.h"
#include "graph.h"

namespace std
{
    template<typename NodeValueType_>
    struct hash<std::pair<NodeValueType_, NodeValueType_>>
    {
        size_t operator()(const std::pair<NodeValueType_, NodeValueType_> &p) const noexcept
        {
            return (std::get<0>(p) * 9) + std::get<0>(p);
        }
    };
}

namespace arccos
{

    namespace structs
    {
        template<typename NodeValueType_, typename EdgeType_>
        class NodeSet : std::unordered_set<const Node<NodeValueType_, EdgeType_> *>
        {
            using parentSet = std::unordered_set<const Node<NodeValueType_, EdgeType_> *>;

            const Graph<NodeValueType_, EdgeType_> *graph_;

            friend Graph<NodeValueType_, EdgeType_>;
            friend Node<NodeValueType_, EdgeType_>;


            NodeSet(const Graph <NodeValueType_, EdgeType_> *graph,
                    const std::unordered_map <NodeValueType_, arccos::structs::Node<NodeValueType_, EdgeType_>> &nodes);

        public:

            NodeSet(const Graph <NodeValueType_, EdgeType_> *graph);

            using NodeType = Node <NodeValueType_, EdgeType_>;

            NodeSet(const NodeSet &other) = delete;

            NodeSet(const NodeSet &&other);

            /**
            * Ajoute les voisins de chaque noeud,
            * Renvoie vrai si un noeud a été nombre de noeuds ajoutés
            **/
            bool addNeighbours();

            /**
            *
            * toRemove : set de noeud dont les noeuds voisins ajoutés seront supprimés
            **/
            bool addNeighbours(NodeSet &toRemove);

            /**
            * Applique un foncteur à chaque noeud ajouté
            **/
            bool addNeighbours(std::function<void(const Node <NodeValueType_, EdgeType_> *)> functor);

            /**
            * Récupère un noeud quelquonque
            **/
            const Node <NodeValueType_, EdgeType_> *getFirstNode() const;

            /**
            * Récupère le noeud posédant la valeur demandée
            **/
            const Node <NodeValueType_, EdgeType_> *getNode(const NodeValueType_ &nodeValue) const;


            using const_iterator = typename parentSet::const_iterator;

            /**
            * Itérateur
            **/
            typename parentSet::const_iterator begin() const
            {
                return parentSet::begin();
            }

            typename parentSet::const_iterator end() const
            {
                return parentSet::end();
            }


            // bool contains( std::add_rvalue_reference<NodeType>::type node  );
            /**
            * ndique si le set contient ce noeud
            **/
            bool contains(const NodeValueType_ &nodeValue);


            bool add(const NodeSet<NodeValueType_, EdgeType_> &other);

            bool add(const Node <NodeValueType_, EdgeType_> &node);

            bool add(const Node <NodeValueType_, EdgeType_> *node);

            bool add(const NodeValueType_ &nodeValue);

            void remove(const NodeSet<NodeValueType_, EdgeType_> &other);

            void remove(const Node <NodeValueType_, EdgeType_> &other);

            void remove(const NodeValueType_ &nodeValue);


            size_t size() const;

            ~NodeSet()
            {
            }

            NodeSet &operator=(const NodeSet &other) = delete;

            bool operator==(const NodeSet &other) const;

            friend std::ostream &operator<<(std::ostream &os, const NodeSet<NodeValueType_, EdgeType_> &nodeSet)
            {
                os << "{[nodeset]:";
                for (auto it = nodeSet.begin(); it != nodeSet.end(); it++)
                {
                    os << (*it)->getValue() << ", ";
                }
                os << "}" << std::endl;
                return os;
            }
        };
    }
}


#endif // ARCCOS_STRUCTS_NODESET_H
