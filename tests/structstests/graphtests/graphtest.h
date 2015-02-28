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

#ifndef ARCCOS_GRAPHTEST_H
#define ARCCOS_GRAPHTEST_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>

#include "arccos/structs/graph.h"


namespace arccos
{
    namespace structs
    {
        
        
        class GraphTest : public CppUnit::TestFixture
        {
        public:
            static CppUnit::TestSuite* suite();

            template<typename NodeValueType_, typename EdgeType_>
            void testPathes( const Graph<NodeValueType_, EdgeType_>& g, NodeValueType_ begin, NodeValueType_ end, unsigned int waitedPathCount );
            void testgraph();
            void testgraphCycles();
        };
    }
}
#endif // ARCCOS_TYPELISTTEST_H
