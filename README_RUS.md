# Maze

Реализация проекта Maze.

## Описание лабиринта

Лабиринт хранится в файле в виде количества строк и столбцов, а также двух матриц, содержащих положение вертикальных и горизонтальных стен соответственно. 
В первой матрице отображается наличие стены справа от каждой ячейки, а во второй - снизу. 

Пример подобного файла:  
```
4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
```

Лабиринт, описанный в этом файле: \
![maze](img/maze.jpg)

## Описание пещер

Пещера, прошедшая 0 шагов симуляции (только инициализированная), хранится в файле в виде количества строк и столбцов, 
а также матрицы, содержащей положение "живых" и "мертвых" клеток.

Пример подобного файла:
```
4 4
0 1 0 1
1 0 0 1
0 1 0 0
0 0 1 1
```

Пещера, описанная в этом файле: \
![cave](img/cave.jpg)

## Реализация проекта Maze

Программа Maze, позволяет генерировать и отрисовывать идеальные лабиринты и пещеры:

- Программа разработана на языке C++ стандарта C++17
- Код программы находится в папке src
- Сборка программы настроена с помощью Makefile снабором целей: all, install, uninstall, clean, dvi, dist, tests
- В программе реализован графический пользовательский интерфейс на базе Qt
- В программе предусмотрена кнопка для загрузки лабиринта из файла, который задается в формате, описанном выше
- Максимальный размер лабиринта - 50х50
- Загруженный лабиринт отрисовывается на экране в поле размером 500 x 500 пикселей
- Толщина "стены" - 2 пикселя
- Размер самих ячеек лабиринта вычисляется таким образом, чтобы лабиринт занимал всё отведенное под него поле

## Генерация идеального лабиринта

- Генерирация лабиринта согласно алгоритму Эллера
- Сгенерированный лабиринт не имеет изолированных областей и петель
- Пользователем вводится только размерность лабиринта: количество строк и столбцов
- Сгенерированный лабиринт можно сохраняться в файл в формате, описанном выше

## Решение лабиринта

Программа позволяет показать решение любого лабиринта, который сейчас изображен на экране:
- Пользователем задаются начальная и конечная точки
- Маршрут, являющийся решением, отображается линией толщиной 2 пикселя, проходящей через середины всех ячеек лабиринта, через которые пролегает решение

## Генерация пещер

Генерация пещер с использованием клеточного автомата:
- Пользователем выбирается файл, в котором описан пещера по описанному выше формату
- Для отображения пещер используется отдельная вкладка пользовательского интерфейса
- Максимальный размер пещеры - 50 х 50
- Загруженная пещера отрисовывается на экране в поле размером 500 x 500 пикселей
- Пользователем задаются пределы "рождения" и "смерти" клетки, а также шанс на начальную инициализацию клетки
- Пределы "рождения" и "смерти" могут иметь значения от 0 до 7
- Предусмотрен пошаговый режим отрисовки результатов работы алгоритма в двух вариантах:
  - По нажатию на кнопку следующего шага отрисовывается очередная итерация работы алгоритма
  - По нажатию на кнопку автоматической работы запускается отрисовка итераций работы алгоритма с частотой 1 шаг в N миллисекунд, где число миллисекунд N задаётся пользователем
- Размер клеток в пикселях вычисляется таким образом, чтобы пещера занимала всё отведенное под него поле