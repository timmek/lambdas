<!-- .slide: data-background="#111111" -->

# The anatomy of lambda

___

## Empty function

```cpp
void f(){}
```

* `void` - return type
* `f` - function name
* `()` - empty parameter list
* `{}` - empty function body

___

## Empty lambda

```cpp
[](){};
```

* `[]` - capture list (what variables from the outer scope the function will capture)
* `()` - parameter list
* `{}` - function body

This lambda does nothing.

___

## Simple unnamed lambda

```cpp
[](int number) { return number % 2; };
```

* `[]` - empty capture list
* `(int number)` - takes one parameter - `int`
* `{ return number % 2; }` - lambda body

___

## Simple named lambda

```cpp
auto isOdd = [](int number) { return number % 2; };
```

* `auto` - the only proper type of lambda; it is deduced by the compiler
* `isOdd` - name of the lambda expression
* `[]` - empty capture list
* `(int number)` - takes one parameter - `int`
* `{ return number % 2; }` - lambda body

___

## Calling a lambda

### Named lambda

```cpp
auto isOdd = [](int number) { return number % 2; };
auto result = isOdd(101);
```

### Unnamed lambda

```cpp
auto result = [](int number) { return number % 2; }(101);
```

___

## Example

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    []() { std::cout << "Hello"; }    // lambda printing Hello (not called)

    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vec.erase(std::remove_if(vec.begin(),
                             vec.end(),
                             [](int num) { return num % 2; }),
              vec.end());

    auto print = [](int num) { std::cout << num << ' '; };
    std::for_each(vec.begin(), vec.end(), print);

    return 0;
}
```

___

## When to use named/unnamed lambda?

Usually prefer unnamed lambdas. They have only a local scope and will be called in current line of code. If there is no concurrency, there should be no lifetime issues.

If your lambda will be used in several places it is a good idea to name it. Beware of lifetime issues.

___

### Full lambda declaration (C++17)

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

### Full lambda declaration (C++20)

```cpp
[captures]<template params>(params) specifiers [[attributes]] -> ReturnType requires Constraint { body };
```

#### [lambda description on cppreference.com](https://en.cppreference.com/w/cpp/language/lambda)

___

## `{ body }`

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

Hopefully, explanation is not required 🙃

Every function must have a body. Forward declaration of lambda is not possible.

___

## `-> ReturnType`

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

* Usually, we do not indicate what is a lambda return type, because it is deduced automatically by the compiler. It uses lambda body `{}` to deduce the returned type.
* You can specify a return type of lambda function with arrow notation.

    ```cpp
    [](int rhs, int lhs) -> int { return rhs + lhs; }
    ```

* From C++14 compiler can easily deduce the returned type, so arrow notation is not popular. It may be used to do implicit conversion.

    ```cpp
    auto isNotNullptr = [](void* ptr) -> bool {
        return ptr;
    };
    ```

* Return type declaration may be needed in case of some template magic.

___

## `[[attributes]]`

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

Barely used. Please refer to Modern C++ training or just check [`[[attributes]] on cppreference.com`](https://en.cppreference.com/w/cpp/language/attributes)

___

## Specifiers

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

There are 3 types of lambda specifiers:

* `noexcept`
* `constexpr`
* `mutable`

From C++20 `consteval` will be available as well.

___

### `noexcept`

`noexcept` specifier guarantees, that no exception will be thrown from this lambda function. This is not checked during compilation. If, in runtime, exception will be thrown then the application will be terminated.

```cpp
auto loggedSwap = [&](auto & a, auto & b) noexcept {
    LOG << "before: a = " << a << ", b = " << b << '\n';
    std::swap(a, b);
    LOG << "after: a = " << a << ", b = " << b << '\n';
};
```

___

### `constexpr`

`constexpr` means that this lambda can be evaluated at compile time and the compiler may used already computed value instead of calling this lambda at runtime.

`constexpr` is implicitly added in C++17 lambdas, wherever possible.

> If the `c​onstexpr` specifier is omitted within the l​ambda-declarator,​ the function call operator (or template) is `c​onstexpr` if it would satisfy the requirements of a constexpr ​function:
>
> ```cpp
> auto ID = [](int n) { return n; };
> constexpr int I = ID(3);
> ```
>
> -- from [P0170R1](https://isocpp.org/files/papers/P0170R1.pdf)

___

### `mutable`

`mutable` means, that we can modify const objects captured by the lambda.

`mutable` is associated with capture list, so it will be covered together with it.


___

## `(params)`

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

Probably it does not require an explanation, but...

* `()` empty parentheses can be skipped

  ```cpp
  auto debugLog = [] { DEBUG << "hello!\n"; };
  ```

* `()` cannot be skipped when return type is provided or specifiers or attributes are used

  ```cpp
  auto loggedSwap = [&]() noexcept {
      LOG << "before: a = " << a << ", b = " << b << '\n';
      std::swap(a, b);
      LOG << "after: a = " << a << ", b = " << b << '\n';
  };
  ```

___

## Funny snippets

* `[](){};` - empty unnamed lambda
* `[](){}();` - immediate call of empty unnamed lambda
* `[]{}();` - the same, empty `()` can be skipped
* `[]<>(){};` - C++20 template lambda
* `(+[](){})();` - code::dive 2019 T-shirts snippet, [explanation](http://slawomir.net/2019/11/29/cpp-code-dive-t-shirts-expression/)
