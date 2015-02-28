#include <exception>

#include "arccos/logging/metalogging.h"

#include "arccos/structs/graph.h"
#include "arccos/structs/recpath.h"
#include "arccos/structs/node.h"

using namespace arccos::structs;



    template<typename NodeValueType_, typename EdgeType_>
    NodeSet<NodeValueType_, EdgeType_> Graph<NodeValueType_, EdgeType_>::newNodeSet() const
    { 
        return NodeSet<NodeValueType_, EdgeType_>( this );
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    NodeSet<NodeValueType_, EdgeType_> Graph<NodeValueType_, EdgeType_>::allNodeSet() const
    { 
        // TODO : mettre en cache
        return NodeSet<NodeValueType_, EdgeType_>( this, nodes_ );
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    void Graph<NodeValueType_, EdgeType_>::addNode( const NodeValueType_& nodeValue )
    {
        nodes_.emplace( std::piecewise_construct, std::forward_as_tuple( nodeValue ), std::forward_as_tuple(this, nodeValue) );
        edges_.emplace( std::piecewise_construct, std::forward_as_tuple( nodeValue ), std::forward_as_tuple( this ) );

    }
    
    
    template<typename NodeValueType_, typename EdgeType_>
    void Graph<NodeValueType_, EdgeType_>::addNode( NodeValueType_&& nodeValue )
    {
        nodes_.emplace( std::piecewise_construct, std::forward_as_tuple( nodeValue ), std::forward_as_tuple(this, nodeValue) );
        edges_.emplace( std::piecewise_construct, std::forward_as_tuple( nodeValue ), std::forward_as_tuple( this ) );
    }
    
    
    
    template<typename NodeValueType_, typename EdgeType_>
    void Graph<NodeValueType_, EdgeType_>::addEdge( typename std::add_lvalue_reference<NodeValueType_>::type node1,
                                               typename std::add_lvalue_reference<NodeValueType_>::type node2, EdgeType_ edgeValue )
    {
        edges_.at(node1).add( node2 );
        edges_.at(node2).add( node1 );
        //edgesTypes_.emplace( std::make_pair( nsPair<NodeType>( node1, node2 ), edgeValue ) );
        // updateCC();
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    void Graph<NodeValueType_, EdgeType_>::addEdge( typename std::add_rvalue_reference<NodeValueType_>::type node1,
                                               typename std::add_rvalue_reference<NodeValueType_>::type node2, EdgeType_ edgeValue )
    {
        edges_.at(node1).add( std::move( node2 ) );
        edges_.at(node2).add( std::move( node1 ) );
        //edgesTypes_.emplace( std::make_pair( nsPair<NodeType>( node1, node2 ), edgeValue ) );
        // updateCC();
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    void Graph<NodeValueType_, EdgeType_>::removeEdge( NodeValueType_& node1, NodeValueType_& node2 )
    {
        edges_[node1].remove( node2 );
        edges_[node2].remove( node1 );
        //updateCC();
    }
    
    
    template<typename NodeValueType_, typename EdgeType_>
    const std::unordered_set<NodeValueType_>& Graph<NodeValueType_, EdgeType_>::getNearNodes( const NodeValueType_& node1,  std::function<bool(EdgeType_)> pred ) const
    {
        return edges_.at(node1); 
    }
    
    
    template<typename NodeValueType_, typename EdgeType_>
    size_t Graph<NodeValueType_, EdgeType_>::size() const
    {
        return nodes_.size();
    }
    
    
    
    template<typename NodeValueType_, typename EdgeType_>
    void Graph<NodeValueType_, EdgeType_>::updateCC() const
    {
        // arccos::Logger::trace( "updateCC" );
        NodeSet<NodeValueType_, EdgeType_> an = allNodeSet();
        int color = 0;
        // arccos::Logger::trace( "before while" );
        while( an.size() != 0 )
        {
            NodeSet<NodeValueType_, EdgeType_> ns( this );
            const Node<NodeValueType_, EdgeType_>* aNode = an.getFirstNode();
            arccos::Logger::trace( "updateCC while, an.size() ==", an.size(), ", aNode == ", aNode->getValue() );

            this->connexesComposants_[ aNode->getValue()] = color;
            ns.add( *aNode );
            an.remove( *aNode );
            while(
            ns.addNeighbours( [&an,this, color] ( const Node<NodeValueType_, EdgeType_>* node )
            {
                arccos::Logger::trace( "updateCC lambda, ", node->getValue(), " ==> color(",color,")"  );
                this->connexesComposants_[ node->getValue()] = color;
                an.remove( *node );
                arccos::Logger::trace("remove ", node->getValue() ," ,( an.size() ==", an.size(), " )");
            } ) );
            color++;
            
        }
    }


    template<typename NodeValueType_, typename EdgeType_>
    bool Graph<NodeValueType_, EdgeType_>::areSameCC ( const NodeValueType_& node1, const NodeValueType_& node2 ) const
    {
        return connexesComposants_.at( node1 ) == connexesComposants_.at( node2 );
    }

    
    template<typename NodeValueType_, typename EdgeType_>
    std::vector<Path<NodeValueType_, EdgeType_>>
    Graph<NodeValueType_, EdgeType_>::getBestPathes( const NodeValueType_& node1, const NodeValueType_& node2 ) const
    {
        std::vector<Path<NodeValueType_, EdgeType_>> ret;
        if( !areSameCC( node1, node2 ) )
        {
            Logger::debug("Not same CC");
            return ret;
        }
        Logger::trace("Same CC");
        if( node1 == node2 )
        {
            Logger::trace("nodes are equals");
            // TODO : vérifier avant l'ajout qu'il existe un arc entre node1 et lui meme
            ret.emplace_back( this, &nodes_.at( node1 ) );
            return ret;
        }
        
        std::unordered_map<NodeValueType_, std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>>> leftMap;
        
        std::unordered_map<NodeValueType_, std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>>> rightMap;

        std::unordered_map<NodeValueType_, std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>>> newLeftMap;
        
        // TODO : make emplace

        std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>> a1( new RecPath<NodeValueType_, EdgeType_> ( &nodes_.at( node1 ) ) );
        leftMap.insert( std::make_pair( node1, a1 ));
        
        std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>> a2( new RecPath<NodeValueType_, EdgeType_> ( &nodes_.at( node2 ) ) );
        rightMap.insert( std::make_pair( node2, a2 ));
//        rightMap.emplace( std::make_pair( node2, new RecPath<NodeValueType_, EdgeType_> ( nodes_.at( node2 ) ) ) );
        

        
        std::unordered_set<const NodeValueType_*> visiteds;
        visiteds.insert( &node1 );
        visiteds.insert( &node2 );
        
        //std::vector<Graph<NodeValueType_, EdgeType_>::PathType> ret;
        while(  ret.size() == 0 && visiteds.size() < nodes_.size() )
        {

            std::unordered_set<const NodeValueType_*> lAddeds;
            std::unordered_set<const NodeValueType_*> rAddeds;

            balance( ret, leftMap, rightMap, visiteds, lAddeds, newLeftMap );
            visiteds.insert( rAddeds.begin(), rAddeds.end() );
            balance( ret, rightMap, leftMap, visiteds, rAddeds, newLeftMap );
            visiteds.insert( lAddeds.begin(), lAddeds.end() );
        }
        
        return ret;
    }
    
    template<typename NodeValueType_, typename EdgeType_>
    void Graph<NodeValueType_, EdgeType_>::balance( 
                    std::vector<Path<NodeValueType_, EdgeType_>>& ret,
                    std::unordered_map<NodeValueType_, std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>>>& leftMap, 
                    const std::unordered_map<NodeValueType_, std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>>>& rightMap,
                    std::unordered_set<const NodeValueType_*>& visiteds,
                    std::unordered_set<const NodeValueType_*>& addeds,
                    std::unordered_map<NodeValueType_, std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>>>& newLeftMap
                                                  ) const
    {
        newLeftMap.clear();
        arccos::Logger::debug( "Balance..." );
        // Itère sur les noeuds du set de gauche
        for( auto it = leftMap.begin(); it != leftMap.end(); it++ )
        {
            arccos::Logger::debug( "\tIterattion sur noeud gauche : ", (it->second) );

            /*std::vector<RecPath<NodeValueType_, EdgeType_>> bPathes;
            it->second->addNextPathes( bPathes );
            // pour chaque chemin suivant le noeud de gauche
            for( auto it0 = bPathes.begin();it0 != bPathes.end(); it0++)
            {*/
            
            // Pour chaque noeud suivant le noeud de gauche
            for( auto it0 = it->second->getHead()->getNeigthbours(); it0 != it->second->getHead()->neigthboursEnd(); it0++ )
            {
                const Node<NodeValueType_, EdgeType_>* const node = *it0;
                arccos::Logger::debug( "\tchemin suivant : ", *node );
                // si le noeud est visité, on ne le traite pas
                if( visiteds.count( &(node->getValue()) ) > 0 )
                {
                    arccos::Logger::debug( "\tnode is visited : ", *node );
                    continue;
                }
                arccos::Logger::debug( "\tnode is not visited : ", *node );
                // on l'ajoute aux noeuds
                addeds.insert( &(node->getValue()) );
                arccos::Logger::debug( "\t(added )" );
//                std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>> a( new RecPath<NodeValueType_, EdgeType_>( *it0 ) );
                std::shared_ptr<const RecPath<NodeValueType_,EdgeType_>> thisPath( new RecPath<NodeValueType_, EdgeType_>( it->second, node ) ) ;
//                auto thisPath = std::make_shared<const RecPath<NodeValueType_,EdgeType_>>(it->second, node);
                newLeftMap.insert( 
                    std::make_pair( node->getValue(), 
                                    thisPath ) );
                
                //assert( res.second );
/*                newLeftMap.emplace( std::piecewise_construct, 
                                    std::forward_as_tuple( it0->getHead()->getValue() ), 
                                    std::forward_as_tuple( *it0 ) );*/
                
                arccos::Logger::debug( "\tsearch path..." );
                // Si le set droit contient le noeud, on a trouvé un chemin
                arccos::Logger::debug( "\t(rightMap.size() == ", rightMap.size(), ")" );
                for( auto rit = rightMap.begin();rit != rightMap.end();rit++)
                {
                    arccos::Logger::debug( "\t\trigthmap contain ", rit->second->getHead()->getValue() );
                }
                
                auto f = rightMap.find( node->getValue() );
                
                if( f != rightMap.end() )
                {
                    arccos::Logger::debug( "\tfind path" );
                    ret.emplace_back( this, thisPath, (f->second) );
                    arccos::Logger::debug( "\templaced" );
                }
                arccos::Logger::trace( "\tnewLeftMap.size() == ", newLeftMap.size() );
                
            }
            
            
        }

        // La map de gauche devient le set visité
        leftMap.swap( newLeftMap );
        
        arccos::Logger::debug( "END balance" );    
    }

