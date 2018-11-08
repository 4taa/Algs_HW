/*Задача 2.2
Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
а на интервале [m, n-1] строго убывают.
Найти m за O( log m ).
2 ≤ n ≤ 10000.*/

#include <iostream>
#include <cassert>

int Counter(int* Array, int lastElem)
{
    int leftElem = 0 , rightElem = lastElem;
    int middleElem = 0;
    while (rightElem - leftElem > 1)
    {
        middleElem = (leftElem + rightElem) / 2;
        if(Array[middleElem - 1] > Array[middleElem])
            rightElem = middleElem;
        else if(Array[middleElem-1] < Array[middleElem] && Array[middleElem] > Array[middleElem+1])
            return middleElem;
        else
            leftElem = middleElem;
    }
    return leftElem;
}

int main()
{
    int ArrSize;
    std::cin >> ArrSize;
    assert(ArrSize >= 2);
    assert(ArrSize <= 10000);
    int* Array = new int[ArrSize];
    for(int i = 0; i < ArrSize; ++i)
        std::cin >> Array[i];
    std::cout << Counter(Array, ArrSize);
    delete [] Array;
    return 0;
}
