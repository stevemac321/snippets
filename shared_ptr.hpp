 /*-----------------------------------------------------------------------------
 ===============================================================================
 Name        : shared_ptr.hpp
 Author      : Stephen MacKenzie
 Version     :
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Description:  see comments at the end of this file
 ===============================================================================
The class template reg_ptr is a shared pointer design pattern that keeps a 
static count of owners that is shared among all instances of the template type. 
It is will compile with C++ 98/03 up to C++14.
Once a reg_ptr is instantiated and in scope, additional ownership is obtained
by acquire/release semantics.  Copying is disabled.  Obviously, policy needs to
be in place to limit access to the particular device register through the
shared pointer instance, else the refcounting is meaningless.
Usage:
   
reg_ptr<IntType, RegisterAddress> sp([optional} initVal); 
 -----------------------------------------------------------------------------*/
#ifndef SHARED_PTR_HPP_
#define SHARED_PTR_HPP_
#include <stdint.h>
#include <stddef.h>
////////////////////////////////////////////////////////////////////////////////
// stand-alone template functions
////////////////////////////////////////////////////////////////////////////////
template <typename T> void setval(T addr, const T val)
{
	*reinterpret_cast<volatile T*>(addr) = val;
}
template <typename T> bool isequal(T addr, const T val)
{
	return (*reinterpret_cast<volatile T*>(addr) == val);
}
////////////////////////////////////////////////////////////////////////////////
// shared refcounted class for memory mapped device registers
////////////////////////////////////////////////////////////////////////////////
namespace stevemac {

template <typename UIntType, UIntType Addr> class reg_ptr
{
public:
#if __cplusplus >= 201103L
	using value_type = UIntType;
	using reference = value_type&;
	using const_reference = const reference;
	using pointer = value_type*;
	using rvalue_reference = value_type&&;
#else
	typedef T value_type;
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef const value_type& const_reference;
#endif
			// construction-destruction
	reg_ptr(){refcount = 1;}
	reg_ptr(const_reference val)
	{
		setval(val);
		refcount = 1;
	}
	
// disable copying - rather acquire and release while in scope
#if __cplusplus >= 201103L
	reg_ptr(rvalue_reference val)
	{
		setval(val);
		refcount = 1;
	}
	reg_ptr(const reg_ptr& other) = delete;
	reg_ptr(reg_ptr&& other) = delete;
	reg_ptr& operator=(const reg_ptr& other) = delete;
#endif	
	// acquire-release
	reg_ptr& acquire()
	{
		++refcount;
		return *this;
	}
	void release(){	--refcount;}	
	
	//modifiers
#if __cplusplus >= 201103L
	void setval(const_reference val)
	{
		*reinterpret_cast<volatile pointer>(Addr) = val;
	}
	void setval(rvalue_reference val)
	{
		*reinterpret_cast<volatile pointer>(Addr) = val;
	}
#else
	void setval(value_type val)
	{
		*reinterpret_cast<volatile pointer>(Addr) = val;
	}
#endif	
	// inquire state
	uint8_t getrefcount(){ return refcount;}

private:
	// static refcount is shared among all instances of this template type
	static uint8_t refcount;

// older compiler, disable copying the old fashion way
#if __cplusplus < 201103L
	reg_ptr(const reg_ptr& other) {}
	reg_ptr& operator=(const reg_ptr& other) { return other; }
#endif
	};
	// initialize static member
template <typename UIntType, UIntType Addr> uint8_t reg_ptr<UIntType, Addr>::refcount = 0;
} // end of namespace

#endif /* SHARED_PTR_HPP_ */