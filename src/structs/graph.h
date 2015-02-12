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

#ifndef ARCCOS_STRUCTS_GRAPH_H
#define ARCCOS_STRUCTS_GRAPH_H

#include <utility>
#include <set>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>


namespace arccos 
{
    namespace structs 
    {
        /**
         * real Pair {a,b} (no sorted) 
         **/
        template<typename T>
        struct nsPair
        {
            std::set<T> p_;
        public:
            nsPair( T v1, T v2 ) 
            { 
                p_.insert( v1 );
                p_.insert( v2 );
            };
            
            nsPair( T&& v1, T&& v2 ) 
            { 
                p_.insert( v1 );
                p_.insert( v2 );
                
            };
            
            nsPair( const nsPair<T>& other ) : p_(other.p_) { }
            
            nsPair( const nsPair<T>&& other ) : p_(other.p_) { }
            
            nsPair<T>& operator=( const nsPair<T> other ) = delete;
/*            {
                nsPair tmp(other);
                std::swap( *this, other );
                return *this;
            };*/
            
            bool operator==(const nsPair<T>& other) const
            {
                return (p_ == other.p_ );
            };
            
            
            bool operator<( const nsPair<T>& other ) const
            {
                auto it = p_.begin();
                auto ito = other.p_.begin();
                if( *it < *ito ) return true;
                if( *it == *ito )
                {
                    it++;ito++;
                    return ( *it < *ito );
                }
                return false; 
            }
        };
        
        template<typename NodeType_, typename EdgeType_>
        class Graph;
        
        template<typename NodeType_, typename EdgeType_>
        class Path
        {
            // TODO : best ref type here ?
            std::vector<const NodeType_&> nodes_;
            const Graph<NodeType_, EdgeType_>& graph_;
            
        public:
            Path( const Graph<NodeType_, EdgeType_>& graph) : graph_(graph) {}
            
            Path( const Path&& other ) : graph_(other.graph_), nodes_(std::move(other.nodes_) ) { }
            
            void addNode( const NodeType_& node ) 
            { 
                nodes_.push_back( node );
            }
            
            typename std::vector<const NodeType_&>::const_iterator operator&&( const Path& other ) const
            {
                return std::set_intersection( nodes_, other.nodes_ );
            }
        };
        
        template<typename NodeType_, typename EdgeType_>
        class Graph
        {
            std::set<NodeType_> nodes_;
            
            std::map<NodeType_,std::set<NodeType_>> edges_;
            
            std::map<nsPair<NodeType_>,EdgeType_> edgesTypes_;
            
            friend Path<NodeType_, EdgeType_>;
            
        public:
            
            using PathType = Path<NodeType_, EdgeType_>;
            
            using NodeType = NodeType_;
            using EdgeType = EdgeType_;
            
            Graph() {}
            Graph(const Graph& other) = delete;
            ~Graph() {}
            Graph& operator=(const Graph& other) = delete;
            bool operator==(const Graph& other) const = delete;
            
            void addNode( NodeType_& node )
            {
                nodes_.insert( node );
                edges_[node] = {};
            }
            void addNode( NodeType_&& node )
            {
                nodes_.insert( node );
                edges_[node] = {};
            }
            
            void removeNode( NodeType_& node );
            void removeNode( NodeType_&& node );
            
            
            void addEdge( NodeType_& node1, NodeType_& node2, EdgeType edgeValue )
            {
                edges_[node1].insert( node2 );
                edges_[node2].insert( node1 );
                edgesTypes_.emplace( std::make_pair( nsPair<NodeType>( node1, node2 ), edgeValue ) );
               
            }
            
            void addEdge( NodeType_&& node1, NodeType_&& node2, EdgeType edgeValue )
            {
                edges_[node1].insert( node2 );
                edges_[node2].insert( node1 );
                edgesTypes_.emplace( std::make_pair( nsPair<NodeType>( node1, node2 ), edgeValue ) );
            }
            
            void removeEdge( NodeType_& node1, NodeType_& node2 )
            {
                edges_[node1].erase( node2 );
                edges_[node2].erase( node1 );
            }
            
            void removeEdges(  EdgeType edgeValue );
            
            const std::set<NodeType_>& getNearNodes( const NodeType_& node1,  std::function<bool(EdgeType_)> pred ) const
            {
                return edges_[node1]; 
            }
           
            
            typename std::add_rvalue_reference<PathType>::type getBestPath( const NodeType_& node1, const NodeType_& node2, std::function<bool(EdgeType_)> pred ) const
            {
                
            }
            
        };
    }
    
}

#endif // ARCCOS_STRUCTS_GRAPH_H
