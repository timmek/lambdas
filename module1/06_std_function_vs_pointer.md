<!-- .slide: data-background="#111111" -->

# `std::function` vs pointer to function

___

## Exercise

### `area.cpp`

Change function `areaLessThan20` into lambda.

Then change it into `areaLessThanX`, which takes `x = 20` on a capture list.

What is the problem?

Use `std::function` to solve the problem.

___

## Conversion to pointer to function #1

Lambda that does not capture anything can be converted into a pointer to function.

```cpp
#include <iostream>
using namespace std;

auto foo(int (*fptr)()) {
    auto result = fptr();
    return result;
}

int main() {
    auto result = foo([] { return 5; });
    std::cout << result;
    return 0;
}
```

___

## Conversion to pointer to function #2

Lambda that captures can not be converted into a pointer to function.

```cpp
#include <iostream>
using namespace std;

auto foo(int (*fptr)()) {
    auto result = fptr();
    return result;
}

int main() {
    int value = 5;
    auto result = foo([value] { return value; });
    // error: cannot convert ‘main()::<lambda()>’ to ‘int (*)()’
    std::cout << result;
    return 0;
}
```

___

## `std::function`

`std::function` is a special wrapper class that can hold any type of callable, especially all kind of lambdas.

It is defined in `<functional>` header.

```cpp
#include <iostream>
#include <functional>
using namespace std;

auto foo(std::function<int()> fptr) {
    auto result = fptr();
    return result;
}

int main() {
    int value = 5;
    auto result = foo([value] { return value; });
    std::cout << result;
    return 0;
}
```

___

## Function signatures

Pointers to functions

* `int (*f)()` - f takes no arguments and returns and int
* `void (*f)(int)` - f takes an int and returns nothing
* `double (*f)(int, string)` - f takes an int and a string and returns double

To get `std::function` template type just remove the pointer name `(*f)`. Name the whole `std::function<>` with the name `f`.

* `std::function<int()> f` - f takes no arguments and returns and int
* `std::function<void(int)> f` - f takes an int and returns nothing
* `std::function<double(int, string)> f` - f takes an int and a string and returns double

___

## `std::function`

> `std::function` is a general-purpose polymorphic function wrapper. Instances of std::function can store, copy, and invoke any Callable target - functions, lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members.
>
> From [cppreference.com](https://en.cppreference.com/w/cpp/utility/functional/function)

`std::function` has `operator()` function, that forwards all arguments to the wrapped callable and invokes it.

Because of this 'polymorphic' feature `std::function` is considered as a 'heavy' stuff. If there is a possibility use pointers to functions instead.

`std::function` can be empty. Invoking an empty `std::function` results in `std::bad_function_call` exception being thrown.
