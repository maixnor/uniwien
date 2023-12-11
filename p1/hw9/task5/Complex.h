#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double real = 0, double imag = 0);

    double getReal() const;
    double getImag() const;

    void setReal(double real);
    void setImag(double imag);

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

		bool operator==(double value) const;
    bool operator!=(double value) const;

    Complex conj() const;

    void print() const;
};

bool operator==(double value, const Complex& c);
bool operator!=(double value, const Complex& c);

#endif  // COMPLEX_H

