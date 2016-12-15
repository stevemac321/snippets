#Snippets
This is a place that I keep bits of code.  It is not a project.

Contents:

------------------------------------------------------------
LEDBlink
debug.mak
release.mak
stm32.mak
Makefile

This is a visualgdb makefile based that I use on Linux.

------------------------------------------------------------
shared_ptr.hpp

The class template reg_ptr is a shared pointer design pattern that keeps a 
static count of owners that is shared among all instances of the template type. 
It is will compile with C++ 98/03 up to C++14.
Once a reg_ptr is instantiated and in scope, additional ownership is obtained
by acquire/release semantics.  Copying is disabled.  Obviously, policy needs to
be in place to limit access to the particular device register through the
shared pointer instance, else the refcounting is meaningless.
Usage:
   
reg_ptr<IntType, RegisterAddress> sp([optional} initVal); 

--------------------------------------------------------------
print.c was provided by Konstantin Isakov to support semihosting
Note that COMM is an alias for USART2 

--------------------------------------------------------------
int_bench.c was provided by Konstantin Isakov to measure interrupt latency



