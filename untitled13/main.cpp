#include <iostream>

bool Election(bool x, bool y, bool z) {
    int sum = x + y + z;
    return sum >= 2;
}

int phi(int n) {
    int result;
    if (n > 1)
        result = phi(n-1) + phi(n-2);
    else
        result = 1;
    return result;
}

int main() {
    std::cout << Election(0,1,1);
//    std::cout << phi(5);
}
