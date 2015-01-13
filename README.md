libarccos
=========

### A little meta programming library


#### Features

* compile-time typelist : the famous typelist with an object-like syntax
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
* $ cmake -DCMAKE\_INSTALL\_PREFIX=/usr/local -DCMAKE\_BUILD\_TYPE=Release &lt;libarccos\_full\_path&gt;
* $ make && sudo make install

Now, you can include header files like this:

`#include <arccos/logging/metalogging.h>`



#### Execute tests

* $ cd tests/mptoolstests && ctest



Please submit issues at https://github.com/devpassion/libarccos/issues.

