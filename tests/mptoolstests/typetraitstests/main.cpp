#include <cppunit/ui/text/TestRunner.h>
#include "typetraitstest.h"

using namespace arccos;


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( TypetraitsTest::suite() );

    bool fail = runner.run();

    return !fail;
}
