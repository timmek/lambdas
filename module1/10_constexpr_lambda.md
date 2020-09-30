<!-- .slide: data-background="#111111" -->

# `constexpr` lambda

___

From C++17 all lambda functions are by default implicitly marked as `constexpr`, if possible. `constexpr` keyword can also be used explicitly.

```cpp
auto squared = [](auto x) {             // implicitly constexpr
    return x * x;
};

std::array<int, squared(8)> a;          // OK - array<int, 64>

auto squared = [](auto x) constexpr {   // OK
    return x * x;
};
```

___

```cpp
constexpr auto add=[](int n, int m) {
    auto L = [=] { return n; };
    auto R = [=] { return m; };
    return [=] { return L() + R(); };
};
static_assert(add(3, 4)() == 7,"");
```
