<!-- .slide: data-background="#111111" -->

# `std::function` vs wskaźnik na funkcję

___

## Konwersja na wskaźnik na funkcję #1

Lambda, która nie przechwytuje niczego jest konwertowalna na wskaźnik na funkcję.

```cpp
#include <iostream>
using namespace std;

auto foo(int (*fptr)()) {
    auto result = fptr();
    return result;
}

int main() {
    auto result = foo([] { return 5; });
    std::cout << result;
    return 0;
}
```

___

## Konwersja na wskaźnik na funkcję #2

Lambda, która coś przechwytuje nie może zostać skonwertowana na wskaźnik na funkcję.

```cpp
#include <iostream>
using namespace std;

auto foo(int (*fptr)()) {
    auto result = fptr();
    return result;
}

int main() {
    int value = 5;
    // auto result = foo([value] { return value; });
    // error: cannot convert ‘main()::<lambda()>’ to ‘int (*)()’
    // std::cout << result;
    return 0;
}
```

___

## `std::function`

`std::function` jest specjalnym wrapperem, który może trzymać obiekty wywoływalne dowolnego typu. W szczególności wszystkie rodzaje lambd, ale też każdy funktor czy wskaźnik na funkcję.

`std::function` jest w nagłówku `<functional>`.

```cpp
#include <iostream>
#include <functional>

auto foo(std::function<int()> fptr) {
    auto result = fptr();
    return result;
}

int main() {
    int value = 5;
    std::cout << foo([value] { return value; });
    return 0;
}
```

___

## Sygnatury funkcji

### Wskaźniki na funkcje
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>int (*f)()</code> - f takes no arguments and returns and int
* <!-- .element: class="fragment fade-in" --> <code>void (*f)(int)</code> - f takes an int and returns nothing
* <!-- .element: class="fragment fade-in" --> <code>double (*f)(int, string)</code> - f takes an int and a string and returns double

Aby uzyskać typ szablonowy potrzebny do `std::function` usuwamy część określającą nazwę wskaźnika `(*f)`. Samo `std::function<>` możemy nazwać nazwą wskaźnika `f`.
<!-- .element: class="fragment fade-in" -->

### `std::function`
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> <code>std::function&lt;int()> f</code> - f takes no arguments and returns an int
* <!-- .element: class="fragment fade-in" --> <code>std::function&lt;void(int)> f</code> - f takes an int and returns nothing
* <!-- .element: class="fragment fade-in" --> <code>std::function&lt;double(int, string)> f</code> - f takes an int and a string and returns double

___

## `std::function`

> `std::function` is a general-purpose polymorphic function wrapper. Instances of std::function can store, copy, and invoke any Callable target - functions, lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members.
>
> -- from [cppreference.com](https://en.cppreference.com/w/cpp/utility/functional/function)

Ponieważ `std::function` jest *polimorficzne*, to uważa się je za dość "ciężki". Nie słynie ono z super wydajności. Jeśli musisz mieć jak najwydajniejszy kod i nie musisz przechowywać lub przekazywać lambd, które coś przechwytują, używać wskaźników na funkcje.

___

## puste `std::function`

`std::function` posiada operator wywołania - `operator()`, który przekazuje to wywołanie do wewnętrznego obiektu.

`std::function` może być też puste. Wywołanie pustego `std::function` skutkuje rzuceniem wyjątku `std::bad_function_call`.

___

## Zadanie

### `area.cpp`

Zmień funkcję `areaLessThan20` w lambdę.

Potem zmień ją w lambdę `areaLessThanX`, która przyjmuje `x = 20` na liście przechwytującej.

Jaki będzie problem?

Użyj `std::function`, aby rozwiązać problem.
