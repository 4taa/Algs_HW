/* Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000.
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.*/

#include <iostream>
#include <cassert>

struct LSD{
    unsigned char byte[8];
};

void countSort(LSD *&Array, unsigned int size){
    for (int i = 0; i < 8; i++){
        int C[256];
        for (int k = 0; k < 256; k++)
            C[k] = 0;
        for (int j = 0; j < size; j++)
            C[Array[j].byte[i]]++;
        for (int t = 1; t < 256; t++)
            C[t] += C[t - 1];
        LSD *tempArray = new LSD[size];
        for (int p = size - 1; p >= 0; p--)
            tempArray[--C[Array[p].byte[i]]] = Array[p];
        delete [] Array;
        Array = tempArray;
    }
};

void sortLSD(long long *&Array, unsigned int size){
    LSD *tempArray = (LSD *)Array;
    countSort(tempArray, size);
    Array = (long long *)tempArray;
};

int main() {
    unsigned int numOfValues = 0;
    std::cin >> numOfValues;
    assert(numOfValues < 1000000);
    long long *Array = new long long[numOfValues];
    for (int i = 0; i < numOfValues; i++)
        std::cin >> Array[i];
    sortLSD(Array, numOfValues);
    for (int i = 0; i < numOfValues; i++)
        std::cout << Array[i] << " ";
    delete [] Array;
    return 0;
}