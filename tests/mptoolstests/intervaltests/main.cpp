#include <cppunit/ui/text/TestRunner.h>
#include "intervaltest.h"

using namespace arccos::mptools;


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( IntervalTestFixture::suite() );

    bool fail = runner.run();

    return !fail;
}
