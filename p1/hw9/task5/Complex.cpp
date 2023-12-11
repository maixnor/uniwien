#include "Complex.h"

Complex::Complex(double real, double imag) : real(real), imag(imag) {}

double Complex::getReal() const {
    return real;
}

double Complex::getImag() const {
    return imag;
}

void Complex::setReal(double real) {
    this->real = real;
}

void Complex::setImag(double imag) {
    this->imag = imag;
}

bool Complex::operator==(const Complex& other) const {
    return (real == other.real) && (imag == other.imag);
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

bool Complex::operator==(double value) const {
    return (real == value) && (imag == 0);
}

bool Complex::operator!=(double value) const {
    return !(*this == value);
}

Complex Complex::conj() const {
    return Complex(real, -imag);
}

void Complex::print() const {
    std::cout << "(" << real << (imag >= 0 ? " + " : " - ") << std::abs(imag) << "i)";
}

bool operator==(double value, const Complex& c) {
    return c == value;
}

bool operator!=(double value, const Complex& c) {
    return c != value;
}
