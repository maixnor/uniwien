#include <iostream>

using namespace std;

int main() {

	cout << "Evaluating a function $f(x) = ax^3 + bx^2 + cx + d$ at position x" << endl;
	
	double a;
	cout << "parameter a: ";
	cin >> a;
	double b;
	cout << "parameter b: ";
	cin >> b;
	double c;
	cout << "parameter c: ";
	cin >> c;
	double d;
	cout << "parameter d: ";
	cin >> d;

	double x;
	cout << "enter x position to evaluate: ";
	cin >> x;

	double result = 0;

	result += d;
	result += c * x;
	result += b * x * x;
	result += a * x * x * x;

	cout << "The result is: " << result << endl;

	return 0;
}
