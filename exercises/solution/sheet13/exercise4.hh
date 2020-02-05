#pragma once

#include <cassert>
#include <memory>

namespace scprog
{
  template <class T>
  class vector
  {
  public:
    using value_type = T;
    using size_type = std::size_t;

    // iterators implemented as pointer to elements
    using iterator = value_type*;
    using const_iterator = value_type const*;

  public:
    // construct without initialization
    vector(size_type s = 0u)
      : size_(s)
      , capacity_(s)
      , data_(capacity_ > 0 ? new value_type[capacity_] : nullptr)
    {}

    // construct and initialize
    vector(size_type s, value_type const& v)
      : vector(s) // delegating constructor
    {
      for (size_type i = 0; i < size_; ++i)
        data_[i] = v;
    }

    // copy constructor
    vector(vector const& that)
      : vector(that.size_) // delegating constructor
    {
      // deep-copy
      for (size_type i = 0; i < size_; ++i)
        data_[i] = that.data_[i];
    }

    // move constructor
    vector(vector&&) = default;

    // copy/move-assignment operator
    vector& operator=(vector that)
    {
      // implemented in terms of copy-and-swap ideom
      swap(that);
      return *this;
    }


    // constant element access
    value_type const& operator[](size_type i) const
    {
      return data_[i];
    }

    // mutable element access
    value_type& operator[](size_type i)
    {
      return data_[i];
    }


    // constant element access with bounds checking
    value_type const& at(size_type i) const
    {
      assert( i < size_ );
      return data_[i];
    }

    // mutable element access with bounds checking
    value_type& at(size_type i)
    {
      assert( i < size_ );
      return data_[i];
    }


    // const access to the underlying array
    value_type const* data() const { return data_.get(); }

    // mutable access to the underlying array
    value_type* data() { return data_.get(); }


    // iterator to the first element of the container.
    iterator        begin()       { return data(); }
    const_iterator cbegin() const { return data(); }

    // iterator to the element following the last element of the container.
    iterator        end()       { return data() + size_; }
    const_iterator cend() const { return data() + size_; }


    // change size of vector, maybe need reallocation
    void resize(size_type s)
    {
      size_ = s;
      if (size_ > capacity_) {
        data_.reset(new value_type[size_]);
        capacity_ = size_;
      }
    }

    // resize and initialize all vector components with `v`
    void resize(size_type s, value_type const& v)
    {
      resize(s);
      for (size_type i = 0; i < size_; ++i)
        data_[i] = v;
    }

  public: // capacity members

    // checks whether the container is empty
    bool empty() const { return size_ == 0; }

    size_type size() const { return size_; }

    size_type capacity() const { return capacity_; }

  private:

    void swap(vector& rhs)
    {
      using std::swap;
      swap(data_, rhs.data_);
      swap(size_, rhs.size_);
      swap(capacity_, rhs.capacity_);
    }

  private:
    // the number of elements
    size_type size_;

    // number of elements that can be held in currently allocated storage
    size_type capacity_;

    // a pointer to the vector data
    std::unique_ptr<value_type[]> data_;
  };

} // end namespace scprog
