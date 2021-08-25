<!-- .slide: data-background="#111111" -->

# Lista przechwytująca

___

<code style="font-size: 0.7em">
<span style="color: #cf802a">[captures]</span>(params) specifiers [[attributes]] -> ReturnType { body };
</code>

## `[captures]`

Przechwytuje zmienne dostępne w lokalnym zakresie, aby były widoczne wewnątrz lambdy.
<!-- .element: class="fragment fade-in" -->

Ciało funkcji lambda to oddzielny zakres. Aby przekazać coś do środka należy to zrobić przez parametry lub poprzez listę przechwytującą.
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

## Dlaczego są 2 sposoby na przekazanie obiektów?

Lambda może zostać utworzona w jednym zakresie, a wywołana w innym.
<!-- .element: class="fragment fade-in" -->

Zmienne z lokalnego zakresu są przechwytywane przez listę przechwytującą podczas tworzenia lambdy, natomiast parametry podaje się podczas wywołania lambdy.
<!-- .element: class="fragment fade-in" -->

Obiekty z listy przechwytującej istnieją jako wewnętrzne pola w lambdzie (pamiętaj, że lambda to funktor, czyli zwykła klasa z `operatorem()`)
<!-- .element: class="fragment fade-in" -->

___

## Demo na [`cppinsights.io`](https://cppinsights.io)

___

## Wartości na liście przechwytującej

* <!-- .element: class="fragment fade-in" --> <code>[]</code> - nic nie przechwytujemy
* <!-- .element: class="fragment fade-in" --> <code>[a]</code> - przechwytujemy zmienną  <code>a</code> przez kopię (wartość)
* <!-- .element: class="fragment fade-in" --> <code>[&a]</code> - przechwytujemy zmienną <code>a</code> przez referencję
* <!-- .element: class="fragment fade-in" --> <code>[a, &b]</code> - przechwytujemy <code>a</code> przez kopię i <code>b</code> przez referencję
* <!-- .element: class="fragment fade-in" --> <code>[=]</code> - przechwytujemy wszystko przez kopię
* <!-- .element: class="fragment fade-in" --> <code>[&]</code> - przechwytujemy wszystko przez referencję
* <!-- .element: class="fragment fade-in" --> <code>[&, a]</code> - przechwytujemy <code>a</code> przez kopię, a wszystko pozostałe przez referencję
* <!-- .element: class="fragment fade-in" --> <code>[=, &a]</code> - przechwytujemy <code>a</code> przez referencję, a wszystko pozostałe przez kopię
* <!-- .element: class="fragment fade-in" --> <code>[this]</code> - przechwytujemy wskaźnik <code>this</code> <b>przez referencję</b> (lambda może zmodyfikować obiekt klasy)
* <!-- .element: class="fragment fade-in" --> <code>[*this]</code> - (C++17) przechwytujemy wskaźnik <code>this</code> przez kopię (tworzona jest kopia aktualnego obiektu)

`this` jest mimo wszystko i tak przechwytywane, gdy używamy `[=]` lub `[&]` i **w obu przypadkach pozwala na modyfikację** obecnego obiektu klasy.
<!-- .element: class="fragment fade-in" -->

___

### Kiedy użycie `[&]` może być niebezpieczne?

___

## Przykład

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

Czy poniższe listy przechwytujące są poprawne?

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

Lambdy w C++11 przechwytują zmienne tylko przez kopię lub referencję. Przez to nie możemy przechwytywać obiektów, które można tylko przenosić (takie jak `std::unique_ptr`).
<!-- .element: class="fragment fade-in" -->

C++14 dopuszcza przenoszenie, dzięki możliwości definiowania nowych zmiennych na liście przechwytującej.
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

Na liście przechwytującej nie podajemy typów nowo zdefiniowanych obiektów. Typy są dedukowane na podstawie przypisania. Jest tam po prostu typ `auto`.
<!-- .element: class="fragment fade-in" -->
