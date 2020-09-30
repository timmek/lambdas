#include <iostream>

auto getIndexGenerator() {
    int value = 0;
    auto lambda = [&value] {
        return value++;
    };
    return lambda;
}

int getFive() {
    auto result = 5 + 4;
    return result;
}

int main() {
    auto generator = getIndexGenerator();
    int value = getFive();
    for (int i = 0; i < 10; ++i) {
        std::cout << generator();
    }
    std::cout << '\n';
    return 0;
}