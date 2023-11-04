#include <iostream>

using namespace std;

/// e.g. 789456789 causes an infinite loop in the negative numbers (-20, -10, -5, -14, -7, ...)

int main() {

	cout << "Enter a positive integer: ";
	int input;
	cin >> input;

	while (input != 1) {
		if (input % 2 == 0) {
			input = input / 2; // even
		} else {
			input = 3 * input + 1; // odd
		}
		cout << input << endl;
	}

	cout << endl;

	return 0;
}
