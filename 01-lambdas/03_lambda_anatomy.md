<!-- .slide: data-background="#111111" -->

# Anatomia lambdy

<!-- TODO: Nice background? -->
___

Ale najpierw przyjrzyjmy się...

## Pusta funkcja
<!-- .element: class="fragment fade-in" -->

```cpp
void f(){}
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>void</code> - typ zwracany
* <!-- .element: class="fragment fade-in" --> <code>f</code> - nazwa
* <!-- .element: class="fragment fade-in" --> <code>()</code> - pusta lista parametrów
* <!-- .element: class="fragment fade-in" --> <code>{}</code> - puste ciało

___

## Pusta lambda

```cpp
[](){};
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>[]</code> - pusta lista przechwytywania
* <!-- .element: class="fragment fade-in" --> <code>()</code> - pusta lista parametrów
* <!-- .element: class="fragment fade-in" --> <code>{}</code> - puste ciało

Ta lambda nic nie robi.
<!-- .element: class="fragment fade-in" -->

___

## Prosta nieznazwana lambda

```cpp
[](int number) { return number % 2; };
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>[]</code> - pusta lista przechwytująca
* <!-- .element: class="fragment fade-in" --> <code>(int number)</code> - przyjmuje 1 parametr - <code>int</code>
* <!-- .element: class="fragment fade-in" --> <code>{ return number % 2; }</code> - ciało lambdy

___

## Prosta nazwana lambda

```cpp
auto isOdd = [](int number) { return number % 2; };
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>auto</code> - jedyny słuszny typ lambdy; jest znany tylko kompilatorowi
* <!-- .element: class="fragment fade-in" --> <code>isOdd</code> - nazwa lambdy
* <!-- .element: class="fragment fade-in" --> <code>[]</code> - pusta lista przechwytująca
* <!-- .element: class="fragment fade-in" --> <code>(int number)</code> - przyjmuje 1 parametr - <code>int</code>
* <!-- .element: class="fragment fade-in" --> <code>{ return number % 2; }</code> - ciało lambdy

___

## Wywoływanie lambdy

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

## Przykład

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

## Kiedy używać nazwanych, a kiedy nienazwanych lambd?

### Nienazwane
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> do użycia tylko w jednym miejscu
* <!-- .element: class="fragment fade-in" --> mają zasięg lokalny
* <!-- .element: class="fragment fade-in" --> nie ma problemów z czasem życia (gdy nie ma wielowątkowości)

### Nazwane
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> reużywalne
* <!-- .element: class="fragment fade-in" --> mogą sprawiać problemy z czasem życia obiektów

___

### Pełna deklaracja lambdy (C++17)

```cpp
[captures](params) specifiers [[attributes]] -> ReturnType { body };
```

### Pełna deklaracja lambdy (C++20)
<!-- .element: class="fragment fade-in" -->

```cpp
[captures]<template params>(params) specifiers [[attributes]] -> ReturnType requires Constraint { body };
```
<!-- .element: class="fragment fade-in" -->

#### [opis lambd na cppreference.com](https://en.cppreference.com/w/cpp/language/lambda)
<!-- .element: class="fragment fade-in" -->

___

<code style="font-size: 0.7em">
[captures](params) specifiers [[attributes]] -> ReturnType <span style="color: #cf802a">{ body }</span>;
</code>

## `{ body }`

Mam nadzieję, że to nie wymaga wyjaśnień 🙃

Każda funkcja musi mieć ciało. Nie można stworzyć deklaracji zapowiadającej lambdy.

___

<code style="font-size: 0.7em">
[captures](params) specifiers [[attributes]] <span style="color: #cf802a">-> ReturnType</span> { body };
</code>

## `-> ReturnType`

* <!-- .element: class="fragment fade-in" --> Zazwyczaj nie wskazujemy, co jest typem zwracanym, ponieważ jest on automatycznie dedukowany przez kompilator na podstawie ciała lambdy.
* <!-- .element: class="fragment fade-in" --> Możesz jawnie określić typ zwracany za pomocą notacji ze strzałką.

    ```cpp
    [](int rhs, int lhs) -> int { return rhs + lhs; }
    ```

* <!-- .element: class="fragment fade-in" --> Od C++14 kompilatory mogą łatwo wydedukować zwracany typ, więc notacja strzałkowa nie jest popularna. Może być ona jednak używana do niejawnej konwersji.

    ```cpp
    auto isNotNullptr = [](void* ptr) -> bool {
        return ptr;
    };
    ```

* <!-- .element: class="fragment fade-in" --> Deklaracja typu zwracanego może być potrzebna w przypadku niektórych magii z użyciem szablonów 🪄

___

<code style="font-size: 0.7em">
[captures](params) specifiers <span style="color: #cf802a">[[attributes]]</span> -> ReturnType { body };
</code>

## `[[attributes]]`

Bardzo rzadko używane (praktycznie wcale). O atrybutach pouczymy się kiedy indziej, ale możesz teraz spojrzeć na [`[[attributes]]` na cppreference.com](https://en.cppreference.com/w/cpp/language/attributes)

___

<code style="font-size: 0.7em">
[captures](params) <span style="color: #cf802a">specifiers</span> [[attributes]] -> ReturnType { body };
</code>

## `specifiers`

Są 3 typy specyfikatorów dla lambd (w C++17):

* <!-- .element: class="fragment fade-in" --> <code>noexcept</code>
* <!-- .element: class="fragment fade-in" --> <code>constexpr</code>
* <!-- .element: class="fragment fade-in" --> <code>mutable</code>

Od C++20 jest jeszcze `consteval`.
<!-- .element: class="fragment fade-in" -->

___

### `noexcept`

`noexcept` gwarantuje, że z lambdy nie zostanie rzucony wyjątek.

Nie jest to sprawdzane podczas kompilacji.
<!-- .element: class="fragment fade-in" -->

Jeśli podczas działania programu wyjątek poleci, to program zostanie ubity.
<!-- .element: class="fragment fade-in" -->

```cpp
auto loggedSwap = [&](auto & a, auto & b) noexcept {
    LOG << "before: a = " << a << ", b = " << b << '\n';
    std::swap(a, b);
    LOG << "after: a = " << a << ", b = " << b << '\n';
};
```
<!-- .element: class="fragment fade-in" -->

___

### `constexpr`

`constexpr` oznacza, że lambda może zostać wykonana już podczas kompilacji i kompilator może użyć gotowej, obliczonej wartości zamiast wołać tę lambdę w czasie działania programu.

`constexpr` jest niejawnie dodawany od C++17, jeśli lambda zostanie użyta w odpowiednim kontekście.
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

`mutable` oznacza, że możemy modyfikować stałe obiekty przechwycone przez lambdę.

Pokryjemy to dokładnie trochę później podczas tematu listy przechwytującej 🙂

___

<code style="font-size: 0.7em">
[captures]<span style="color: #cf802a">(params)</span> specifiers [[attributes]] -> ReturnType { body };
</code>

## `(params)`

To chyba nie wymaga wyjaśnienia, ale...

* <!-- .element: class="fragment fade-in" --> <code>()</code> puste nawiasy można pominąć

  ```cpp
  auto debugLog = [] { DEBUG << "hello!\n"; };
  ```

* <!-- .element: class="fragment fade-in" --> <code>()</code> nie można pominąć pustych nawiasów, jeśli wskazujemy typ zwracany w notacji ze strzałką, używamy specyfikatorów lub atrybutów.

  ```cpp
  auto loggedSwap = [&]() noexcept {
      LOG << "before: a = " << a << ", b = " << b << '\n';
      std::swap(a, b);
      LOG << "after: a = " << a << ", b = " << b << '\n';
  };
  ```

___
<!-- .slide: data-background="../img/tshirt.jpg" data-background-position="bottom" data-background-opacity="0.2" -->

## Funny snippets

* <!-- .element: class="fragment fade-in" --> <code>[](){};</code>
  * <!-- .element: class="fragment fade-in" --> pusta nienazwana lambda
* <!-- .element: class="fragment fade-in" --> <code>[]{}();</code>
  * <!-- .element: class="fragment fade-in" --> natychmiastowe wywołanie pustej nienazwanej lambdy, puste <code>()</code> są pominięte
* <!-- .element: class="fragment fade-in" --> <code>[](){}();</code>
  * <!-- .element: class="fragment fade-in" --> to samo, ale puste <code>()</code> nie są pominięte
* <!-- .element: class="fragment fade-in" --> <code>[]<>(){};</code>
  * <!-- .element: class="fragment fade-in" --> szablonowa lambda z C++20
* <!-- .element: class="fragment fade-in" --> <code>(+[](){})();</code>
  * <!-- .element: class="fragment fade-in" --> code::dive 2019 T-shirts snippet, <a href="http://slawomir.net/2019/11/29/cpp-code-dive-t-shirts-expression/">wyjaśnienie</a>
