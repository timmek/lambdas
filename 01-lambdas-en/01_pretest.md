<!-- .slide: data-background="#111111" -->

# Pre-test

___

## 1. Which lambda function is valid?

1. `[]() -> int { return 4; };`
1. `int [](){ return 4; };`
1. `auto [](){ return 4; };`
1. `[]() -> auto {return 4; };`
1. `[](){ return 4; };`
1. `[] { return 4; }`
1. `[] mutable { return 4; }`
1. `[] -> int { return 4; }`
1. `int []{ return 4; }`

Note: 1, 4, 5, 6

___

## 2. Which capture lists are correctly formed?

Assume that all variables exist.

1. `[=, this]`
2. `[&, this]`
3. `[this, *this]`
4. `[&, &a]`
5. `[a, &]`
6. `[&, a, &b]`
7. `[=, a, &b]`
8. `[=, &a]`
9. `[=, *a]`

Note: 2, 8
