<!-- .slide: data-background="#111111" -->

# STL algorithms customization

___

## How to sort a container?

```cpp
std::vector<double> diffs = {1.1, -0.2, -1.3, 0.8, 0.1, -0.3}
```

### Use `std::sort`

```cpp
std::sort(diffs.begin(), diffs.end());
```

By default, sorting is done using `std::less` function, which calls `operator<` to compare elements.

### Result

```cpp
{-1.3, -0.3, -0.2, 0.1, 0.8, 1.1}
```

___

## How to sort the container by absolute values?

Most of STL algorithms can be customized by passing an additional parameter - a special function object.

```cpp
bool absoluteCompare(double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
}
std::sort(diffs.begin(), diffs.end(), absoluteCompare);
```

### Result

`{0.1, -0.2, -0.3, 0.8, 1.1, -1.3}`

#### How to get to know what function object should be passed?

___

## Customization function

Each algorithm has a documented signature of needed function.

[Check `std::sort` on cppreference.com](https://en.cppreference.com/w/cpp/algorithm/sort)

___

## Common kinds of functions

* (unary) predicate
  * returns `bool`, takes 1 arg
* binary predicate
  * returns `bool`, takes 2 args
* comparator
  * returns `bool` takes 2 args

___

## What is a *function object*?

It is any object for which the function call operator is defined - `operator()`.

* pointer to function
* functor
* lambda expression
* `std::function`
* function?
  * no, it's not a *function object*, but it is implicitly convertible to *pointer to function*

___

## Sorting with a function

```cpp
bool absoluteCompare(double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
}
std::sort(diffs.begin(), diffs.end(), absoluteCompare);
```

## Sorting with a functor

```cpp
struct AbsoluteCompare {
    bool operator()(double rhs, double lhs) {
        return std::abs(rhs) < std::abs(lhs);
    }
};
std::sort(diffs.begin(), diffs.end(), AbsoluteCompare{});
```

___

## Sorting with lambda

### Named lambda

```cpp
auto absoluteCompare = [](double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
};
std::sort(diffs.begin(), diffs.end(), absoluteCompare);
```

### Unnamed lambda

```cpp
std::sort(diffs.begin(), diffs.end(), [](double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
});
```

___

## Why so many ways?

![What if...](../img/what_if.png)
<!-- .element: style="text-align: center" -->

___

## Exercise

Use proper STL algorithm to check if all elements of the vector *numbers* are divisible by 3.

```cpp
std::vector<int> numbers = {18, 21, 36, 90, 27, 14, 103};
```

Implement 3 versions:

* lambda
* functor
* function

___

### Solutions

#### Lambda

```cpp
bool result = std::all_of(numbers.begin(), numbers.end(), [](int number){
    return number % 3 == 0;
});
```

#### Functor

```cpp
struct DivisibleBy {
    DivisibleBy(int n);
    bool operator()(int number) {
            return number % n == 0;
    }
private:
    int n;
};
bool result = std::all_of(numbers.begin(), numbers.end(), DivisibleBy{3});
```

#### Function

```cpp
bool isDivisibleBy3(int number) {
    return number % 3 == 0;
}
bool result = std::all_of(numbers.begin(), numbers.end(), isDivisibleBy3);
```
