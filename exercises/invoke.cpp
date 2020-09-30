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

template <typename Function, typename... Args>
auto callAnything(Function f, Args... args) {
    return std::invoke(f, args...);
}

template <typename Function, typename... Args>
auto returnAnything(Function f, Args... args) {
    // static_assert(!std::is_void_v<std::invoke_result_t<Function, Args...>>);
    return std::invoke(f, args...);
}

int main() {
    callAnything(getIndexGenerator);
    callAnything(sum, 5, 6);
    callAnything([]{});
    callAnything([]{ return "Hello!"; });
    callAnything([] { std::cout << "Just testing\n"; });
    callAnything(createVector<int>, std::initializer_list<int>{1, 2, 3});

    returnAnything(getIndexGenerator);
    returnAnything(sum, 5, 6);
    returnAnything([]{});
    returnAnything([]{ return "Hello!"; });
    returnAnything([] { std::cout << "Just testing\n"; });
    returnAnything(createVector<int>, std::initializer_list<int>{1, 2, 3});
    return 0;
}