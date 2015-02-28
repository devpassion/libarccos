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

#include <vector>
#include <chrono>
#include "graphtest.h"
#include <cppunit/TestCaller.h>

#include "arccos/structs/graph.h"

using namespace arccos::structs;


void GraphTest::testgraph()
{
    Graph<int, char> g;
    for (int i = 0; i < 10; i++)
    {
        g.addNode(i);
    }
    g.addEdge(1, 2, 'c');
    g.addEdge(1, 3, 'b');
    g.addEdge(2, 3, 'b');
    g.addEdge(3, 4, 'b');
    g.addEdge(4, 5, 'b');

    g.addEdge(4, 2, 'd');
    g.addEdge(5, 7, 'e');
    g.addEdge(7, 8, 'f');
    g.addEdge(0, 9, 'g');

    std::cout << g << std::endl;

    g.updateCC();

    // TODO : tiome of execution
    //auto start = std::chrono::steady_clock::now();

    std::vector<Path<int, char>> pathes = g.getBestPathes(1, 5);

    //auto end = std::chrono::steady_clock::now();

    CPPUNIT_ASSERT( pathes.size() == 2);

    //std::cout << "time : " << (end - start) << std::endl;

    for (auto it = pathes.begin(); it != pathes.end(); it++)
    {
        std::cout << *it << std::endl;
    }


}


void GraphTest::testgraphCycles()
{
    Graph<int, char> g;
    for (int i = 0; i <= 6; i++)
    {
        g.addNode(i);
    }
    g.addEdge(1, 2, 'c');
    g.addEdge(1, 3, 'b');
    g.addEdge(3, 3, 'b');
    g.addEdge(3, 4, 'b');
    g.addEdge(4, 5, 'b');
    g.addEdge(5, 1, 'b');
    g.addEdge(4, 2, 'b');
    g.addEdge(4, 4, 'b');


    std::cout << g << std::endl;

    g.updateCC();

    // TODO : tiome of execution
    //auto start = std::chrono::steady_clock::now();


    testPathes(g, 1, 4, 3);
    testPathes(g, 0, 4, 0);
    testPathes(g, 0, 6, 0);
    testPathes(g, 3, 3, 1);

    testPathes(g, 2, 3, 2);

}

template<typename NodeValueType_, typename EdgeType_>
void GraphTest::testPathes( const Graph<NodeValueType_, EdgeType_>& g, NodeValueType_ begin, NodeValueType_ end, unsigned int waitedPathCount)
{
    std::cout << "Test best path from " << begin << " to " << end << std::endl;

    std::vector<Path<NodeValueType_, EdgeType_>> pathes = g.getBestPathes(begin, end);

    for (auto it = pathes.begin(); it != pathes.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    CPPUNIT_ASSERT( pathes.size() == waitedPathCount);
}

CppUnit::TestSuite *GraphTest::suite()
{
    CppUnit::TestSuite *suite = new CppUnit::TestSuite("GraphTest");
    suite->addTest(new CppUnit::TestCaller<GraphTest>("testGraph", &GraphTest::testgraph));
    suite->addTest(new CppUnit::TestCaller<GraphTest>("testGraphCycles", &GraphTest::testgraphCycles));
    return suite;
}
