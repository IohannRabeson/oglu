# Unit tests directory

This is the sub project dedicated to unit testing of Oglu.  
You can new tests suites by adding a cpp file in `./src`.  
Append the new path file to the CMakeLists.txt in this folder.

## How to add a new test

First add your C++ source file in folder /tests/src/.
<code>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( buffer )

BOOST_AUTO_TEST_CASE( init_read )
{

}

BOOST_AUTO_TEST_SUITE_END()
</code>

Then add it to the CMakeLists.txt.  
The variable SRC_TEST list the cpp for each test program. This file is compiled then linked to a generic main. Finally, they are an executable for each C++ file in the SRC_TEST list.
<code>
# Put here your hpp and cpp of tests
set(SRC_TEST
	${SRC_DIR}/TestBuffer.cpp
)
</code>

To run tests:
<code>
	$> make && ctest
</code>
