#include <iostream>

using namespace std;

int main() {
	cout << "Enter a string: ";
	string input;
	cin >> input;

	while (cin) {
		cout << "What letter do you want to exclude: ";
		char exclude;
		cin >> exclude;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == exclude) continue;
			cout << input[i];
		}
		cout << endl;
	}


}
