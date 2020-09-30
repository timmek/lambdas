<!-- .slide: data-background="#111111" -->

# Templates vs generic lambdas

___

Templates are the least intuitive feature of C++, however, very useful.

Generic lambdas can replace some template function.

```cpp
#include <iostream>
#include <memory>

template <typename T>
std::unique_ptr<T> wrapWithUniquePtr(T value) {
    return std::make_unique<T>(value);
}

int main() {
    wrapWithUniquePtr(4);
    wrapWithUniquePtr(5.3);

    return 0;
}
```

```cpp
auto wrapWithUniquePtr = [](auto value) {
    return std::make_unique<decltype(value)>(value);
};
```

___

## Exercise

### `sfinae.cpp`

Write a function `insert()` that allows inserting objects of class derived from Circle to be inserted into collection. Usage:

```cpp
insert(Circle{1.0}, circles);
insert(Ellipse{1.1}, circles);      // derives from Circle
// insert(double{1.1}, circles);    // not allowed
```

You may use SFINAE (`std::enable_if`) or `constexpr if`.

___

### SFINAE solution

```cpp
template <typename T,
          typename Collection,
          typename = std::enable_if_t<std::is_base_of_v<Shape, T>>
>
void insert(T item, Collection& collection) {
    collection.emplace_back(make_shared<T>(item));
}
```

___

### `if constexpr` solution

```cpp
auto insert = [](auto item, auto& collection) {
    if constexpr (std::is_base_of_v<Shape, decltype(item)>) {
        collection.emplace_back(make_shared<decltype(item)>item);
    }
};
```

___

## What is a difference between those two solutions?

* SFINAE does not compile (or does not generate an additional overload) for improper types, `constexpr if` does nothing
* Lambda is an object with some lifetime, function is not an object (in C++)

