#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    int x;                          // uninitialized
    std::cout << v[3] << '\n';      // out of bounds read
    if (x > 0) std::cout << "positive\n";
    return 0;
}
