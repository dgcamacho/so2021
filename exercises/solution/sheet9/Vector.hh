#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>

namespace scprog
{
  class Vector
  {
  public:
    using value_type = double;
    using size_type = std::size_t;

    // Default constructor, just allocates memory, no initialization!
    // Marked `explicit`, so no `Vector x = 7` allowed.
    explicit Vector(size_type size = 0)
      : size_(size)
      , data_(size > 0 ? new value_type[size] : nullptr)
    {}

    // Constructor that initializes all components with value
    Vector(size_type size, value_type value)
      : Vector(size)
    {
      std::fill(data_, data_ + size_, value);
    }

    // Destructor, releases the allocated memory
    ~Vector()
    {
      delete[] data_;
    }

    // Copy constructor using delegation to default constructor
    Vector(Vector const& that)
      : Vector(that.size_)
    {
      std::copy(that.data_, that.data_ + size_, data_);
    }

    // Copy assignment operator implemented in terms of copy constructor
    // and move assignment operator
    Vector& operator=(Vector const& that)
    {
      return *this = Vector(that);
    }

    // Move constructor implemented in terms of move assignment operator
    Vector(Vector&& that)
    {
      *this = std::move(that);
    }

    // Move assignment operator implemented in terms of swap
    Vector& operator=(Vector&& that)
    {
      this->swap(that);
      return *this;
    }

    // Swap the content of this and that
    void swap(Vector& that)
    {
      using std::swap;
      swap(size_, that.size_);
      swap(data_, that.data_);
    }

    // Const access to the element of the container
    value_type const& operator[](size_type i) const
    {
      assert(i < size_);
      return data_[i];
    }

    // Mutable access to the elements of the container
    value_type& operator[](size_type i)
    {
      assert(i < size_);
      return data_[i];
    }

    // Return the size of the container
    size_type size() const
    {
      return size_;
    }

  private:
    size_type size_ = 0;
    value_type* data_ = nullptr;
  };

  void swap(Vector& lhs, Vector& rhs)
  {
    lhs.swap(rhs);
  }

} // end namespace scprog
