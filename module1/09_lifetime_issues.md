<!-- .slide: data-background="#111111" -->

# Lifetime issues

___


Notes
Care should be taken when a std::function whose result type is a reference is initialized from a lambda expression without a trailing-return-type. Due to the way auto deduction works, such lambda expression will always return a prvalue. Hence, the resulting reference will usually bind to a temporary whose lifetime ends when `std::function::operator()` returns.

```cpp
std::function<const int&()> F([]{ return 42; });
int x = F(); // Undefined behavior: the result of F() is a dangling reference
```
