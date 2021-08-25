<!-- .slide: data-background="#111111" -->

# Problemy z czasem życia obiektów

___

## Wiszące referencje

### (ang. dangling references)

Głównym problemem jaki napotkasz przy lambdach będą tzw. wiszące referencje.
<!-- .element: class="fragment fade-in" -->

Lambda jest tworzona w miejscu, w którym jest zdefiniowana - na stosie. Przechwycone zmienne zawsze są dostępne w tym miejscu.
<!-- .element: class="fragment fade-in" -->

Lambda może zostać wywołana później, w innym miejscu. Można ją przekazać w dowolne miejsce. Niektóre lokalne zmienne nie będą wtedy dostępne. Jeśli przechwyciliśmy je przez referencję to mamy niezdefiniowane zachowanie (UB).
<!-- .element: class="fragment fade-in" -->

___

## Zadanie

### `05_dangling.cpp`

Napraw kod.

Chcemy, aby generator dostarczał kolejne liczby zaczynając od 0.

Prawidłowe wyjście: `0123456789`
