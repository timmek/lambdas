#include <iostream>
#include <vector>

auto getIndexGenerator() {
    int value = 0;
    auto lambda = [&value] {
        return value++;
    };
    return lambda;
}

int sum(int a, int b) {
    return a + b;
}

template <typename T>
auto createVector(std::initializer_list<T> initList) {
    return std::vector<T>{initList};
}

// Write a function `callAnything()` that can take any function/functor/lambda as a first parameter.
// The rest of parameters will be passed into this callable from the first argument.
// Function should return a result of a function object call.

int main() {
    // callAnything(getIndexGenerator);
    // callAnything(sum, 5, 6);
    // callAnything([]{});
    // callAnything([]{ return "Hello!"; });
    // callAnything([] { std::cout << "Just testing\n"; });
    // callAnything(createVector<int>, std::initializer_list<int>{1, 2, 3});

    return 0;
}