#include <iostream>

int main() {
	  double length, width;
		std::cout << "Length of the rect: ";
		std::cin >> length;
		std::cout << "Width of the rect: ";
		std::cin >> width;
    std::cout << "Area: " << length * width << ", Circumferenc: " << (length + width) * 2 << "\n";
    return 0;
}
