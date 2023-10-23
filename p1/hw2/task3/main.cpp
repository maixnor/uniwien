#include <iostream>

using namespace std;

int main() {

	cout << "Enter a 3 digit number: ";
	int input;
	cin >> input;

	cout << input % 10; // last digit
	cout << ((input % 100) - (input % 10)) / 10; // middle digit
	cout << input / 100; // first digit
	cout << endl;

	return 0;
}
