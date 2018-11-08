/*Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
 *Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в
 *отсортированном массиве.
 *Напишите нерекурсивный алгоритм.
 *Требования к дополнительной памяти: O(n).
 *Требуемое среднее время работы: O(n).
 *Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 *Описание для случая прохода от начала массива к концу:
 *Выбирается опорный элемент.
 *Опорный элемент меняется с последним элементом массива.
 *Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие
 *опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
 *Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 *Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 *Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j. Если он не больше опорного,
 *то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 *В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 */

#include <iostream>
#include <cstdlib>
#include <algorithm>

int partition(int *Array, int leftElem, int rightElem){
    int pivot = rand() % (rightElem - leftElem) + leftElem;
    std::swap(Array[pivot], Array[rightElem - 1]);

    int i = rightElem - 2;
    int j = rightElem - 1;

    while (j >= 0) {
        if (Array[rightElem - 1] < Array[j]){
            std::swap(Array[i], Array[j]);
            i--;
        }
        else
            i = i;
        j--;
    }
    i++;
    std::swap(Array[i], Array[rightElem - 1]);
    return i;
}

int kStat(int *Array, int leftElem, int rightElem, int kStatistic) {
    int pivot = partition(Array, leftElem, rightElem);
    while (pivot != kStatistic) {
        if (pivot < kStatistic) {
            leftElem = pivot;
            pivot = partition(Array, leftElem, rightElem);
        }
        else if (pivot > kStatistic) {
            rightElem = pivot;
            pivot = partition(Array, leftElem, rightElem);
        }
    }
    return Array[pivot];
}

int main() {
    int sizeOfArray = 0;
    int kStatistic = 0;
    std::cin >> sizeOfArray >> kStatistic;
    int *Array = new int[sizeOfArray];
    for (int i = 0; i < sizeOfArray; i++)
        std::cin >> Array[i];
    int result = kStat(Array, 0, sizeOfArray, kStatistic);
    std::cout << result;
    delete [] Array;
    return 0;
}