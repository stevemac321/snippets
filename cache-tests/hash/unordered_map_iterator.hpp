/*
 * unordered_map_iterator.h
 *
 *  Created on: May 16, 2015
 *      Author: stevemac
 */

#pragma once
namespace stevemac {
///===----------------------------------------------------------------------===//
///
/// \class stevemac::iterator
/// \brief Implementation started in fall of 2014. It is is derived from:
/// std::iterator<std::random_access_iterator_tag>.  It has only been tested
/// with stevemac::vector.
///
//===----------------------------------------------------------------------===//
/// Class Template stevemac::iterator
///
//===----------------------------------------------------------------------===//

template <typename Container>
class unordered_map_iterator : public std::iterator<std::random_access_iterator_tag,
                                             typename Container::value_type> {
public:
  using value_type = typename Container::value_type;
  using pointer = typename Container::pointer;
  using reference = typename Container::reference;
  using difference_type = typename Container::size_type;
  using key_type = typename Container::key_type;
  using mapped_type = typename Container::key_type;

protected:
  /// pointee is owned by the Container
  ///
  pointer pointee;

  //===----------------------------------------------------------------------===//
  /// construct/destroy: The constructor is used for conversion
  /// The pointee member is owned and managed by the Container which is why
  /// iterator does not have any destruction duties
  //===----------------------------------------------------------------------===//

public:
  unordered_map_iterator() {}
  /// explicit constructor used for converting to the underlying pointer type
  /// provided by the Container: Container::pointer.
  explicit unordered_map_iterator(pointer ptr) : pointee(ptr) {}

  /// the Container owns the only resource: pointee; hence no duties here.
  ~unordered_map_iterator() {}
  reference operator*() { return *pointee; }
   pointer operator->() { return pointee; }
   pointer get_ptr() {return pointee;}

   unordered_map_iterator& operator++() {
	   ++pointee;
       return *this;
     }
     unordered_map_iterator operator++(int) {
       unordered_map_iterator tmp = *this;
       ++pointee;
       return tmp;
     }
     ///
     unordered_map_iterator& operator--() {
    --pointee;
       return *this;
     }
     unordered_map_iterator operator--(int) {
       unordered_map_iterator tmp = *this;
        --pointee;
       return tmp;
     }
     difference_type operator-(unordered_map_iterator& other) {
       return pointee - other.pointee;
     }
     unordered_map_iterator operator+(difference_type n) {
       return unordered_map_iterator(pointee + n);
     }
     unordered_map_iterator operator-(difference_type n) {
       return unordered_map_iterator(pointee - n);
     }
     unordered_map_iterator& operator+=(difference_type n) {
       pointee += n;
       return *this;
     }
     unordered_map_iterator& operator-=(difference_type n) {
       pointee -= n;
       return *this;
     }

     //===----------------------------------------------------------------------===//
     /// logical operators
     ///
     //===----------------------------------------------------------------------===//
     bool operator==(const unordered_map_iterator &other) const {
       return pointee == other.pointee;
     }

     bool operator!=(const unordered_map_iterator &other) const {
       return pointee != other.pointee;
     }

     bool operator<(const unordered_map_iterator &other) {
       return pointee < other.pointee;
     }

     bool operator>(const unordered_map_iterator &other) {
       return pointee > other.pointee;
     }

     bool operator<=(const unordered_map_iterator &other) {
       return pointee <= other.pointee;
     }

     bool operator>=(const unordered_map_iterator &other) {
       return pointee >= other.pointee;
     }

};
} // end namespace


