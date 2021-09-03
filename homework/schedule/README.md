# Schedule

1. Napisz funkcję `schedule()`, która przyjmuje dwa parametry:
   1. Pierwszy parametr to dowolną funkcję `func`, która nie przyjmuje żadnego argumentu i nic nie zwraca
   2. Drugi parametr to okres czasu `duration` wyrażony w sekundach (użyj biblioteki `std::chrono`)
   Funkcja `schedule()` ma odczekać podany okres czasu `duration`, a potem wywołać funkcję `func`.
2. Napisz również przeciążenie funkcji `schedule()`, które oprócz okresu czasu ma przyjąć dowolną funkcję, która przyjmuje `int` i nic nie zwraca. Pomyśl jak przekazać ten argument `int` do tej funkcji.
3. Napisz kolejne przeciążenie, które będzie przyjmować funkcje, które przyjmują `std::string` oraz `double` jako swoje argumenty i nic nie zwracają.

Na gałęzi `schedule` masz już gotowy szkielet do tej aplikacji. Tam dostarcz swój kod.

## Bonus

Zaimplementuj schedule jako funkcję szablonową. Wystarczy wtedy tylko jedna jej wersja, bez żadnych przeciążeń.

Uwaga, to trudne zadanie na tym etapie kursu! Ale nie bój się eksperymentować i poprosić o pomoc na Discordzie :) 
