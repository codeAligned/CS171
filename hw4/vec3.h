#ifndef __VEC3_
#define __VEC3_
/*
A simple vector class
*/

class Vec3 {

public:
  // Constructors
  Vec3();                      // default constructor
  Vec3(const Vec3 &v);             // copy constructor
  Vec3(double aX, double aY, double aZ);

  // Destructor
  ~Vec3() {};

  // Operators
  Vec3 & operator=(const Vec3 &rhs);

  Vec3 & operator+=(const Vec3 &rhs);
  Vec3 & operator-=(const Vec3 &rhs);
  Vec3 & operator*=(const Vec3 &rhs);

  const Vec3 operator+(const Vec3 &v) const;
  const Vec3 operator-(const Vec3 &v) const;

  bool operator==(const Vec3 &other) const;
  bool operator!=(const Vec3 &other) const;

  void add(double v);
  void subtract(double v);
  void multiply(double v);
  void divide(double v);

  double length() const;
  double dot(const Vec3 &other) const;
  void normalize();
  Vec3 cross(const Vec3 &other) const;

  void zeroClip();
  void oneClip();

  // Debugging functions
  void print() const;

  double x, y, z;
private:

  void copy(const Vec3 &v);

};
#endif
