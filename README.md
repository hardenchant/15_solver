# Алгоритмы. Вариант 38

## Usage:
Fast track:
```
pypy3 solver15.py in.dat out.ans
```
Long track:
```
python3.5 solver15.py in.dat out.ans
```
Unit tests:
```
python3.5 test_solver15.py
```
Some other tests:
```
python3.5 tests.py
pypy3 tests.py         #faster stronger harder better
```
Testing can take a long time (over 20 - 40 sec), be patient and have a tea.


## Задача

Постройте программу для решения головоломки «Пятнашки»
произвольного размера. 

---
## Разбор задачи

Игра представляет собой поле 4 на 4 (классический вариант), на котором расположены 15 фишек, пронумерованных числами от 1 до 15, а одно поле оставлено пустым. Требуется, передвигая на каждом шаге какую-либо фишку на свободную позицию, прийти в конце концов к следующей позиции:
```
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 __
```
[Доказательство NP полноты](https://www.aaai.org/Papers/AAAI/1986/AAAI86-027.pdf)
для кратчайшего решения пятнашек размерности n.
    
### Проверка на существование решения

Пусть дана некоторая позиция `a` на доске:
```
a1  a2  a3  a4
a5  a6  a7  a8
a9  a10 a11 a12
a13 a14 a15 a16
```
где один из элементов `a[z]` равен нулю и обозначает пустую клетку.
Рассмотрим перестановку:
```
a[1]a[2]...a[z-1]a[z+1]...a[15]a[16]
```
(т.е. перестановка чисел, соответствующая позиции на доске, без нулевого элемента.

Обозначим через **N** количество инверсий в этой перестановке (т.е. количество таких элементов `a[i]` и `a[j]`, что `i < j`, но `a[i] > a[j]`).

Далее, пусть **K** — номер строки, в которой находится пустой элемент (т.е. `K = (z - 1) \ div n + 1`).

Тогда, решение существует тогда и только тогда, когда:
 
 `N + K = 0 mod 2`.

[Доказательство](http://www.cs.cmu.edu/afs/cs/academic/class/15859-f01/www/notes/15-puzzle.pdf).

### Решение

Весь процесс поиска решения в "Пятнашках" можно представить как задачу поиска на графе. Вершинами такого графа будут состояния поля головоломки, полученные в результате перемещения костяшек.

Поиск решения можно свести к поиску терминального состояния игрового поля (обычно, в качестве терминальной, выбирается расстановка костяшек, упорядоченных по возрастанию слева направо, сверху вниз - 1,2,3,... ).

Для решения задачи поиска терминальной вершины на графе, можно использовать алгоритмы полного перебора (поиск в глубину или ширину), но количество возможных решений (возможных перестановок) скорее всего окажется слишком большим (сложность в таком случае: О(n ^ 2 !)),
где n - количество всех вершин графа (а для пятнашек размера 4х4 это уже 16! если отсекать циклы)

Возможные алгоритмы для решения:
- Поиск в ширину
- Поиск в глубину
- Алгоритм Флойда
- Алгоритм Форда-Беллмана
- Алгоритм Дейкстры
- Алгоритм A*

Все неинформированные методы поиска сразу отсекаются, т.к. перебор всех вершин займёт большее количество времени.

По той же причине можно убрать алгоритмы поиска пути от каждой вершины до каждой. И остается только А*.

Так же в [статье с доказательством](http://www.cs.cmu.edu/afs/cs/academic/class/15859-f01/www/notes/15-puzzle.pdf) приводится описание полиномиально - приближенного алгоритма. По принципу работы он похож на А* - использует эвристическую оценку расстояния до терминальной вершины. Минусом является сложность понимания (86 страниц на английском) и реализации.

## Алгоритм A*

Алгоритм A* позволяет существенно сократить количество состояний для перебора, путем применения некоторой дополнительной информации - эвристики. В качестве такой информации для пятнашек я возьму несколько эвристик описанных ниже.

Алгоритм A* предполагает наличие двух списков вершин графа: открытого и закрытого. В первом находятся вершины, еще не проверенные алгоритмом, а во втором те вершины, которые уже встречались в ходе поиска решения.

На каждом новом шаге, из списка открытых вершин выбирается вершина с наименьшим весом (поэтому использовалась очередь). Вес (F) каждой вершины вычисляется как сумма расстояния от начальной вершины до текущей (G) и эвристическое предположение о расстоянии от текущей вершины, до терминальной (H).

**Fi = Gi + Hi**, где i - текущая вершина (состояние игрового поля).

### Оценка сложности
Временная сложность алгоритма A* зависит от эвристики.
В худшем случае, число вершин растёт **экспоненциально по сравнению с длиной оптимального пути**, но сложность становится полиномиальной, когда эвристика удовлетворяет следующему условию:

```
h(x) - h*(x) <= O(log(h*(x))
```
где h* — точная оценка расстояния из вершины x к цели.
Другими словами, ошибка h(x) не должна расти быстрее, чем логарифм от оптимальной эвристики.

### Оценка памяти
В худшем случае алгоритму приходится помнить экспоненциальное количество узлов.
Есть так же улучшенные по памяти версии алгоритма А*: IDA*, MA* и Recursive Best-First Search.
Но для задачи решения пятнашек они будут потреблять сравнимое количество памяти за счёт использования рекурсии (400-500 Мб для размерности 4х4 на A*, против 300-350 Мб на IDA*).
Так же для рекурсивных алгоритмов требуется доработка для контроля глубины рекурсии, иначе они потребляют гораздо больше памяти.


## Эвристики

Все эвристики будут рассмотрены на примере пятнашек размерности 3, но так же являются верными и для размерности n.

После непродолжительного поиска, было принято решение взять за основу сумму следующих эвристик:

### Manhattan distance

Функция: ***manh_distance()***


Основная эвристика, это сумма расстояний по строкам и столбцам от текущего расположения костяшки до ее правильной позиции. 
Допустимость следует из того, что за один ход перемещается только одна фишка, и расстояние между этой фишкой и её конечной позицией изменяется на 1

Пример:

| **1** | **2** | **3** |  
--- | --- | ---
| **6** | **5** | **4** | 
| **7** | **8** |  |

***this->manh_distance()*** // == 4

### Linear conflict

Функция: ***linear_conflict()***

Костяшка I и костяшка J находятся в линейном конфликте по строке, если они обе стоят в своей строке, но костяшка I находится левее костяшки J, хотя на самом деле должна быть справа. Мы должны подвинуть одну из костяшек со строки, поэтому можем добавить 2 к общей эвристике. Аналогичным образом рассматривается линейный конфликт по столбцу. Правый нижний угол в эвристике не рассматривается, так как очень сложно скомбинировать этот случай с **last_move**.

Пример:

| **2** | **1** | **k** |  
--- | --- | ---
| **k** | **k** | **k** | 
| **k** | **k** | **k** |

***this->manh_distance()*** // H + 2

### Corner tiles

Функция: ***corner_tiles()***

Пусть на месте 1 стоит любая другая костяшка, а один из её соседей (или оба), 
уже выставлен на своё место, тогда чтобы поставить единицу на место соседей придётся подвинуть. Прибавляем 2 к общей эвристике. Если соседи уже участвуют в **linear_conflict**, то всё учтено и 2 добавлять уже не нужно.

Пример:

| **!1** | **2** | **k** |  
--- | --- | ---
| **k** | **k** | **k** | 
| **k** | **k** | **k** |

| **!1** | **k** | **k** |
--- | --- | ---
| **4** | **k** | **k** | 
| **k** | **k** | **k** |

**this->corner_tiles()** // == H + 2 в обоих случаях

### Last move

Функция: ***last_move()***

На последнем ходу у нас есть два варианта:

| **1** | **2** | **3** |
--- | --- | ---
| **4** | **5** | **6** | 
| **7** |  | **8** |

| **1** | **2** | **3** |
--- | --- | ---
| **4** | **5** |  | Считается, что к
| **7** | **8** | **6** |

**this->last_move()** // == H + 0 в обоих случаях, при другом расположении 6 и 8 прибавляем 2.

Если костяшки не находятся на требуемых позициях, манхэттенское расстояние не учитпроверка на сущестывает переход через угол. Следовательно, мы можем добавить к нему 2.

## Оценка необходимости подбора оптимальных эвристик
Попробуем увидеть разницу в работе алгоритма с различным числом эвристик.

Все варианты тестировались так:
```
time pypy3 solver15
```
Со следующим набором входных данных:
```
5  1  9  3
11 13 6  8
14 10 4  15
0  12 7  2
```

Для начала просто посмотрим как долго алгоритм работает с простейшей эвристикой:
```
simple_heur()  # число фишек стоящих не на своих местах
time: >4m
len(node_hash): max
# алгоритм так и не закончил работу,
# будем считать эвристику неоптимальной
```

Будем наращивать функцию h(x), начиная с h(x) = manhattan_distance().

Попробуем запустить алгоритм с одной лишь эвристикой manhattan_distance():

```
time: 1m23,330s
len(node_hash): 696569
len(decision): 41
```

Длина списка вершин которые мы обошли просто огромна,
т.к. большинство эвристик будут отличаться на слишком малую величину, алгоритму придётся обойти большое количество вершин прежде чем станет понятно где вершины с наименьшим весом.

Далее добавим простейшую (с малым весом) дополнительную эвристику last_move():
```
time: 36,829s
len(node_hash): 283798
len(decision): 41
```
Увидим сокращение пройденных вершин в 2,5 раза и, само собой, такой же результат по длине решения. Сократили число рассматриваемых вершин, получили и сокращение времени.
Это произошло из за большей дифференциации весов вершин. Алгоритм с большей вероятностью выбирает правильный путь.

Добавив эвристику corner_tiles() увидим следующее:
```
time: 1m49,561s
len(node_hash): 192863
len(decision): 41
```
Количество рассматриваемых вершин уменьшилось, но время увеличилось.
Это произошло из за сложности эвристической функции corner_tiles.
Отсюда можно сделать вывод, что эвристическая функция должна быть не только близка к значение реального расстояния, но и быть довольно легковесной, т.к. применяться она будет к большому количеству вершин.

По той же причине была убрана эвристика linear_conflict().
Таким образом, итоговая эвристическая функция выглядит как:
```
h(x) = manhattan_distance() + last_move()
```


## Описание реализации

В файле ```a_star.py``` находится реализация основого алгоритма и краткое описание его работы.

В начале работы просматриваются узлы, смежные с начальным; выбирается тот из них, который имеет минимальное значение f(x), после чего этот узел раскрывается. На каждом этапе алгоритм оперирует с множеством путей из начальной точки до всех ещё не раскрытых (листовых) вершин графа — множеством частных решений, — которое размещается в очереди с приоритетом. Приоритет пути определяется по значению f(x) = g(x) + h(x). Алгоритм продолжает свою работу до тех пор, пока значение f(x) целевой вершины не окажется меньшим, чем любое значение в очереди, либо пока всё дерево не будет просмотрено. Из множества решений выбирается решение с наименьшей стоимостью.

Для сравнения эвристик для каждой цепочки решений использую очередь с приоритетами, для работы которой перегружаю оператор \_\_lt\_\_()

Для хранения списка пройденных вершин использую хэш таблицу или dict в python.

Имплементация самого решателя пятнашек находится в файле ```solver15.py```.

Внутри определена функция для подсчёта Манхэттенского расстояния и класс chain15 содержащий конкретную реализацию представления пятнашек в виде графа. К каждой функции приведено описание или принцип работы ясен из её названия.

Файлы ```test_a_star.py```, ```test_solver15.py```, ```tests.py``` содержат тесты и примеры использования для алгоритма A*, класса перевода пятнашек в задачу на графе, программы решения пятнашек соответственно. Тесты описаны в формате docstring.


## Формат входных и выходных данных
На вход первой подаём состояние поля, оно должно соответствовать разумному смыслу, т.к. никак не валидируется, пустой символ это 0:
```
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 0
```
На выходе ~~даст бог~~ получим первой строкой число ходов до решения, а далее состоянии доски на каждый ход:
```
353
1 2 3 4
5 6 7 8
9 10 11 12
13 15 14 0
----------
1 2 3 4
5 6 7 8
9 10 11 12
13 15 0 14
...
...
...
```

 ... либо:
 ``` NO SOLUTION FOR YOUR COMBINATION```


## Что можно улучшить
- Эвристики (сложно, но можно найти в англоязычных статейках умные варианты)
- При равенстве функций f (эвристических расстояний) очередь с приоритетами работает как стек (LIFO), это зависит от реализации. Можно узнать как в конкретном случае (для пятнашек) это влияет на скорость нахождения решения. И, например, заменить реализацию очереди на свою - FIFO в случае равенства эвристик.
- Для случая из предыдущего пункта получаем:
При LIFO - поиск в глубину,
при FIFO - в ширину.
В зависимости от величины эвристики можем подставлять ту или иную очередь.
Тоесть чем меньше эвристика тем ближе мы к решению, тем выгоднее нам уходить вглубь.
И наоборот, при большой величине эвристической функции интересно посмотреть в ширину, не уменьшается ли она там.

## Интересное отступление
Можем из алгоритма A* получить Greedy Wide Algorithm
убрав g() из: 
```
f() = h() + g()
```

Тогда получим для следующих входных данных:
```
5  1  9  3
11 13 6  8
14 10 4  15
0  12 7  2
```
Следующие результаты:
```
time: 1,641s
len(node_hash): 2721
len(decision): 291
```
Заметим намного меньшее время по сравнению с предыдущими замерами на A star.
Но так же и возросшую длину решения.
Это произошло из за того что алгоритм следит лишь за весов следующей вершины - берёт минимальную. А сколько вершин было позади его уже не интересует.
Число рассмотренных вершин так же, меньше.

Можно сделать вывод что в случаях, когда необходимо получить любое решение и его длина не важна, выгоднее использовать такой вариант.

Полный A star в свою очередь находит оптимальное решение.

## Оптимизация
Посмотрим результаты работы профилировщика для жадного алгоритма (так как он работает быстрее):
``` bash
python3.5 -m cProfile -s time solver15.py
```
```
Start from:
5 1 9 3 
11 13 6 8 
14 10 4 15 
0 12 7 2
-----
Result:
1 2 3 4 
5 6 7 8 
9 10 11 12 
13 14 15 0 
-----
414 moves


         92069971 function calls (92069970 primitive calls) in 53.480 seconds

   Ordered by: internal time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
  1796766   24.731    0.000   48.634    0.000 solver15.py:28(manh_dst)
 28878926   20.555    0.000   24.051    0.000 solver15.py:6(manh_dst_matrix)
 57757852    3.496    0.000    3.496    0.000 {built-in method builtins.abs}
   898383    0.789    0.000   50.037    0.000 solver15.py:65(__lt__)
    39392    0.778    0.000    1.712    0.000 solver15.py:68(get_neighbours)
  1796766    0.614    0.000   49.248    0.000 solver15.py:62(f)
   118045    0.598    0.000    0.682    0.000 solver15.py:23(__init__)
        1    0.553    0.553   53.391   53.391 a_star.py:11(a_star)
   157437    0.480    0.000    0.480    0.000 solver15.py:35(last_node)
    39393    0.363    0.000   30.647    0.001 {built-in method _heapq.heappop}
    75215    0.247    0.000   20.000    0.000 {built-in method _heapq.heappush}
        1    0.088    0.088   53.480   53.480 solver15.py:1(<module>)
   118045    0.066    0.000    0.066    0.000 {built-in method math.sqrt}
   118043    0.051    0.000    0.051    0.000 {method 'copy' of 'list' objects}
    39392    0.030    0.000    0.030    0.000 {method 'index' of 'list' objects}
   118043    0.022    0.000    0.022    0.000 {method 'append' of 'list' objects}
   118049    0.018    0.000    0.018    0.000 {built-in method builtins.len}

```
Видно, что большая часть нагрузки приходится на эвристическую функцию:
```python
    def manh_dst(self):
        dst = 0
        for i in range(0, int(self.size ** 2)):
            dst += manh_dst_matrix((self.board_state[i] - 1) %
                                   (self.size ** 2), i, self.size)
        return int(dst)
```
Не помешает что нибудь улучшить:
- a*a быстрее чем a ** 2
- да и вообще зачем каждый раз считать квадрат, можно сделать отдельную переменную

Получаем время 41.259s с теми же данными, что +22% к скорости.

```time python3.5 solver15.py```

Без профилировщика: 27,313s

Выходит всё же долго (тот же алгоритм на C++ работает за 1,421s). Можем использовать оптимизированные сборки Python:
```
time pypy3 solver15.py
```

Получаем 4,128s. Что всего в 4 раза медленнее чем на С++.

## Источники
- https://www.cs.princeton.edu/courses/archive/fall12/cos226/assignments/8puzzle.html

- http://www.cs.cmu.edu/afs/cs/academic/class/15859-f01/www/notes/15-puzzle.pdf

- http://book.etudes.ru/toc/15puzzle/

- https://www.aaai.org/Papers/AAAI/1986/AAAI86-027.pdf