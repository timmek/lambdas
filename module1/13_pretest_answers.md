<!-- .slide: data-background="#111111" -->

# Pre-test

## Answers

___

## 1. Which lambda function is valid?

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

## 2. Which capture lists are correctly formed?

Assume that all variables exist.

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

## Post-test

The link to post-test will be sent to you in a next week.

It's better to forget some of the content and refresh your knowledge later.

It enhances knowledge retention :)

___

## Homework

Write a lambda that returns lambda that returns lambda and use them in callbacks to model TCP connection handshake:
- SYN
- ACK
- SYN ACK

___

## Feedback

* What could be improved in this training?
* What was the most valuable for you?
* [Training evaluation](https://forms.gle/qEZFvYKdgbxkyxYj7)
