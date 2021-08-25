<!-- .slide: data-background="#111111" -->

# Generyczne lambdy

___

## Generyczne lambdy

W C++11 parametry lambdy muszą mieć konkretne typy.
<!-- .element: class="fragment fade-in" -->

C++14 pozwala na użycie typu parametru `auto`.
<!-- .element: class="fragment fade-in" -->

```cpp
int main() {
    auto multiplyByFactor = [factor = 10](auto number) {
        return number * factor;
    };
    std::cout << multiplyByFactor(20) << '\n';
    std::cout << multiplyByFactor(1.23) << '\n';

    return 0;
}
```
<!-- .element: class="fragment fade-in" -->

Output:
<!-- .element: class="fragment fade-in" -->

```text
200
12.3
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.95em" -->

## Domknięcia generycznych lambd

Użycie typu `auto` powoduje wygenerowanie klasy domknięcia, która ma szablonowy operator wywołania.
<!-- .element: class="fragment fade-in" -->

```cpp
auto lambda = [](auto x, auto y) { return x + y; }
```
<!-- .element: class="fragment fade-in" -->

```cpp
struct UnnamedClosureClass {
    template <typename T1, typename T2>
    auto operator()(T1 x, T2 y) const {
        return x + y;
    }
};
auto lambda = UnnamedClosureClass{};
```
<!-- .element: class="fragment fade-in" -->
