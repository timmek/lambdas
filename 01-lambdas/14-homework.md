<!-- .slide: data-background="#111111" -->

# Praca domowa

___
<!-- .slide: style="font-size: 0.8em" -->
## Zadanie domowe

* `schedule` (10 XP)
* `template-schedule` (zaawansowane, dla chętnych) (15 XP)

## Bonusy

* +3 XP za dostarczenie każdego zadania przed 19.09.2021 (razem +6 XP)
* +1 XP za pracę w grupie dla każdej osoby z grupy za każde zadanie (razem +2 XP na osobę)

___

## `schedule`

Napisz funkcję `schedule()`, która przyjmie dowolną funkcję, która nie przyjmuje żadnego argumentu i nic nie zwraca. Ma ona wewnątrz wywołać tę funkcję.
Napisz również przeciążenie funkcji `schedule()`, które ma przyjąć dowolną funkcję, która przyjmuje `int` i zwraca `int`.

Na gałęzi `schedule` masz już gotowy szkielet do tej aplikacji. Funkcja `schedule()` jest tam odpalana asynchronicznie na oddzielnym wątku. Przy okazji możesz zobaczyć jak się pisze proste programy wielowątkowe 🙂

___

## `template-schedule`

Zaawansowane - dla chętnych

Przerób funkcję `schedule()` na szablon funkcji, który przyjmie zupełnie dowolny typ funkcji, o dowolnej liczbie i typach parametrów oraz o dowolnym typie zwracanym.
