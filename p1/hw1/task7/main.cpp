#include <iostream>

using namespace std;

int main() {
	char choice;
	double amount;

	cout << "What to convert? Euro (e) or Dollar (d): ";
	cin >> choice;
	cout << "Sure thing! How much do you want to convert: ";
	cin >> amount;

	double result;
	string out_currency;

	if (choice == 'e') {
		result = amount * 1.2; // don't know the exact course, but this should do
		out_currency = "Dollars";
	}

	if (choice == 'd') {
		result = amount / 1.2;
		out_currency = "Euros";
	}

	cout << "That will be " << result << " " << out_currency << "\n";

	return 0;
}
