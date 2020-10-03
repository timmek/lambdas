#include <iostream>
#include <vector>
#include <algorithm>

// use STL algorithm to check if all elements are divisible by 3
// implement 3 versions:
// * lambda
// * functor
// * function


bool isDivisibleBy3(int value) {
    return value % 3 == 0;
}

int main() {
    std::vector numbers = {18, 21, 36, 90, 27, 14, 103};

    bool result = std::all_of(numbers.begin(), numbers.end(), [](int value){
        return value % 3 == 0;
    });

    bool result2 = std::all_of(numbers.begin(), numbers.end(), isDivisibleBy3);

    struct IsDivisible {
        IsDivisible(int divisor) : divisor_(divisor) {}
        bool operator()(int value) {
            return value % divisor_ == 0;
        }
    private:
        int divisor_;
    };

    bool result3 = std::all_of(numbers.begin(), numbers.end(), IsDivisible{3});

    std::cout << result << result2 << result3 << '\n';

    return 0;
}
