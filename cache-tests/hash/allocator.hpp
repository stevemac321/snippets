/*==============================================================================
 Name        : allocator.hpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#pragma once
namespace stevemac
{
template <typename T> struct allocator {

	using value_type = T;
	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	pointer allocate(size_type n) { return new value_type[n]; }
	void deallocate(pointer p, size_type n = 0) { delete [] p; }
	void construct(pointer p, const_reference val) { new (p) T(val); }
	void destroy(pointer p) { ((T *)p)->~T(); }
	size_type max_size() const { return _max; }

	const size_type _max = 1048576;
};
} // end of namespace
