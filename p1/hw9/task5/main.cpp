#include <iostream>
#include "Complex.h"

using namespace std;

int main() {
  Complex c1(2),c2(3,-4);
  double d1=2, d2(3);
  c2.print(); cout << " is " << (c2==d2 ? "" : "not ") << "equal to ";
  cout << d2 << endl;
  c1.print(); cout << " is " << (c1!=d1 ? "not " : "") << "equal to ";
  cout << d1 << endl;
  cout << d1 << " is " << (d1==c1 ? "" : "not ") << "equal to ";
  c1.print(); cout << endl;
  cout << d2 << " is " << (d2!=c2 ? "not " : "") << "equal to ";
  c2.print(); cout << endl;
  cout << "The complex conjugate of "; c2.print();
  cout << " is "; c2.conj().print(); cout << endl;
  return 0;
}
