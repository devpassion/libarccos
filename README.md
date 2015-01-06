libarccos
=========

### A little meta programming library


#### Features

* Hexadecimal dump for std::string, raw string and arbitrary types (based on memory layout)
* compile-time interval
    * create compile-time interval and apply meta operations to all elements
* compile-time logging
    * Define logging level at compile time ( non displayed logging informations does not produce asm code )

    
#### Prerequisites

* c++11 (for example, gcc-4.7)
* cmake
* ctest (if you want to execute the unit tests)

    
#### Installation 

This library just install some headers files in the include directory.

* $ git clone https://github.com/devpassion/libarccos
* $ cd libarccos
* $ mkdir build && cd build
* $ cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release <libarccos_full_path>
* $ make && sudo make install

Now, you can include header files like this:

`#include <arccos/logging/metalogging.h>`



#### Execute tests

* $ cd tests/mptoolstests && ctest



Please submit issues at https://github.com/devpassion/libarccos/issues.

