#include <iostream>

using namespace std;

class Piggy {
private:
    int cents;
    int nickels;
    int dimes;

    int total() const {
        return cents + nickels * 5 + dimes * 10;
    }

public:
    Piggy() : cents(0), nickels(0), dimes(0) {}

    void empty() {
        cents = nickels = dimes = 0;
    }

    void insert(int a, int b, int c) {
        cents += a;
        nickels += b;
        dimes += c;
    }

    void print() const {
        cout << "cents: " << cents << ", nickels: " << nickels << ", dimes: " << dimes << endl;
        cout << "total amount in piggy bank: " << total() << endl;
    }

    bool operator<(const Piggy& rhs) const { return total() < rhs.total(); }
    bool operator>(const Piggy& rhs) const { return total() > rhs.total(); }
    bool operator<=(const Piggy& rhs) const { return total() <= rhs.total(); }
    bool operator>=(const Piggy& rhs) const { return total() >= rhs.total(); }
    bool operator==(const Piggy& rhs) const { return total() == rhs.total(); }
    bool operator!=(const Piggy& rhs) const { return total() != rhs.total(); }
};

int main() {
    Piggy piggy1;
    Piggy piggy2;

    piggy1.insert(0, 2, 0);
    cout << (piggy1 > piggy2) << endl;
    piggy2.insert(0, 0, 2);
    cout << (piggy1 < piggy2) << endl;
    cout << (piggy1 != piggy2) << endl;
    piggy1.insert(10, 0, 0);
    cout << (piggy1 == piggy2) << endl;
    piggy1.print();
    piggy2.print();

    piggy1.empty();
    piggy2.empty();

		piggy1.print();

    return 0;
}

