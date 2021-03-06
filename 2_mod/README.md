# Algorithms HW

## Задача 1.2

Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

Для разрешения коллизий используйте двойное хеширование.

Формат входных данных

Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.

Тип операции  – один из трех символов:

    +  означает добавление данной строки в множество; 

    -  означает удаление  строки из множества;  

    ?  означает проверку принадлежности данной строки множеству. 
    
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.

Формат выходных данных:

Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.


| Input | Output |
| :---: | :---: |
| + hello | OK |
| + bye | OK |
| ? bye | OK |
| + bye | FAIL |
| - bye | OK |
| ? bye | FAIL |
| ? hello | OK |


---
## Задача 2.3

Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.


| Input | Output |
| :---: | :---: |
| 3 | |
| 2 1 3 | 1 3 2 |
| | |
| 3 | |
| 1 2 3 | 3 2 1 |
| | |
| 3 | |
| 3 1 2 | 2 1 3 |


---
## Задача 3.2

Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

**Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.**

| Input | Output |
| :---: | :---: |
| 10 | 1 |
| 5 11 | |
| 18 8 | |
| 25 7 | |
| 50 12 | |
| 30 30 | |
| 15 15 | |
| 20 10 | |
| 22 5 | |
| 40 20 | |
| 45 9 | |
| | | 
| 10 | 1 |
| 38 19 | |
| 37 5 | |
| 47 15 | |
| 35 0 | |
| 12 3 | |
| 0 42 | |
| 31 37 | |
| 21 45 | |
| 30 26 | |
| 41 6 | |


---
## Задача 4.2

Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).


| Input | Output |
| --- | --- |
| 5 | |
| 40 0 | 40 |
| 10 1 | 40 |
| 4 1 | 10 |
| -10 0 | 4 |
| 50 2 | 50 |


---
## Задача 5.

Напишите две функции для создания архива из одного файла и извлечения файла из архива.

```C++
// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);
 где:
typedef char byte;
#define interface struct
```

```C++
interface IInputStream {
	// Возвращает false, если поток закончился
	virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
	virtual void Write(byte value) = 0;
};
```

В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный символ.
В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит размер сжатого файла в процентах от исходного.

Лучшие 3 решения с коэффициентом сжатия < 1 из каждой группы оцениваются в 10, 7 и 4 баллов соответственно.

Пример минимального решения:

```C++
#include "Huffman.h"

static void copyStream(IInputStream& input, IOutputStream& output)
{
	byte value;
	while (input.Read(value)) 
	{ 
		output.Write(value); 
	}
}

void Encode(IInputStream& original, IOutputStream& compressed) 
{
	copyStream(original, compressed); 
}

void Decode(IInputStream& compressed, IOutputStream& original) 
{ 
	copyStream(compressed, original); 
}
```

---