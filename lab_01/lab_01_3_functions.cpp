
#include <iostream>

using namespace std;

// parameter passing

// passing by value
void add_by_value(int x, int y)
{
  x = x + y;
}

// passing by reference (aliasing)
void add_by_reference(int &x, int y)
{
  x = x + y;
}

// passing by pointer
void add_by_pointer(int *x, int y)
{
  *x = *x + y;
}

int main()
{
  int x = 10, y = 5;

  add_by_value(x, y);
  cout << "By value: x = " << x << ", y = " << y << endl;

  x = 10, y = 5;
  add_by_reference(x, y);
  cout << "By reference: x = " << x << ", y = " << y << endl;

  x = 10, y = 5;
  add_by_pointer(&x, y);
  cout << "By pointer: x = " << x << ", y = " << y << endl;
}