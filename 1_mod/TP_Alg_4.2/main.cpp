/*Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы
 *двух чисел равно их сумме. Таким образом для нахождения суммы чисел 1,2,3 может потребоваться
 *разное время, в зависимости от порядка вычислений. ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2
 *= 10 ((2+3)+1) -> 2+3 + 5+1 = 11 Требуется написать программу, которая определяет минимальное
 *время, достаточное для вычисления суммы заданного набора чисел.
 *5                                                                                   45
  5 2 3 4 6

  Входной массив сортируем (?), складываем первые два элемента и суем сумму на законное место в массиве
  (проходим по массиву с целью сортировки отдельного элемента), затем снова повторяем первые два действия.*/

#include <iostream>
#include <cassert>

void swap (int &a, int &b) {
    int temp = 0;
    temp = a;
    a = b;
    b = temp;
}

class Heap {
private:
    int *Array;
    int size;
    int capacity;

    int parentIndex(int ind) {
        return (ind - 1) / 2;
    }

    void siftUp(int ind) {
        int par = 0;
        while (ind > 0) {
            par = parentIndex(ind);
            if (Array[ind] >= Array[par])
                return;
            swap(Array[ind], Array[par]);
            ind = par;
        }
    }

    void siftDown(int ind) {
        int first = 0;
        int second = 0;
        while (2 * ind + 1 < size) {
            first = 2 * ind + 1;
            second = 2 * ind + 2;
            int last = first;
            if (second < size && Array[first] > Array[second])
                last = second;
            if (Array[ind] <= Array[last])
                break;
            swap(Array[ind], Array[last]);
            ind = last;
        }
    }

public:

    Heap(int *array, int size): size(size), capacity(size) {
        Array = new int [capacity];
        std::copy(array, array + capacity, Array);
    }

    Heap(const Heap&) = default;
    Heap(Heap&&) = default;
    Heap& operator=(const Heap&) = default;
    Heap& operator=(Heap&&) = default;

    ~Heap() {
        delete [] Array;
    }

    Heap buildHeap(int *Array, int size) {
        Heap heap(Array, size);
        for (int i = heap.sizeOfHeap() / 2; i >= 0; --i)
            heap.siftDown(i);
        return heap;
    }

    int sizeOfHeap() {
        return size;
    }

    int popMin() {
        int min = Array[0];
        Array[0] = Array[--size];
        siftDown(0);
        return min;
    }

    void addElem(int elemToAdd) {
        size++;
        Array[size - 1] = elemToAdd;
        siftUp(size - 1);
    }
};

int counter(Heap heap) {
    int result = 0;
    int temp = 0;
    while (heap.sizeOfHeap() > 1) {
        temp = heap.popMin();
        temp = temp + heap.popMin();
        result = result + temp;
        heap.addElem(temp);
    }
    return result;
}

int main() {
    int count = 0;
    std::cin >> count;
    int *Array = new int [count];
    for (int i = 0; i < count; i++)
        std::cin >> Array[i];
    Heap heap(Array, count);
    std::cout << counter(heap.buildHeap(Array, count));
    delete [] Array;
    return 0;
}