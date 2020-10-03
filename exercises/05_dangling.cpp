#include <iostream>

int sth = 0;

auto getIndexGenerator() {
    // static int value = 0;
    auto lambda = [value = 0]() mutable {
        sth++;
        return value++;
    };
    return lambda;
}

int getFive() {
    auto result = 5 + 4;
    return result;
}

// Fix the code.
// We want a generator to provide consecutive numbers starting from 0.
// Correct output: `0123456789`

int main() {
    auto generator = getIndexGenerator();
    auto generator2 = getIndexGenerator();
    [[maybe_unused]] int value = getFive();
    for (int i = 0; i < 10; ++i) {
        std::cout << generator();
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << generator2();
    }
    std::cout << '\n';
    return 0;
}