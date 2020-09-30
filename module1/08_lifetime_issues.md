<!-- .slide: data-background="#111111" -->

# Lifetime issues

___

## Exercise

### `05_dangling.cpp`

Fix the code.

We want a generator to provide consecutive numbers starting from 0.

Correct output: `0123456789`

___

## Dangling reference

The main problem with lambdas is a dangling reference.
<!-- .element: class="fragment fade-in" -->

Lambda is created in a place of it's definition - on stack. Some variables are available during it's creation.
<!-- .element: class="fragment fade-in" -->

This lambda does not have to be called immediately or in a current scope. It may be passed somewhere else. Some local variables captured by lambda by reference may become unavailable. This causes UB (Undefined Behavior).
<!-- .element: class="fragment fade-in" -->

___

## Exercise

### `06_synchronization.cpp`

Fix `generateContainer()` function.

We want to have each value from 1 to 10 to be printed on the screen only once.

Every thread should put only one value to the shared vector.

The order does not matter.

Possible outputs:

`1, 2, 3, 4, 5, 6, 7, 8, 9, 10`

`2, 4, 6, 8, 10, 1, 3, 5, 7, 9`

`1, 3, 2, 4, 5, 6, 8, 10, 9, 7`

___

## Dangling reference with `std::function`

> Care should be taken when `std::function` whose **result type is a reference** is initialized from a lambda expression [...]. Due to the way auto deduction works, such lambda expression will always return an prvalue. Hence, the resulting reference will usually bind to a temporary whose lifetime ends when `std::function::operator()` returns.
>
> ```cpp
> std::function<const int&()> F([]{ return 42; });
> int x = F(); // Undefined behavior:
> // the result of F() is a dangling reference
> ```
>
> -- [cppreference.com](https://en.cppreference.com/w/cpp/utility/functional/function)
