<!-- .slide: data-background="#111111" -->

# Capture list

___

## `[]` - capture list

Capture variables from the local scope of the lambda.

Things used inside lambda body have another scope. To pass something to lambda you need to use parameters or a capture list.

```cpp
int divide(int number) {
    int divider = 100
    auto divideBy100 = [divider](int value){
        return value / divider;
    }
    return divideBy100(number);
}
```

___

## Why the are 2 ways of passing things inside a lambda?

Lambda may be created in one scope and passed somewhere else to be called.

Variables from the local scope are captured by a capture list immediately (on lambda creation), whereas parameters may be passed later in a calling scope.

Things from a capture list exist as a lambda internal members.

___

## Capture list values

* `[]` - capture nothing
* `[a]` - capture variable `a` by copy (value)
* `[&a]` - capture variable `a` by reference
* `[a, &b]` - capture `a` by copy and `b` by reference
* `[=]` - capture everything by copy
* `[&]` - capture everything by reference
* `[&, a]` - capture `a` by copy and everything else by reference
* `[=, &a]` - capture `a` by reference and everything else by copy
* `[this]` - capture `this` pointer by copy (pointer copy points to the same object! It can modify current class object!)
* `[*this]` - (C++17) capture `this` pointer by copy (creates a copy of this object)

`this` is captured anyway when either `[=]` or `[&]` are used and **in both cases allow to modify** the current object

### Question

When using `[&]` may not be safe?

___

## Examples

```c++
int a {5};
auto add5 = [=](int x) { return x + a; };
// auto add5 = [](int x) { return x + a; }; // error: a is not defined

int counter {};
auto inc = [&counter] { counter++; };

int even_count = 0;
for_each(v.begin(), v.end(), [&even_count] (int n) {
    cout << n;
    if (n % 2 == 0)
        ++even_count;
});

cout << "There are " << even_count
     << " even numbers in the vector." << endl;
```

___

## Quiz

* `[i, i]` - error, `i` repeated
* `[&, &i]` - error, by-reference capture when by-reference is the default
* `[this, *this]` - error, `this` repeated
* `[&, this]` - OK, equivalent to `[&]`
* `[&, this, i]` - OK, equivalent to `[&, i]`
* `[=, this]` - since C++20 OK, same as `[=]`, C++17 - error

___

## Lambda capture expressions (C++14)

C++11 lambda functions capture variables declared in their outer scopes by value-copy or by reference. This means that a value members of a lambda cannot be **move-only** types.

C++14 allows captured members to be initialized with arbitrary expressions. This allows both capture by value-move and declaring arbitrary members of the lambda, without having a correspondingly named variable in an outer scope.

```c++
auto lambda = [value = 1] { return value; };

std::unique_ptr<int> ptr(new int(10));
auto anotherLambda = [value = std::move(ptr)] { return *value; };
```

Variable initialized on capture list have `auto` type. It is deduced from the expression.

___

## Exercise

Create a lambda, which prints `*` characters. Each lambda call should produce a string longer by one `*`.

Example:

* `*`
* `**`
* `***`
* etc.
