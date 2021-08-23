<!-- .slide: data-background="#111111" -->

# Capture list

___

<code style="font-size: 0.7em">
<span style="color: #cf802a">[captures]</span>(params) specifiers [[attributes]] -> ReturnType { body };
</code>

## `[captures]`

Captures variables from the local scope of the lambda.
<!-- .element: class="fragment fade-in" -->

Things used inside lambda body have another scope. To pass something to lambda you need to use parameters or a capture list.
<!-- .element: class="fragment fade-in" -->

```cpp
int divide(int number) {
    int divider = 100;
    auto divideBy100 = [divider](int value){
        return value / divider;
    }
    return divideBy100(number);
}
```
<!-- .element: class="fragment fade-in" -->

___

## Why there are 2 ways of passing things inside a lambda?

Lambda may be created in one scope and called in another.
<!-- .element: class="fragment fade-in" -->

Variables from the local scope are captured by a capture list immediately (on lambda creation), whereas parameters may be passed later in a calling scope.
<!-- .element: class="fragment fade-in" -->

Things from a capture list exist as a lambda internal members.
<!-- .element: class="fragment fade-in" -->

___

## Capture list values

* <!-- .element: class="fragment fade-in" --> <code>[]</code> - capture nothing
* <!-- .element: class="fragment fade-in" --> <code>[a]</code> - capture variable <code>a</code> by copy (value)
* <!-- .element: class="fragment fade-in" --> <code>[&a]</code> - capture variable <code>a</code> by reference
* <!-- .element: class="fragment fade-in" --> <code>[a, &b]</code> - capture <code>a</code> by copy and <code>b</code> by reference
* <!-- .element: class="fragment fade-in" --> <code>[=]</code> - capture everything by copy
* <!-- .element: class="fragment fade-in" --> <code>[&]</code> - capture everything by reference
* <!-- .element: class="fragment fade-in" --> <code>[&, a]</code> - capture <code>a</code> by copy and everything else by reference
* <!-- .element: class="fragment fade-in" --> <code>[=, &a]</code> - capture <code>a</code> by reference and everything else by copy
* <!-- .element: class="fragment fade-in" --> <code>[this]</code> - capture <code>this</code> pointer <b>by reference</b> (lambda can modify current class object)
* <!-- .element: class="fragment fade-in" --> <code>[*this]</code> - (C++17) capture <code>this</code> pointer by copy (creates a copy of current object)

`this` is captured anyway when either `[=]` or `[&]` are used and **in both cases allow to modify** the current object
<!-- .element: class="fragment fade-in" -->

___

### When using `[&]` may not be safe?

___

## Examples

```cpp
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

* <!-- .element: class="fragment fade-in" --> <code>[i, i]</code>
  * <!-- .element: class="fragment fade-in" --> error, <code>i</code> repeated
* <!-- .element: class="fragment fade-in" --> <code>[&, &i]</code>
  * <!-- .element: class="fragment fade-in" --> error, by-reference capture when by-reference is the default
* <!-- .element: class="fragment fade-in" --> <code>[this, *this]</code>
  * <!-- .element: class="fragment fade-in" --> error, <code>this</code> repeated
* <!-- .element: class="fragment fade-in" --> <code>[&, this]</code>
  * <!-- .element: class="fragment fade-in" --> OK, equivalent to <code>[&]</code>
* <!-- .element: class="fragment fade-in" --> <code>[&, this, i]</code>
  * <!-- .element: class="fragment fade-in" --> OK, equivalent to <code>[&, i]</code>
* <!-- .element: class="fragment fade-in" --> <code>[=, this]</code>
  * <!-- .element: class="fragment fade-in" --> C++17 - error, since C++20 OK, same as <code>[=]</code>

___

## Lambda capture expressions (C++14)

C++11 lambda functions capture variables declared in their outer scopes by value-copy or by reference. This means that a value members of a lambda cannot be **move-only** types.
<!-- .element: class="fragment fade-in" -->

C++14 allows captured members to be initialized with arbitrary expressions. This allows both capture by value-move and declaring arbitrary members of the lambda, without having a correspondingly named variable in an outer scope.
<!-- .element: class="fragment fade-in" -->

```cpp
auto lambda = [value = 1] { return value; };
```
<!-- .element: class="fragment fade-in" -->

```cpp
std::unique_ptr<int> ptr(new int(10));
auto anotherLambda = [value = std::move(ptr)] { return *value; };
```
<!-- .element: class="fragment fade-in" -->

Variable initialized on capture list have `auto` type. It is deduced from the expression.
<!-- .element: class="fragment fade-in" -->

___

## Exercise

### `02_asterisks.cpp`

Create a lambda, which prints `*` characters. Each lambda call should produce a string longer by one `*`.

Example:

* `*`
* `**`
* `***`
* etc.
