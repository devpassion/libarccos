#include <cppunit/ui/text/TestRunner.h>
#include "graphtest.h"

using namespace arccos::structs;


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( GraphTest::suite() );

    bool fail = runner.run();

    return !fail;
}
