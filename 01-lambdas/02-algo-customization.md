<!-- .slide: data-background="#111111" -->

# Konkretyzowanie algorytmów STL

___

## Jak posortować kontener?

```cpp
std::vector<double> diffs = {1.1, -0.2, -1.3, 0.8, 0.1, -0.3}
```

### Użyć `std::sort`
<!-- .element: class="fragment fade-in" -->

```cpp
std::sort(diffs.begin(), diffs.end());
```
<!-- .element: class="fragment fade-in" -->

Domyślnie sortowanie odbywa się przy użyciu funktora `std::less`, która wywołuje  `operator<` do porównywania argumentów.
<!-- .element: class="fragment fade-in" -->

### Wynik
<!-- .element: class="fragment fade-in" -->

`{-1.3, -0.3, -0.2, 0.1, 0.8, 1.1}`
<!-- .element: class="fragment fade-in" -->

___

## Jak posortować kontener po wartościach bezwzględnych?

Przekazać dodatkową funkcję, która będzie określała jak sortować elementy.
<!-- .element: class="fragment fade-in" -->

```cpp
bool absoluteCompare(double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
}
std::sort(diffs.begin(), diffs.end(), absoluteCompare);
```
<!-- .element: class="fragment fade-in" -->

### Wynik
<!-- .element: class="fragment fade-in" -->

`{0.1, -0.2, -0.3, 0.8, 1.1, -1.3}`
<!-- .element: class="fragment fade-in" -->

#### Skąd się dowiedzieć jaką sygnaturę powinien posiadać ten obiekt funkcyjny?
<!-- .element: class="fragment fade-in" -->

___

## Funkcje ukonkretniające

Każdy algorytm posiada dokumentację, w której powinna być wyspecyfikowana taka funkcja.

[Sprawdź `std::sort` na cppreference.com](https://en.cppreference.com/w/cpp/algorithm/sort)

___

## Najczęstsze typy funkcji

* <!-- .element: class="fragment fade-in" --> (unary) predicate
  * zwraca `bool`, przyjmuje 1 argument
* <!-- .element: class="fragment fade-in" --> binary predicate
  * zwraca `bool`, przyjmuje 2 argumenty
* <!-- .element: class="fragment fade-in" --> comparator
  * zwraca `bool`, przyjmuje 2 argumenty

___

## Co to jest *obiekt funkcyjny*?

Jakikolwiek obiekt, który można wywołać za pomocą operatora wywołania - `operator()`.
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> wskaźnik na funkcję
* <!-- .element: class="fragment fade-in" --> funktor
* <!-- .element: class="fragment fade-in" --> wyrażenie lambda
* <!-- .element: class="fragment fade-in" --> <code>std::function</code>
* <!-- .element: class="fragment fade-in" --> funkcja?
  * <!-- .element: class="fragment fade-in" --> nie, funkcja nie jest <i>obiektem funkcyjnym</i>, ale jest bezpośrednio i niejawnie konwertowana na <i>wskaźnik na funkcję</i>

___

## Sortowanie z funkcją

```cpp
bool absoluteCompare(double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
}
std::sort(diffs.begin(), diffs.end(), absoluteCompare);
```
<!-- .element: class="fragment fade-in" -->

## Sortowanie z funktorem
<!-- .element: class="fragment fade-in" -->

```cpp
struct AbsoluteCompare {
    bool operator()(double rhs, double lhs) {
        return std::abs(rhs) < std::abs(lhs);
    }
};
std::sort(diffs.begin(), diffs.end(), AbsoluteCompare{});
```
<!-- .element: class="fragment fade-in" -->

___

## Sortowanie z lambdą

### Lambda nazwana (named)
<!-- .element: class="fragment fade-in" -->

```cpp
auto absoluteCompare = [](double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
};
std::sort(diffs.begin(), diffs.end(), absoluteCompare);
```
<!-- .element: class="fragment fade-in" -->

### Lambda nienazwana (unnamed)
<!-- .element: class="fragment fade-in" -->

```cpp
std::sort(diffs.begin(), diffs.end(), [](double rhs, double lhs) {
    return std::abs(rhs) < std::abs(lhs);
});
```
<!-- .element: class="fragment fade-in" -->

___

## Dlaczego mamy aż tyle sposobów?

![What if...](../img/what_if.png)
<!-- .element: class="fragment fade-in" style="text-align: center" -->

___

## Wyrażenia lambda

**Uzasadnienie**: programowanie funkcyjne, jednorazowe funkcje in-place, bardziej uniwersalne przekazywanie funkcji
<!-- .element: class="fragment fade-in" -->

Wyrażenie lambda jest zwykle definiowane bezpośrednio w miejscu jego użycia. Zwykle jest używane jako parametr innej funkcji, która oczekuje wskaźnika do funkcji lub funktora - ogólnie obiektu wywoływalnego.
<!-- .element: class="fragment fade-in" -->

___

## Zadanie

### `01_threeWays.cpp`

Użyj odpowiedniego algorytmu STL, aby sprawdzić, czy wszystkie elementy wektora *numbers* są podzielne przez 3.

```cpp
std::vector numbers = {18, 21, 36, 90, 27, 14, 103};
```

Zaimplementuj 3 wersje:

* lambda
* funktor
* funkcja

___

### Rozwiązanie - lambda

```cpp
bool result = std::all_of(numbers.begin(), numbers.end(), [](int number){
    return number % 3 == 0;
});
```
<!-- .element: class="fragment fade-in" -->

___

#### Rozwiązanie - funkcja
<!-- .element: class="fragment fade-in" -->

```cpp
bool isDivisibleBy3(int number) {
    return number % 3 == 0;
}
bool result = std::all_of(numbers.begin(), numbers.end(), isDivisibleBy3);
```
<!-- .element: class="fragment fade-in" -->

___

### Rozwiązanie - funktor

```cpp
struct DivisibleBy {
    DivisibleBy(int n) : n_{n} {}
    bool operator()(int number) {
            return number % n_ == 0;
    }
private:
    int n_;
};
bool result = std::all_of(numbers.begin(), numbers.end(), DivisibleBy{3});
```
<!-- .element: class="fragment fade-in" -->

___

## Twoje wnioski

### Co to jest wyrażenie lambda?

* <!-- .element: class="fragment fade-in" --> Obiekt funkcyjny
* <!-- .element: class="fragment fade-in" --> Prosta i krótka w zapisie - <code>[](){}</code>
* <!-- .element: class="fragment fade-in" --> Używana, aby krócej zapisywać funktory
* <!-- .element: class="fragment fade-in" --> Zapewnia lepszą czytelność kodu
* <!-- .element: class="fragment fade-in" --> Typ lambdy nazywa się <i>domknięciem</i> ("closure class")
* <!-- .element: class="fragment fade-in" --> Domknięcie jest znane tylko kompilatorowi
* <!-- .element: class="fragment fade-in" --> Aby stworzyć nazwaną lambdę jej typ musi być <code>auto</code>
