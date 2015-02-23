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

#include "graphtest.h"
#include <cppunit/TestCaller.h>

#include "structs/graph.h"

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

    g.updateCC();

    std::vector<Path<int, char>> pathes = g.getBestPathes(1, 5);

    for (auto it = pathes.begin(); it != pathes.end(); it++)
    {
        std::cout << *it << std::endl;
    }


}


CppUnit::TestSuite *GraphTest::suite()
{
    CppUnit::TestSuite *suite = new CppUnit::TestSuite("GraphTest");
    suite->addTest(new CppUnit::TestCaller<GraphTest>("testGraph", &GraphTest::testgraph));
    return suite;
}
