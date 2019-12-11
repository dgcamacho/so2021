#include <string>

// (a)
class Encode {
  private:
    long secretKey;
  public:
    Encode(long key); // Constructors do not have a return type!
};

// (b)
class Gift {
    std::string gift;
  public:
    ~Gift();
    //~Gift(std::string&); // There is only 1 destructor! Without arguments!
};                         // Semicolon missing

// (c)
class Numeric {
  private:
    long x;
  public:
    void set(long n) { x = n; } // A const-function can not modify member variables
    long get() const { return x; } // The const keyword must be placed directly after the argument list
};

// (d)
class Pair {
  private:
    double x; double y;
  public:
    void getPair(double& x, double& y) { x = this->x; y = this->y; }
    // Function parameters hide the names of the member variables.
    // Use "this" to explicitly name the member variables!
};
