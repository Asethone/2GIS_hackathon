

- [2GIS_HACKATHON](#2gis_hackathon)
  - [Introduction](#introduction)
  - [Building and running](#building-and-running)
  - [List of symbols](#list-of-symbols)
  - [Brute Force algorithm](#brute-force-algorithm)
  - [Raita algorithm](#raita-algorithm)

# 2GIS_HACKATHON

## Introduction

- Все представленные алгоритмы работают с нуль-терминированной последовательностью байт (C-String). Такое решение было принято ввиду наличия уточнения о возможной бесконечной длины строки *haystack*, соответственно ожидать на вход строковый тип `std::string` не имеет смысла. Кроме того обработка, "сырой" нуль-терминированной последовательности байт будет занимать меньше времени.
- Алгоритмы основаны на идее итерирования в прямом направлении относительно начала строки *haystack* и последовательном получении доступа к ее символам. Поэтому в теории, длина такой строки ничем не ограничена. На практике, конечно же, длина такой строки ограничена максимальным размерном указателя в системе (2^64 в случае 64-разрядного процессора).
- Все алгоритмы учитывают лишь первое вхождение подстроки из *needle* в *haystack*.
- Все классы реализованы в пространстве имен `gis`. 
- Для смены алгоритма поиска предусмотрен паттерн программирования **стратегия**: объекту класса *DataSearch* необходимо предварительно методом `setSearch()` указать адрес объекта, реализующего алгоритм поиска. Список классов, реализующих данные алгоритмы:
  - Search_1
  - Search_2

## Building and running
- Для сборки алгоритма необходимо запустить команду `make` из директории *src* в проекте.
- Данные для поиска вводятся в *main.cpp* в массивы *haystack* и *needle* соответственно. Здесь же осуществляется выбор алгоритма поиска.


## List of symbols
- В этом разделе приведен список обозначений для удовства описания алогритмов.
  -  `m` - длина паттерна (в данном случае *needle*) 
  -  `n` - длина исходной строки *haystack* (введена только для описания, так как пользоваться этой величиной в алгоритме нельзя по причинам, изложенным выше)
  -  

## Brute Force algorithm
- Алгоритм простого перебора наиболее прос в реализации и обладает приемлимой скоростью для случаев, когда `m < n`. Вместе с тем, скорость данного алгоритма значительно падает на больших объемах данных, особенно, когда `m >= n`.
- Данный алгоритм не требует стадии препроцессинга, а также не потребляет дополнительной памяти.
- Алгоритм посимвольно проходится по *haystack*, сравнивая последовательность символов с *needle*. В случае совпадения не менее, чем *threshold* символов подряд, алгоритм сдвигает начало поиска на длину найденного участка и продолжает до тех пор, пока не встретит терминирующий ноль в *haystack*.
- Как видно из описания алгоритма, его реализация требует минимум трех вложенных циклов - внешний для прохода по *haystack*, следующий по вложенности - для прохода по *needle* и, наконец, наиболее вложенный - для последовательного сравнения символов. Соответственно, вычислительная сложность такого алгоритма в худшем случае составит `O(n^2*m)`.
- **Оптимизация:** Так как алгоритм учитывает лишь первое вхождение подстроки из *needle*, то после первого же нахождения совпадающей последовательности, длиной не менее *threshold* символов, из второго цикла можно выйти.

## Raita algorithm
- Алгоритм, разработанный Тимом Райта для поиска фиксированной подстроки в строке является модификацией алгоритма Бойера-Мура, который считается одним из самых быстрых для данной задачи. Для применения к данной задаче требует дополнительно написания алгоритма, выделяющего подстроки длиной не менее *threshold* символов из *needle*.
