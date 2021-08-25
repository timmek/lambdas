<!-- .slide: data-background="#111111" -->

# Szablony vs generyczne lambdy

___

Szablony są najtrudniejszą i najmniej intuicyjną częścią języka C++. Są one jednak bardzo użyteczne.

Generyczne lambdy mogą nam zastąpić szablony w niektórych miejscach. Dzięki nim kod może stać się czytelniejszy.

___
<!-- .slide: style="font-size: 0.9em" -->

```cpp
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
#include <memory>

int main() {
    auto wrapWithUniquePtr = [](auto value) {
        return std::make_unique<decltype(value)>(value);
    };

    auto ptr1 = wrapWithUniquePtr(4);
    auto ptr2 = wrapWithUniquePtr(5.3);
    return 0;
}
```
<!-- .element: class="fragment fade-in" -->
