#include <cassert>                                // (38) needs include for assert
#include <cstddef>                                // (39) needs additional include for std::size_t

class Vector                                      // (1) classes in upper case
{
public:                                           // (2) member functions and some type should be public
  typedef double value_type;                      // (3) wrong order in typedef
  typedef std::size_t size_type;                  // (4) introduce type of size and indices

  Vector(size_type size = 0)                      // (5),(6),(7) type should match member variable type, name must be meaningful, default constructor
    : size_(size)                                 // (8) member variable with different name than parameter
    , data_(size_ > 0 ? new value_type[size_] : nullptr)   // (9),(10),(11) member variable with common style, test for 0-size arrays, use typedef for value type
  {}

  Vector(Vector const& that)
    : size_(that.size_)                           // same as above
    , data_(size_ > 0 ? new value_type[size_] : nullptr)  // same as above
  {
    for (size_type i = 0; i < size_; ++i)         // (12),(13),(14) size_type, upper limit of loop, ++i
      data_[i] = that.data_[i];                   // (15) copy from that to this
  }                                               // (16) no return statement in constructor!

  ~Vector() { delete[] data_; }                   // (17),(40) destructor without arguments, delete must match new

  Vector& operator=(Vector const& that)           // (18),(19) assignment operator is non-const, use common bracket-style
  {
    assert(size_ == that.size_);                  // (20) inverse logic in assert, end statement with a ;
    if (this != &that) {                          // (21) no self-assignment!
      for (size_type i = 0; i < size_; ++i)       // (22) loop index is always >= 0, thus infinite loop
        data_[i] = that.data_[i];
    }
    return *this;                                 // (23) return reference, not pointer
  }

                                                  // (24),(25) missing move constructor, move-assignment operator

  value_type const& operator[](size_type i) const // (26),(27), types and const-access function must be marked const
  {
    return data_[i];                              // (28) access to data with square brackets
  }

  value_type& operator[](size_type i)
  {
    return data_[i];
  }

  size_type size() const { return size_; }      // (29) size() should be a member function not a free function

private:
  size_type const size_;                        // (30) order of the member variables
  value_type* data_;                            // (31) static array without size not possible as class member, but raw pointer
};                                              // (32) class closes with semicolon;

int main()                                      // (33) main() must return integer
{
  Vector v1(6);
  Vector v2(v1);
  Vector v3(10);
  v1 = v2;
  //v3 = v2;                                    // (34) assignment of vectors of different size
  v1[2] = 1;                                    // (35) wrong access operator
  const Vector v4(v2);
  //v4[2] = 1.0;                                // (36) assignment to const object not allowed
  v4.size();                                    // (37) wrong syntax for call to size()
}