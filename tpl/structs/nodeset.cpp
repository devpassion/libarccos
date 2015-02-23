#include <stddef.h>
#include <algorithm>
#include <cmath>

#include "structs/node.h"
#include "structs/nodeset.h"
#include "structs/graph.h"

#include "logging/metalogging.h"

using namespace arccos::structs;


    template<typename NodeValueType_, typename EdgeType_>
    NodeSet<NodeValueType_, EdgeType_>::NodeSet( const Graph<NodeValueType_, EdgeType_>* graph ) : graph_(graph)
    {
        
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    NodeSet<NodeValueType_, EdgeType_>::NodeSet( const Graph<NodeValueType_, EdgeType_>* graph,
                 const std::unordered_map<NodeValueType_, arccos::structs::Node<NodeValueType_, EdgeType_>>& nodes) : graph_(graph)
    {
        for( auto it = nodes.begin(); it != nodes.end(); it++ )
        {
            parentSet::insert( &(it->second) );
        }
    }
    
    /*template<typename NodeValueType_, typename EdgeType_>
    NodeSet<NodeValueType_, EdgeType_>::NodeSet(const NodeSet& other) : 
                            std::unordered_set<Node<NodeValueType_, EdgeType_>>( 
                                static_cast<std::unordered_set<Node<NodeValueType_, EdgeType_>>>( other )  
                            ), graph_(other.graph_)
    {
    }*/
        
    
    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::add ( const NodeValueType_& nodeValue )
    {
        return parentSet::insert( &graph_->nodes_.at( nodeValue ) ).second;
    }


    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::add ( const Node< NodeValueType_, EdgeType_ >* node )
    {
        return parentSet::insert( node ).second;
    }

    template<typename NodeValueType_, typename EdgeType_>
    const Node<NodeValueType_, EdgeType_>* NodeSet<NodeValueType_, EdgeType_>::getNode( const NodeValueType_& nodeValue ) const
    {
        return *(std::find_if(
                parentSet::begin(), parentSet::end(), [&nodeValue] (const Node<NodeValueType_, EdgeType_>& node0)
        {
            return
                    node0 == nodeValue;
        } ));
    };
    
    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::add ( const NodeSet<NodeValueType_, EdgeType_>& other )
    {
        bool ret = false;
        for( auto it = other.begin(); it != other.end(); it++ )
        {
            ret |= add( it );
        }
        return ret;
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::add ( const Node< NodeValueType_, EdgeType_ >& node )
    {
        return parentSet::insert( &node ).second;
    }


    
    
    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::addNeighbours()
    {
        size_t prevSize = parentSet::size();
        
        NodeSet<NodeValueType_, EdgeType_> toAdd( graph_ );
        
        for( auto it = parentSet::cbegin();it != parentSet::cend();it++ )
        {
            arccos::Logger::trace( __func__, "node is ", (*it)->getValue() , "" );
            
            for( auto it0 = (*it)->getNeigthbours(); it0 != (*it)->neigthboursEnd(); it0++ )
            {
                toAdd.add( *it0 );
            }
            arccos::Logger::trace( __func__,  "toAdd.size() == ", toAdd.size() );
        }
        
        arccos::Logger::trace( "Add ", toAdd.size(), " nodes" );
        parentSet::insert( toAdd.cbegin(), toAdd.cend() );
        return prevSize != parentSet::size();
    }
    
    /*template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::addNeighbours( NodeSet& toRemove)
    {
        size_t prevSize = size();
        NodeSet<NodeValueType_, EdgeType_> toAdd( graph_ );
        for( auto it = parentSet::cbegin();it != parentSet::cend();it++ )
        {
            arccos::Logger::trace( "node is ", (*it)->value_->getPosition() , "" );
            const NodeSet<NodeValueType_, EdgeType_>& toAdd0 = (*it)->getNeigthbours();
            toAdd.add( toAdd0 );
            arccos::Logger::trace( "toAdd.size() == ", toAdd.size() );
        }
        arccos::Logger::trace( "Add ", toAdd.size(), " nodes" );
        parentSet::insert( toAdd.cbegin(), toAdd.cend() );
        toRemove.remove( toAdd );
        return prevSize != parentSet::size();
    }*/
    
    
    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::addNeighbours( std::function<void(const Node<NodeValueType_, EdgeType_>*)> functor )
    {
        // TODO : forte redondance du passage de la fonction, ajouter un paramètre spécifiant les noeuds visités?
        size_t prevSize = parentSet::size();

        NodeSet<NodeValueType_, EdgeType_> toAdd( graph_ );

        for( auto it = parentSet::cbegin();it != parentSet::cend();it++ )
        {
//            arccos::Logger::trace( "node is ", (*it)->getValue() , "" );
            
            for( auto it0 = (*it)->getNeigthbours(); it0 != (*it)->neigthboursEnd(); it0++ )
            {
                toAdd.add( *it0 );
                functor( *it0 );
            }
//            arccos::Logger::trace( "toAdd.size() == ", toAdd.size() );
        }
        
//        arccos::Logger::trace( "Add ", toAdd.size(), " nodes" );
        parentSet::insert( toAdd.cbegin(), toAdd.cend() );
        return prevSize != parentSet::size();
    }
    

    template<typename NodeValueType_, typename EdgeType_>    
    size_t NodeSet<NodeValueType_, EdgeType_>::size() const
    {
        return parentSet::size();
    }

    template<typename NodeValueType_, typename EdgeType_>    
    const Node< NodeValueType_, EdgeType_ >* NodeSet<NodeValueType_, EdgeType_>::getFirstNode() const
    {
        auto it = parentSet::cbegin();
        return *it;
    }

    /*
    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::add( const NodeSet<NodeValueType_, EdgeType_>& other )
    {
        size_t prevSize = size();
        parentSet::insert( other.cbegin(), other.cend() );
        return parentSet::size() != prevSize;
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    bool NodeSet<NodeValueType_, EdgeType_>::add( const Node<NodeValueType_, EdgeType_>& node )
    {
        // WARNING : ici le noeud est peut ^etre bient^ot détruit
        size_t prevSize = size();
        //TODO sureté de d'identité
        parentSet::insert( &node );
        return parentSet::size() != prevSize;
    }
    
    */
    
    
    template<typename NodeValueType_, typename EdgeType_>
    void NodeSet<NodeValueType_, EdgeType_>::remove( const NodeSet<NodeValueType_, EdgeType_>& other )
    {
        parentSet::erase( other.cbegin(), other.cend() );
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    void NodeSet<NodeValueType_, EdgeType_>::remove( const Node<NodeValueType_, EdgeType_>& node )
    {
        parentSet::erase( &node );
    }


