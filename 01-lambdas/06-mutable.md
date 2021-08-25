<!-- .slide: data-background="#111111" -->

# `mutable` keyword

___

## `mutable` specifier

> `mutable` specifier - permits modification of the class member declared mutable even if the containing object is declared const.
>
> -- [cppreference.com](https://en.cppreference.com/w/cpp/language/cv):

___

## zasada M&M (wielowątkowość)

Zazwyczaj `mutable` używamy w zasadzie M&M.

```cpp
class ThreadsafeCounter {
    mutable std::mutex m; // The "M&M rule": mutable and mutex go together
    int data = 0;

 public:
    int get() const {
        std::lock_guard<std::mutex> lk(m);
        return data;
    }
    void inc() {
        std::lock_guard<std::mutex> lk(m);
        ++data;
    }
};
```

___

## `mutable` w lambdzie

Operator wywołania - `operator()` - w lambdzie jest funkcją `const`. Oznacza to, że nie może on modyfikować pól klasy.
<!-- .element: class="fragment fade-in" -->

Łatwiej jest myśleć o tym w ten sposób, że to co przechwycimy przez kopię jest `const`.
<!-- .element: class="fragment fade-in" -->

`mutable` w lambdzie oznacza, że możemy modyfikować obiekty przechwycone przez kopię.
<!-- .element: class="fragment fade-in" -->

```cpp
void foo() {
    double number = 0.5;
    [number]() mutable { number += 1.0 }(); // ok
    // [number] { number += 1.0 }();
    // error: assignment of read-only variable ‘number’
    [&number]() { number += 1.0 }(); // ok, capture by ref
}
```
<!-- .element: class="fragment fade-in" -->

`mutable` pozwala na modyfikowanie pól w stałym obiekcie.
<!-- .element: class="fragment fade-in" -->

___

## Example

```cpp
int main() {
    std::vector<int> vec(10);
    std::generate(begin(vec), end(vec), [i{0}]() mutable { return i++; });
    print(vec);

    return 0;
}
```

Output: `0 1 2 3 4 5 6 7 8 9`

___

## Zadanie

Utwórz lambdę, która ma wraz z każdym wywołaniem zwracać kolejną literę alfabetu, zaczynając od `a`. Gdy dojdziemy do `z` lambda powinna zwracać duże litery - od `A` do `Z`, a potem znów małe. Nie używaj zewnętrznych zmiennych statycznych lub globalnych.
