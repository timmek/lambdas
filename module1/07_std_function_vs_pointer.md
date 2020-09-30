<!-- .slide: data-background="#111111" -->

# `std::function` vs pointer to function

___

## Exercise

### `03_area.cpp`

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
    // auto result = foo([value] { return value; });
    // error: cannot convert ‘main()::<lambda()>’ to ‘int (*)()’
    // std::cout << result;
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

### Pointers to functions
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>int (*f)()</code> - f takes no arguments and returns and int
* <!-- .element: class="fragment fade-in" --> <code>void (*f)(int)</code> - f takes an int and returns nothing
* <!-- .element: class="fragment fade-in" --> <code>double (*f)(int, string)</code> - f takes an int and a string and returns double

To get `std::function` template type just remove the pointer name `(*f)`. Name the whole `std::function<>` with the name `f`.
<!-- .element: class="fragment fade-in" -->

### `std::function`
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>std::function&lt;int()> f</code> - f takes no arguments and returns and int
* <!-- .element: class="fragment fade-in" --> <code>std::function&lt;void(int)> f</code> - f takes an int and returns nothing
* <!-- .element: class="fragment fade-in" --> <code>std::function&lt;double(int, string)> f</code> - f takes an int and a string and returns double

___

## `std::function`

> `std::function` is a general-purpose polymorphic function wrapper. Instances of std::function can store, copy, and invoke any Callable target - functions, lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members.
>
> -- from [cppreference.com](https://en.cppreference.com/w/cpp/utility/functional/function)

Because of this 'polymorphic' feature `std::function` is considered as a heavy stuff. If there is a possibility use pointers to functions instead.

___

## empty `std::function`

`std::function` has a call operator function - `operator()`, that forwards all arguments to the wrapped callable and invokes it.

`std::function` can be empty. Invoking an empty `std::function` results in `std::bad_function_call` exception being thrown.

___
<!-- .slide: style="font-size: 0.9em" -->

## Exercise

### `04_invoke.cpp`

Write a function `callAnything()` that can take any function/functor/lambda as a first parameter.

The rest of parameters will be passed into this callable from the first argument.

Function should return a result of a function object call.

```cpp
int main() {
    callAnything(getIndexGenerator);
    callAnything(sum, 5, 6);
    callAnything([]{});
    callAnything([]{ return "Hello!"; });
    callAnything([] { std::cout << "Just testing\n"; });
    callAnything(createVector<int>, std::initializer_list<int>{1, 2, 3});
    return 0;
}
```

Hint #1: Variadic template can handle any number of template parameter.
<!-- .element: class="fragment fade-in" -->

Hint #2: [`std::invoke`](https://en.cppreference.com/w/cpp/utility/functional/invoke) may be useful.
<!-- .element: class="fragment fade-in" -->
