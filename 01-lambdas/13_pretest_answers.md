<!-- .slide: data-background="#111111" -->

# Pre-test 🤯

## Answers

___

## 1. Które lambdy są poprawne?

1. <!-- .element: class="fragment highlight-green" --> <code>[]() -> int { return 4; };</code>
1. <!-- .element: class="fragment highlight-red" --> <code>int [](){ return 4; };</code>
1. <!-- .element: class="fragment highlight-red" --> <code>auto [](){ return 4; };</code>
1. <!-- .element: class="fragment highlight-green" --> <code>[]() -> auto {return 4; };</code>
1. <!-- .element: class="fragment highlight-green" --> <code>[](){ return 4; };</code>
1. <!-- .element: class="fragment highlight-green" --> <code>[] { return 4; }</code>
1. <!-- .element: class="fragment highlight-red" --> <code>[] mutable { return 4; }</code>
1. <!-- .element: class="fragment highlight-red" --> <code>[] -> int { return 4; }</code>
1. <!-- .element: class="fragment highlight-red" --> <code>int []{ return 4; }</code>

Note: 1, 4, 5, 6

___

## 2. Które listy przechwytywania są poprawnie zapisane?

Zakładamy, że wszystkie użyte zmienne istnieją.

1. <!-- .element: class="fragment highlight-red" --> <code>[=, this]</code>
2. <!-- .element: class="fragment highlight-green" --> <code>[&, this]</code>
3. <!-- .element: class="fragment highlight-red" --> <code>[this, *this]</code>
4. <!-- .element: class="fragment highlight-red" --> <code>[&, &a]</code>
5. <!-- .element: class="fragment highlight-red" --> <code>[a, &]</code>
6. <!-- .element: class="fragment highlight-red" --> <code>[&, a, &b]</code>
7. <!-- .element: class="fragment highlight-red" --> <code>[=, a, &b]</code>
8. <!-- .element: class="fragment highlight-green" --> <code>[=, &a]</code>
9. <!-- .element: class="fragment highlight-red" --> <code>[=, *a]</code>

Note: 1 is an error in C++17, but not in C++20, 2, 8

___
