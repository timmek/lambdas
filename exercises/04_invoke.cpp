#include <iostream>
#include <vector>
#include <functional>

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

struct A {
    int func() {
        std::cout << "func\n";
        return 1;
    }
};

// Write a function `callAnything()` that can take any function/functor/lambda as a first parameter.
// The rest of parameters will be passed into this callable from the first argument.
// Function should return a result of a function object call.

template <typename Function, typename ... Args>
decltype(auto) callAnything(Function && f, Args && ... args) {
    // return std::forward<Function>(f)(std::forward<Args>(args)...);
    return std::invoke(std::forward<Function>(f), std::forward<Args>(args)...);
}

int main() {
    A a;
    // callAnything(a.func);
    callAnything(&A::func, &a);
    callAnything(getIndexGenerator);
    callAnything(sum, 5, 6);
    callAnything([]{});
    callAnything([]{ return "Hello!"; });
    callAnything([] { std::cout << "Just testing\n"; });
    // callAnything(createVector<int>, std::initializer_list<int>{1, 2, 3});

    return 0;
}