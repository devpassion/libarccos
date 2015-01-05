#include <cppunit/ui/text/TestRunner.h>
#include "loggingtest.h"

using namespace arccos;


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( LoggingTest::suite() );

    bool fail = runner.run();

    return !fail;
}
