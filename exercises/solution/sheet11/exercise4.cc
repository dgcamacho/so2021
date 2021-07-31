#include <utility> // -> std::swap

namespace scprog
{
  template <class T>
  class SmartPointer
  {
  public:
    // default constructor
    SmartPointer() = default;

    // Constructor
    SmartPointer(T* ptr_)
      : ptr(ptr_)
    {}

    // Destructor
    ~SmartPointer()
    {
      delete ptr;
    }

    // NO Copy-constructor!
    SmartPointer(SmartPointer const&) = delete;

    // Move-constructor
    SmartPointer(SmartPointer&& that)
    {
      std::swap(ptr, that.ptr);
    }

    // NO Copy-assignment operator
    SmartPointer& operator=(SmartPointer const&) = delete;

    // Move-assignment operator
    SmartPointer& operator=(SmartPointer&& that)
    {
      SmartPointer tmp(std::move(that));
      std::swap(ptr, that.ptr);

      return *this;
    }

    // Dereferencing operator
    T& operator*() { return *ptr; }
    T const& operator*() const { return *ptr; }

    // Member-access operator
    T* operator->() { return ptr; }
    T const* operator->() const { return ptr; }

    // Set ptr to new address
    void reset(T* ptr_)
    {
      delete ptr;
      ptr = ptr_;
    }

    // Return raw pointer
    T* get() { return ptr; }
    T const* get() const { return ptr; }

  private:
    T* ptr = nullptr;
  };

  SmartPointer<double> make_smart_pointer() {
    return SmartPointer<double>{ new double };
  }

} // end namespace scprog

int main()
{
  using namespace scprog;

  auto p = make_smart_pointer();
  *p = 1.0;

#if 0
  auto q = p; // Does this make sense for your pointer type? --> no! copy not allowed
  *q = 2.0;   // What is the effect on p?
#endif
}
