<!-- .slide: data-background="#111111" -->

# The anatomy of lambda

<!-- TODO: Nice background? -->
___

But first, let's take a look into...

## Empty function
<!-- .element: class="fragment fade-in" -->

```cpp
void f(){}
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>void</code> - return type
* <!-- .element: class="fragment fade-in" --> <code>f</code> - function name
* <!-- .element: class="fragment fade-in" --> <code>()</code> - empty parameter list
* <!-- .element: class="fragment fade-in" --> <code>{}</code> - empty function body

___

## Empty lambda

```cpp
[](){};
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>[]</code> - capture list (which variables from the outer scope will be captured)
* <!-- .element: class="fragment fade-in" --> <code>()</code> - parameter list
* <!-- .element: class="fragment fade-in" --> <code>{}</code> - function body

This lambda does nothing.
<!-- .element: class="fragment fade-in" -->

___

## Simple unnamed lambda

```cpp
[](int number) { return number % 2; };
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>[]</code> - empty capture list
* <!-- .element: class="fragment fade-in" --> <code>(int number)</code> - takes one parameter - <code>int</code>
* <!-- .element: class="fragment fade-in" --> <code>{ return number % 2; }</code> - lambda body

___

## Simple named lambda

```cpp
auto isOdd = [](int number) { return number % 2; };
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>auto</code> - the only proper type of lambda; it is deduced by the compiler
* <!-- .element: class="fragment fade-in" --> <code>isOdd</code> - name of the lambda expression
* <!-- .element: class="fragment fade-in" --> <code>[]</code> - empty capture list
* <!-- .element: class="fragment fade-in" --> <code>(int number)</code> - takes one parameter - <code>int</code>
* <!-- .element: class="fragment fade-in" --> <code>{ return number % 2; }</code> - lambda body

___

## Calling a lambda

### Named lambda
<!-- .element: class="fragment fade-in" -->

```cpp
auto isOdd = [](int number) { return number % 2; };
auto result = isOdd(101);
```
<!-- .element: class="fragment fade-in" -->

### Unnamed lambda
<!-- .element: class="fragment fade-in" -->

```cpp
auto result = [](int number) { return number % 2; }(101);
```
<!-- .element: class="fragment fade-in" -->

___

## Example

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    []() { std::cout << "Hello"; };    // lambda printing Hello (not called)

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

Output: `2 4 6 8`

___

## When to use named/unnamed lambda?

### Unnamed lambdas
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> can be used and called only in one place
* <!-- .element: class="fragment fade-in" --> have a local scope
* <!-- .element: class="fragment fade-in" --> usually no lifetime issues (when no concurrency)

### Named lambdas
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> reusable
* <!-- .element: class="fragment fade-in" --> may be problematic because of lifetime issues

___

### Full lambda declaration (C++17)

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

### Full lambda declaration (C++20)
<!-- .element: class="fragment fade-in" -->

```cpp
[captures]<template params>(params) specifiers [[attributes]] -> ReturnType requires Constraint { body };
```
<!-- .element: class="fragment fade-in" -->

#### [lambda description on cppreference.com](https://en.cppreference.com/w/cpp/language/lambda)
<!-- .element: class="fragment fade-in" -->

___

<code style="font-size: 0.7em">
[captures](params) specifiers [[attributes]] -> ReturnType <span style="color: #cf802a">{ body }</span>;
</code>

## `{ body }`

Hopefully, explanation is not required 🙃

Every function must have a body. Forward declaration of lambda is not possible.

___

<code style="font-size: 0.7em">
[captures](params) specifiers [[attributes]] <span style="color: #cf802a">-> ReturnType</span> { body };
</code>

## `-> ReturnType`

* <!-- .element: class="fragment fade-in" --> Usually, we do not indicate what is a lambda return type, because it is deduced automatically by the compiler. It uses lambda body <code>{}</code> to deduce the returned type.
* <!-- .element: class="fragment fade-in" --> You can specify a return type of lambda function with arrow notation.

    ```cpp
    [](int rhs, int lhs) -> int { return rhs + lhs; }
    ```

* <!-- .element: class="fragment fade-in" --> From C++14 compiler can easily deduce the returned type, so arrow notation is not popular. It may be used to do implicit conversion.

    ```cpp
    auto isNotNullptr = [](void* ptr) -> bool {
        return ptr;
    };
    ```

* <!-- .element: class="fragment fade-in" --> Return type declaration may be needed in case of some template magic.

___

<code style="font-size: 0.7em">
[captures](params) specifiers <span style="color: #cf802a">[[attributes]]</span> -> ReturnType { body };
</code>

## `[[attributes]]`

Barely used. Please refer to Modern C++ training or just check [`[[attributes]]` on cppreference.com](https://en.cppreference.com/w/cpp/language/attributes)

___

<code style="font-size: 0.7em">
[captures](params) <span style="color: #cf802a">specifiers</span> [[attributes]] -> ReturnType { body };
</code>

## Specifiers

There are 3 types of lambda specifiers (in C++17):

* <!-- .element: class="fragment fade-in" --> <code>noexcept</code>
* <!-- .element: class="fragment fade-in" --> <code>constexpr</code>
* <!-- .element: class="fragment fade-in" --> <code>mutable</code>

From C++20 `consteval` will be available as well.
<!-- .element: class="fragment fade-in" -->

___

### `noexcept`

`noexcept` specifier guarantees, that no exception will be thrown from this lambda function.

It is not checked during compilation.

If, in runtime, exception will be thrown then the application will be terminated.

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
<!-- .element: class="fragment fade-in" -->

`constexpr` is implicitly added in C++17 lambdas, wherever possible.
<!-- .element: class="fragment fade-in" -->

> If the `constexpr` specifier is omitted within the lambda-declarator, the function call operator (or template) is `constexpr` if it would satisfy the requirements of a constexpr function:
>
> ```cpp
> auto ID = [](int n) { return n; };
> constexpr int I = ID(3);
> ```
>
> -- from [P0170R1](https://isocpp.org/files/papers/P0170R1.pdf)
<!-- .element: class="fragment fade-in" -->
___

### `mutable`

`mutable` means, that we can modify const objects captured by the lambda.

`mutable` is associated with capture list, so it will be covered together with it.

___

<code style="font-size: 0.7em">
[captures]<span style="color: #cf802a">(params)</span> specifiers [[attributes]] -> ReturnType { body };
</code>

## `(params)`

Probably it does not require an explanation, but...

* <!-- .element: class="fragment fade-in" --> <code>()</code> empty parentheses can be skipped

  ```cpp
  auto debugLog = [] { DEBUG << "hello!\n"; };
  ```

* <!-- .element: class="fragment fade-in" --> <code>()</code> cannot be skipped when return type is provided or specifiers or attributes are used

  ```cpp
  auto loggedSwap = [&]() noexcept {
      LOG << "before: a = " << a << ", b = " << b << '\n';
      std::swap(a, b);
      LOG << "after: a = " << a << ", b = " << b << '\n';
  };
  ```

___

## Funny snippets

* <!-- .element: class="fragment fade-in" --> <code>[](){};</code>
  * <!-- .element: class="fragment fade-in" --> empty unnamed lambda
* <!-- .element: class="fragment fade-in" --> <code>[]{}();</code>
  * <!-- .element: class="fragment fade-in" --> immediate call of empty unnamed lambda, empty <code>()</code> are skipped
* <!-- .element: class="fragment fade-in" --> <code>[](){}();</code>
  * <!-- .element: class="fragment fade-in" --> the same, but <code>()</code> is not skipped
* <!-- .element: class="fragment fade-in" --> <code>[]<>(){};</code>
  * <!-- .element: class="fragment fade-in" --> C++20 template lambda
* <!-- .element: class="fragment fade-in" --> <code>(+[](){})();</code>
  * <!-- .element: class="fragment fade-in" --> code::dive 2019 T-shirts snippet, <a href="http://slawomir.net/2019/11/29/cpp-code-dive-t-shirts-expression/">explanation</a>

<!-- TODO: image of code::dive t-shirt -->