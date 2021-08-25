<!-- .slide: data-background="#111111" -->

# `constexpr` lambda

___

## Niejawny `constexpr`

Od C++17 wszystkie funkcje lambda są domyślnie oznaczone jako `constexpr`, jeśli jest to możliwe.

```cpp
auto squared = [](auto x) {             // implicitly constexpr
    return x * x;
};

std::array<int, squared(8)> a;          // OK - array<int, 64>
```

___

## Jawny `constexpr`

Słowa kluczowego `constexpr` możemy też użyć jawnie.

```cpp
auto squared = [](auto x) constexpr {   // OK
    return x * x;
};
```

___

## Zaawansowany przykład

`static_assert` jest zawsze ewaluowany podczas kompilacji. Można w nim używać tylko wyrażeń `constexpr`.
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

### Antywzorzec 'lambada'
<!-- .element: class="fragment fade-in" -->

Powyższy kod z lambdami wewnątrz lambd jest trudny do zrozumienia. Potrzeba dużo czasu, aby wydedukować jak on działa. Jeśli nie jest to konieczne - unikaj tego.
<!-- .element: class="fragment fade-in" -->

Problemy z czasem życia obiektów są bardzo trudne do odkrycia i debugowania.
<!-- .element: class="fragment fade-in" -->

<!-- TODO: Add some exercise for lambda in lambda? -->
