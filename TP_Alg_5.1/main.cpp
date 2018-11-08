/* В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
 * Каждому покупателю необходимо показать минимум 2 рекламы. Рекламу можно транслировать только в целочисленные моменты
 * времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина. В каждый момент времени
 * может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в
 * момент ухода или прихода, то считается, что посетитель успел её посмотреть.
 * Требуется определить минимальное число показов рекламы.*/

#include <iostream>
#include <cassert>

struct Visitor{
    int enter;
    int exit;

    Visitor() : enter(0), exit(0){};

    Visitor(int enterTime, int exitTime) : enter(enterTime), exit(exitTime){};
};

bool operator < (Visitor visitor1, Visitor visitor2){
    if (visitor1.exit == visitor2.exit)
        return visitor1.enter > visitor2.enter;
    else
        return visitor1.enter < visitor2.enter;
}

template <class T>
void merge(T *firstArray, int sizeOfFirstArray, T *secondArray, int sizeOfSecondArray, T *buffer){
    int temp1 = 0;
    int temp2 = 0;
    int bufTemp = 0;

    while (temp1 < sizeOfFirstArray && temp2 < sizeOfSecondArray){
        if (firstArray[temp1] < secondArray[temp2]){
            buffer[bufTemp] = firstArray[temp1];
            temp1++;
        } else{
            buffer[bufTemp] = secondArray[temp2];
            temp2++;
        }
        bufTemp++;
    }

    while (temp1 < sizeOfFirstArray){
        buffer[bufTemp] = firstArray[temp1];
        bufTemp++;
        temp1++;
    }
    while (temp2 < sizeOfSecondArray){
        buffer[bufTemp] = secondArray[temp2];
        bufTemp++;
        temp2++;
    }
}
template <class T>
void mergeSort(T *Array, int sizeOfArray){
    if (sizeOfArray <= 1)
        return;
    int temp1 = sizeOfArray / 2;
    int temp2 = sizeOfArray - temp1;

    mergeSort(Array, temp1);
    mergeSort(Array + temp1, temp2);

    T *buffer = new T[sizeOfArray];
    merge(Array, temp1, Array + temp1, temp2, buffer);
    for (int i = 0; i < sizeOfArray; i++)
        Array[i] = buffer[i];
    delete [] buffer;
}

int counter(Visitor *visitorArray, int sizeOfArray){
    mergeSort(visitorArray, sizeOfArray);

    int first = visitorArray[0].exit - 1;
    int last = visitorArray[0].exit;
    int count = 2;
    for (int i = 0; i < sizeOfArray; i++){
        if (visitorArray[i].enter > first){
            if (visitorArray[i].enter > last){
                count = count + 2;
                first = visitorArray[i].exit - 1;
                last = visitorArray[0].exit;
            } else{
                count++;
                first = last;
                last = visitorArray[0].exit;
                if (first == last){
                    first--;
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    int numOfVisitors = 0;
    int enter = 0;
    int exit = 0;
    std::cin >> numOfVisitors;
    Visitor *visitors = new Visitor[numOfVisitors];
    for (int i = 0; i < numOfVisitors; i++){
        std::cin >> enter >> exit;
        assert(0 < enter < exit);
        visitors[i] = Visitor(enter, exit);
    }
    int result = 0;
    result = counter(visitors, numOfVisitors);
    std::cout << result;
    delete [] visitors;
    return 0;
}
