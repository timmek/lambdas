<!-- .slide: data-background="#111111" -->

# `constexpr` lambda

___

## Implicit `constexpr`

From C++17 all lambda functions are by default implicitly marked as `constexpr`, if possible.

```cpp
auto squared = [](auto x) {             // implicitly constexpr
    return x * x;
};

std::array<int, squared(8)> a;          // OK - array<int, 64>
```

___

## Explicit `constexpr`

`constexpr` keyword can also be used explicitly.

```cpp
auto squared = [](auto x) constexpr {   // OK
    return x * x;
};
```

___

## Advanced example

`static_assert` is evaluated at compile time. Only `constexpr` values can be used in it.
<!-- .element: class="fragment fade-in" -->

```cpp
constexpr auto add = [](int n, int m) {
    auto L = [=] { return n; };
    auto R = [=] { return m; };
    return [=] { return L() + R(); };
};
static_assert(add(3, 4)() == 7);
```
<!-- .element: class="fragment fade-in" -->

### The 'lambada' antipattern
<!-- .element: class="fragment fade-in" -->

Above code with lambdas inside lambdas is difficult to understand. It takes some time to deduce the way it works. If it is not necessary - avoid it :)
<!-- .element: class="fragment fade-in" -->

Lifetime issues may be especially arduous to discover and debug.
<!-- .element: class="fragment fade-in" -->

<!-- TODO: Add some exercise for lambda in lambda? -->
