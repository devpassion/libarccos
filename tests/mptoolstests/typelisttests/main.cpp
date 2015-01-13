#include <cppunit/ui/text/TestRunner.h>
#include "typelisttest.h"

using namespace arccos;


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( TypelistTest::suite() );

    bool fail = runner.run();

    return !fail;
}
