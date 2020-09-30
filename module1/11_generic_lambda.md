<!-- .slide: data-background="#111111" -->

# Generic lambda

___

## Generic lambdas

In C++11 parameters of lambda expression must be declared with use of specific type.

C++14 allows to declare parameter as `auto`.

```cpp
int main() {
    auto multiplyByFactor = [factor = 10](auto number) { return number * factor; };
    std::cout << multiplyByFactor(20) << '\n';
    std::cout << multiplyByFactor(1.23) << '\n';

    return 0;
}
```

Output:

```text
200
12.3
```

___
<!-- .slide: style="font-size: 0.95em" -->

## Generic lambdas closure class

In C++11 parameters of lambda expression must be declared with use of specific type.

C++14 allows to declare parameter as `auto`.

This allows a compiler to deduce the type of lambda parameter in the same way parameters of the templates are deduced. In result compiler generates a code equivalent to closure class given below:

```cpp
auto lambda = [](auto x, auto y) { return x + y; }
```

```cpp
struct UnnamedClosureClass {
    template <typename T1, typename T2>
    auto operator()(T1 x, T2 y) const {
        return x + y;
    }
};
auto lambda = UnnamedClosureClass{};
```
