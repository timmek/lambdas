<!-- .slide: data-background="#111111" -->

# Templates vs generic lambdas

___

Templates are the least intuitive feature of C++, however, very useful one.

Generic lambdas can replace some template function.

```cpp
#include <iostream>
#include <memory>

template <typename T>
std::unique_ptr<T> wrapWithUniquePtr(T value) {
    return std::make_unique<T>(value);
}

int main() {
    auto ptr1 = wrapWithUniquePtr(4);
    auto ptr2 = wrapWithUniquePtr(5.3);

    return 0;
}
```

```cpp
auto wrapWithUniquePtr = [](auto value) {
    return std::make_unique<decltype(value)>(value);
};
```
<!-- .element: class="fragment fade-in" -->

___

## Exercise (or homework)

### `07_sfinae.cpp`

Write a function `insert()` that allows objects of class derived from Circle to be inserted into collection.

Objects of other class should be not allowed.

Usage:

```cpp
insert(Circle{1.0}, circles);
insert(Ellipse{1.1}, circles);      // ok, derives from Circle
// insert(double{1.1}, circles);    // not allowed
```

You may use SFINAE (`std::enable_if`) or `constexpr if`.

___

### SFINAE solution

```cpp
template <typename T,
          typename Collection,
          typename = std::enable_if_t<std::is_base_of_v<Circle, T>>
>
void insert(T item, Collection& collection) {
    collection.emplace_back(make_shared<T>(item));
}
```

___

### `if constexpr` solution

```cpp
auto insert = [](auto item, auto& collection) {
    if constexpr (std::is_base_of_v<Circle, decltype(item)>) {
        collection.emplace_back(make_shared<decltype(item)>item);
    }
};
```

___

## What is a difference between those two solutions?

* <!-- .element: class="fragment fade-in" --> SFINAE does not compile (or does not generate an additional overload) for improper types
* <!-- .element: class="fragment fade-in" --> <code>constexpr if</code> does nothing

* <!-- .element: class="fragment fade-in" --> Lambda is an object with some lifetime, it must be created in a proper place (or must be passed)
* <!-- .element: class="fragment fade-in" --> Function is not an object (in C++), so it can be called anywhere. Proper include is needed.
