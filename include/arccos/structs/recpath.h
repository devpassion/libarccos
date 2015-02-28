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

#ifndef ARCCOS_RECPATH_H
#define ARCCOS_RECPATH_H

#include <cassert>
#include <vector>
#include "node.h"
#include <iterator>
#include <memory>

namespace arccos
{
    namespace structs
    {
        template<typename NodeValueType_, typename EdgeType_>
        class RecPath // : std::enable_shared_from_this<RecPath<NodeValueType_, EdgeType_>>
        {
            const std::shared_ptr<const RecPath> tail_;
            const Node<NodeValueType_, EdgeType_> *const head_;

            const RecPath *const base_;

            const size_t size_;


        public:

            RecPath(const Node<NodeValueType_, EdgeType_> *head) :
                    tail_(nullptr), head_(head), base_(this), size_(1)
            {
                arccos::Logger::trace("RecPath == ", this);
                arccos::Logger::trace("\tRecPath, head == ", head->getValue());
            }


            RecPath(std::shared_ptr<const RecPath> tail, const Node<NodeValueType_, EdgeType_> *head)
                    : tail_(tail),
                      head_(head),
                      base_(tail->base_),
                      size_(tail->size_ + 1)
            {
                assert(tail_->size_ == size_ - 1);

                arccos::Logger::trace("RecPath == ", this);
                arccos::Logger::trace("\tRecPath, head == ", head->getValue());
                arccos::Logger::trace("\tRecPath, tail_ == ", tail_);
            }


            RecPath(const RecPath &other) = delete;

            RecPath(RecPath &&other)
                    : tail_(other.tail_),
                      head_(other.head_),
                      base_(other.base_),
                      size_(other.size_)
            {
                assert(tail_->size_ == size_ - 1);
            }

            ~RecPath()
            {
                arccos::Logger::trace("RecPath::~DTOR == ", this);

            }

            RecPath &operator=(const RecPath &other)
            {
                RecPath tmp(other);
                std::swap(tmp, other);
                return *this;
            }

            bool operator!=(const RecPath &other) const
            {
                return head_ != other.head_ || (tail_ != other.tail_);
            }

            bool operator==(const RecPath &other) const
            {
                return !(operator==(other));
            }


            bool contains(const NodeValueType_ &value) const
            {
                Logger::warning("WARN : contains method is linear and not optimized");

                if (size() == 0 || tail_ == nullptr)
                {
                    arccos::Logger::trace("\t\tcontains, size == ", size(), " and  tail_ == ", tail_);

                    return false;
                }
                arccos::Logger::trace("\t\tcontains, compare ", *value, " and ", *(head_->getValue()));

                assert(tail_ != nullptr);
                return (head_->getValue()) == value || tail_->contains(value);
            }


            // TODO : faut il paramétrer avec le type de gestion des noeuds ?
            const Node<NodeValueType_, EdgeType_> *getHead() const
            {
                return head_;
            }

            const std::shared_ptr<const RecPath> getTail() const
            {
                return tail_;
            }

            bool hasTail() const
            {
                return size_ > 1;
            }


            size_t size() const
            {
                return size_;
            }

/*        RecPath<NodeValueType_, EdgeType_>::iterator<false> cbegin() const
        {
            return iterator<false>( std::enable_shared_from_this<RecPath<NodeValueType_, EdgeType_>>::shared_from_this() );
        }
        
        RecPath<NodeValueType_, EdgeType_>::iterator<false> cend() const
        {
            return iterator<false>(  );
        }
        
        RecPath<NodeValueType_, EdgeType_>::iterator<true> crbegin() const
        {
            return iterator<true>(  std::enable_shared_from_this<RecPath<NodeValueType_, EdgeType_>>::shared_from_this() );
        }
        
        RecPath<NodeValueType_, EdgeType_>::iterator<true> crend() const
        {
            return iterator<true>(  );
        }*/

            void addNextPathes(std::vector<RecPath<NodeValueType_, EdgeType_>> &ret) const;

            std::vector<RecPath<NodeValueType_, EdgeType_>> getNextPathes(std::function<bool(Node<NodeValueType_, EdgeType_> &)> predicate) const;

            friend std::ostream &operator<<(std::ostream &os, const RecPath<NodeValueType_, EdgeType_> &recPath)
            {
                os << "{[RecPath (size == " << recPath.size() << ", id == " << recPath.id_ << ", reverse)]:";

                if (recPath.head_ != nullptr && recPath.tail_ != nullptr)
                    os << "HEAD == " << recPath.head_->getValue() << ", tail.size ==" << recPath.tail_->size();
                else os << "no TAIL";
                //const RecPath<NodeValueType_, EdgeType_>* p = &recPath;
/*            int s = recPath.size_;
            for( auto it = recPath.crbegin(); it != recPath.crend();++it )
            {
                assert( s-- > -3);
                os << (*it)->getValue() << ", ";
            }*/
                return os << "}" << std::flush;
            }

        };
    }
}

#endif // ARCCOS_RECPATH_H



//         template<bool reverse = false, bool end = false>
//         class iterator : public std::iterator<std::input_iterator_tag, Node<NodeValueType_, EdgeType_>>
//         {
//              const std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>> path_;
//              const std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>> current_;
// 
//         public:
//             
//             iterator( std::shared_ptr<const RecPath<NodeValueType_, EdgeType_>> path ) : path_(path), current_(path) 
//             {
//                 arccos::Logger::debug( "RecPath::iterator::iterator..." );
//                 arccos::Logger::debug( "RecPath::iterator::iterator, path.id == ", path.id_ );
//                 if( path_->tail_ != nullptr )
//                     assert( path_->tailid_ == path_->tail_->id_ );
//                 // WARNING : just for short path ! (ie greatescape)
//                 if( !reverse )
//                     current_ = path.base_;
//                     /*while( current_->tail_ != nullptr )
//                     {
//                         arccos::Logger::debug( "RecPath::iterator::iterator::current_ == ", current_ );
//                         arccos::Logger::debug( "RecPath::iterator::iterator::current_->tail_ == ", current_->tail_ );
//                         current_ = current_->tail_;
//                     }*/
//             }
//             
//             
//             iterator(  ) : path_(nullptr), current_( nullptr) { }
//             
//             template<bool R = reverse>
//             typename std::enable_if<R, const iterator&>::type operator++()
//             {
//                 if( path_->tail_ )
//                     assert( path_->tailid_ == path_->tail_->id_ );
//                 arccos::Logger::debug("RecPath::iterator::operator++<reverse>");
//                 current_ = current_->tail_;
//                 return *this;
//             }
//             
//             template<bool R = reverse>
//             typename std::enable_if<!R, const iterator&>::type operator++()
//             {
//                 arccos::Logger::debug("RecPath::iterator::operator++<!reverse>");
//                 arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, current_->id_ == ", current_->id_);
//                 if( current_ == path_ ) 
//                 {
//                     current_ = nullptr;
//                     return *this;
//                 }
//                 std::shared_ptr<const RecPath> p = path_;
//                 if( path_->tail_ )
//                     assert( path_->tailid_ == path_->tail_->id_ );
//                 arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, path_ == ", path_);
//                     arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, path_->id_ == ", path_->id_);       
//                                         arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, path_->tailid_ == ", path_->tailid_);       
//                     //arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, path_->tail_ == ", path_->tail_->id_);
//                     
//                 assert( p );
//                 size_t s = path_->size();
//                 while( p && p->tail_ != current_ )
//                 {
//                     assert( s-- > 0);
//                     arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, p == ", p);
//                     arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, p->id_ == ", p->id_);       
//                                         arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, p->tailid_ == ", p->tailid_);       
//                     //arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, p->tail_ == ", p->tail_->id_);
//                     arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, in while");
//                     arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, p->tail_ == ", p->tail_);
//                     //arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, p->tail_->size_ == ", p->tail_->size_);
//                     arccos::Logger::trace("RecPath::iterator::operator++<!reverse>, p->size_ == ", p->size_);
//                     
//                     //assert( p->tail_ != p );
//                     
//                     
//                     //assert( p->tail_->size_ == p->size() - 1 );
//                     p = p->tail_;
//                     assert( p || nullptr == current_ );
//                 }
//                 current_ = p;
//                 return *this;
//             }
//             
//             const Node<NodeValueType_, EdgeType_>& operator*() const
//             {
//                 if( path_->tail_ )
//                     assert( path_->tailid_ == path_->tail_->id_ );
//                 return *(current_->head_);
//             }
//             
//             /*const Node<NodeValueType_, EdgeType_>* operator->() const
//             {
//                 return current_->head_;
//             }*/
//             
//             template<bool R = reverse>
//             typename std::enable_if<!R, bool>::type operator!=(const iterator& other) const
//             {
//                 if( path_->tail_ )
//                     assert( path_->tailid_ == path_->tail_->id_ );
//                 return current_ != other.current_;
//             }
//             
//             template<bool R = reverse>
//             typename std::enable_if<R, bool>::type operator!=(const iterator& other) const
//             {
//                 if( path_->tail_ )
//                     assert( path_->tailid_ == path_->tail_->id_ );
// 
//                 if( other.current_ == nullptr && current_ == nullptr )
//                 {
//                     return false;
//                 }
// 
//                 if( current_ != nullptr )
//                 {
//                     arccos::Logger::trace("RecPath::iterator::operator!=<reverse>, other.current_ == ", other.current_);
//                     arccos::Logger::trace("RecPath::iterator::operator!=<reverse>, current_.size_ == ", current_->size_);    
//                 }
//                 return current_ != other.current_;
//             }
//             
//             
//             bool operator==(const iterator& other) const
//             {
//                 if( path_->tail_ )
//                     assert( path_->tailid_ == path_->tail_->id_ );
//                 return !(operator!=(other));
//             }
//             
//             
//             
//         };