/*==============================================================================
 Name        : fastkey.hpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#pragma once
#include <cassert>
#include <functional>
#include <type_traits>

namespace stevemac
{
template <typename K> struct is_equal {
	bool operator()(const K &k1, const K &k2) const
	{
		static_assert(std::is_integral<K>::value, "integral required.");
		return k1 == k2;
	}
};

template <typename K, typename T, K _empty_key = K(),
	  typename Hash = std::hash<K>, typename Pred = is_equal<K>>
class fastkey
{
      public:
	using hasher = Hash;
	using key_equal = Pred;
	using iterator = T *;

	fastkey() = delete;
	fastkey(const size_t n) : _max_size(n)
	{
		allocate(n);
	}
	~fastkey()
	{
		deallocate();
	}

	fastkey(const fastkey &m) = delete;
	fastkey &operator=(const fastkey &m) = delete;

	bool insert(const K &key, T &val)
	{
		assert(_size <= _max_size);
		if (_size >= _max_size)
			return false;

		int idx = get_slot(key);
		if (_is_equal(_ktable[idx], _empty_key)) {
			construct(&_ktable[idx], key, &_table[idx], val);
			_size++;
			return true;
		}

		return false;
	}
	iterator find(const K &key) const
	{
		int idx = get_slot(key);
		if (_is_equal(_ktable[idx], _empty_key))
			return nullptr;

		return &_table[idx];
	}

	iterator begin()
	{
		return &_table[0];
	}
	iterator end()
	{
		return _end;
	}
	void stats()
	{
		printf("\nsize %zu: Max_size: %zu\n", _size, _max_size);
	}

      private:
	size_t get_slot(const K &key) const
	{
		size_t h = _hf(key);
		size_t idx = h % (_max_size);

		size_t step = hash2(h);

		while (!_is_equal(_ktable[idx], key)
		       && !_is_equal(_ktable[idx], _empty_key)) {
			idx += step;
			idx = idx % (_max_size);
		}
		return idx;
	}
	size_t hash2(const size_t &primary_hash) const
	{
		size_t h2 = (primary_hash * _max_size) % _max_size;
		return h2 == 0 ? 1 : h2; // can't return 0 for step
	}
	void allocate(const size_t n)
	{
		_table = new T[n];
		_ktable = new T[n];
		assert(_table && _ktable);
		_end = _table + _max_size;
		for (size_t i = 0; i < _max_size; i++) {
			_table[i] = T();
			_ktable[i] = _empty_key;
		}
	}

	void deallocate()
	{
		if (!std::is_trivially_constructible<K>::value
		    || !std::is_trivially_constructible<T>::value) {
			for (size_t i = 0; i < _max_size; i++)
				destroy(&_table[i], &_ktable[i]);
		}

		delete[] _table;
		delete[] _ktable;

		_max_size = 0;
		_size = 0;
		_end = nullptr;
		_table = nullptr;
		_ktable = nullptr;
	}
	void construct(K *kp, const K &key, T *tp, const T &val)
	{
		new (kp) K(key);
		new (tp) T(val);
	}
	void destroy(K *kp, T *tp)
	{
		((K *)kp)->~K();
		((T *)tp)->~T();
	}

      private:
	K *_ktable = nullptr;
	T *_table = nullptr;
	size_t _max_size = 0;
	hasher _hf = hasher();
	size_t _resize_factor = 2;
	float _density = 1.00;
	size_t _size = 0;
	T *_end = nullptr;
	key_equal _is_equal = key_equal();
};

} // end of namespace stevemac

