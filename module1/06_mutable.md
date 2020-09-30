<!-- .slide: data-background="#111111" -->

# `mutable` keyword

___

## `mutable` specifier

> `mutable` specifier - permits modification of the class member declared mutable even if the containing object is declared const.
>
> -- [cppreference.com](https://en.cppreference.com/w/cpp/language/cv):

___

## M&M rule (multithreading)

The usual use of `mutable` is in M&M rule.

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

## `mutable` in lambda

Variables captured by value (copy), are implicitly const. They are read-only and you can not modify them.
<!-- .element: class="fragment fade-in" -->

`mutable` in lambda means, that we can modify objects captured by value.
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

`mutable` keyword allows you to modify const members
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
