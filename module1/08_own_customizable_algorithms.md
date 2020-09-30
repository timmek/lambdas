<!-- .slide: data-background="#111111" -->

# Own customizable algorithms

___

## Exercise

### `invoke.cpp`

Write a function `callAnything()` that can take any function/functor/lambda as a first parameter.

The rest of parameters will be passed into this callable from the first argument.

Function should return a result of a function object call.

Hint #1: Variadic template can handle any number of template parameter.

```cpp
int main() {
    callAnything(getIndexGenerator);
    callAnything(sum, 5, 6);
    callAnything([]{});
    callAnything([]{ return "Hello!"; });
    callAnything([] { std::cout << "Just testing\n"; });
    callAnything(createVector<int>, std::initializer_list<int>{1, 2, 3});
    return 0;
}
```

___

Hint #2: [`std::invoke`](https://en.cppreference.com/w/cpp/utility/functional/invoke) may be useful.
