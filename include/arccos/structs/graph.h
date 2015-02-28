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

        /**
        * Cette classe représente un graphe non orienté.
        *
        * Elle est adaptée aux graphes aux nombres restreints de noeuds (par exemple pour représenter les cases d'un
        * plateau de jeu) et optimisée pour la recherche rapide de chemin avec une mise à jour régulière (typiquement
        * un tour de jeu).
        *
        * \tparam NodeValueType_ type du noeud des graphes, stocké par valeur
        * \tparam EdgeType_ type des valeurs d'arcs
        */
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

            /**
            * Met à jour le cache des composantes connexes après une modification.
            */
            void updateCC() const;

            /**
            * Met à jour le cache des chemins
            *
            * Cette opération vérifie si un chemin présent dans le cache des chemins est obsolète.
            * TODO : doit elle etre const ? doit elle etre publique?
            */
            void updatePathCache() const;

            /**
            * Construit un graphe sans noeuds
            */
            Graph() {
            }


            Graph(const Graph &other) = delete;


            Graph(const Graph &&other);

            ~Graph() {
            }

            Graph &operator=(const Graph &other) = delete;

            bool operator==(const Graph &other) const = delete;

            /**
            * Récupère un Nodeset vide associé à ce graphe
            *
            */
            NodeSet<NodeValueType_, EdgeType_> newNodeSet() const;

            /**
            * Récupère le nodeset contenant tous les noeuds du graphe
            */
            NodeSet<NodeValueType_, EdgeType_> allNodeSet() const;


            /**
            * récupère le noeud dont la valeur est celle spécifiée
            * @param[in] nodeValue Valeur du noeud recherché
            * @throw out_of_range : levée si la valeur ne correspond pas à un noeud
            * TODO : ajouter une fonction de vérification d'existance
            */
            const Node <NodeValueType_, EdgeType_> &getNode(const NodeValueType_ &nodeValue) const
            {
                return nodes_.at(nodeValue);
            }


            /**
            * Ajoute un noeud au graphe. Sans effet si le noeud existe déjà.
            * @param nodeValue valeur du nouveau noeud.
            */
            void addNode(const NodeValueType_& nodeValue);

            /**
            * Ajoute un noeud au graphe. Sans effet si le noeud existe déjà.
            * @param nodeValue valeur du nouveau noeud.
            */
            void addNode(NodeValueType_&& nodeValue);

            /**
            * Supprime un noeud du graphe.
            * TODO : temps x^2
            */
            void removeNode(NodeValueType_& nodeValue);

            void removeNode(NodeValueType_&& nodeValue);


            /**
            * Ajoute un arc entre 2 noeuds
            */
            void addEdge(typename std::add_lvalue_reference<NodeValueType_>::type node1,
                    typename std::add_lvalue_reference<NodeValueType_>::type node2, EdgeType_ edgeValue);

            /**
            * Ajoute un arc entre 2 noeuds
            */
            void addEdge(typename std::add_rvalue_reference<NodeValueType_>::type node1,
                    typename std::add_rvalue_reference<NodeValueType_>::type node2, EdgeType_ edgeValue);

            /**
            * Supprime un arc
            */
            void removeEdge(NodeValueType_ &node1, NodeValueType_ &node2);

            /**
            * Supprime les arcs dont la valeur d'arc est celle spécifiée
            */
            void removeEdges(EdgeType_ edgeValue);

            /**
            * renvoie le nombre de noeuds du graphe
            */
            size_t size() const;


            /**********/

            /**
            * Indique si 2 noeuds font partie de la meme composante connexe
            */
            bool areSameCC(const NodeValueType_ &node1, const NodeValueType_ &node2) const;


            // TODO : déplacer ?
            const std::unordered_set<NodeValueType_> &getNearNodes(const NodeValueType_ &node1, std::function<bool(EdgeType_)> pred) const;


            Path<NodeValueType_, EdgeType_> getBestPath(const NodeValueType_ &node1, const NodeValueType_ &node2, std::function<bool(EdgeType_)> pred) const;

            Path<NodeValueType_, EdgeType_> getBestPath(const NodeValueType_ &node1, const NodeValueType_ &node2) const;


            /**
            * renvoie tous les chemins les plus courts entre 2 noeuds.
            * TODO : définir précisément le comportement
            */
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




#include "arccos/structs/graph.tpp"
#include "arccos/structs/node.tpp"
#include "arccos/structs/recpath.tpp"
#include "arccos/structs/nodeset.tpp"
#include "arccos/structs/path.tpp"

#endif // ARCCOS_STRUCTS_GRAPH_H


// IMPLEMENTATION ZONE



