/*Задача 3.2
 * Реализовать дек с динамическим зацикленным буфером.
Обрабатывать команды push * и pop *.
Формат ввода

В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Если дана команда pop *, то число b - ожидаемое значение. Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

3
1 44
3 50
2 44
                                                            YES*/

#include <iostream>
#include <cassert>

class Deck{

public:
    Deck (int capacity):
    capacity(capacity), head (0), tail (0){
        Array = new int [capacity];
    }

    void pushTail(int valToAdd){
        Array[tail] = valToAdd;
        tail = (tail + 1) % capacity;
        if (tail == head)
            incCapacity();
    }

    void pushHead(int valToAdd){
        if (head == 0)
            head = capacity - 1;
        else
            head--;
        Array[head] = valToAdd;
        if (tail == head)
            incCapacity();
    }

    int popHead(){
        if (head == tail)
            return -1;
        else {
            int result = Array[head];
            head = (head + 1) % capacity;
            return result;
        }
    }

    int popTail(){
        if (head == tail)
            return -1;
        else {
            if (tail == 0)
                tail = capacity - 1;
            else
                tail--;
            int result = Array[tail];
            return result;
        }
    }

    ~Deck(){
        delete[] Array;
    }

private:

    int *Array;
    int head;
    int tail;
    int capacity;

    void incCapacity(){
        int *newArray = new int [capacity * 2];
        for (int i = 0; i < capacity; i++)
            newArray[i] = Array[(head + i) % capacity];
        delete[] Array;
        Array = newArray;
        head = 0;
        tail = capacity;
        capacity = capacity * 2;
    }
};

int main(){
    Deck deck(2);
    int n = 0, func_num = 0, func_value = 0;
    std::cin >> n;
    assert(n <= 1000000);
    for (int i = 0; i < n; i ++){
        std::cin >> func_num >> func_value;
        if (func_num == 1){
            deck.pushHead(func_value);
        }
        if (func_num == 3){
            deck.pushTail(func_value);
        }
        if (func_num == 2){
            if(deck.popHead() != func_value){
                std::cout << "NO";
                return 0;
            }
        }
        if (func_num == 4){
            if(deck.popTail() != func_value){
                std::cout << "NO";
                return 0;
            }
        }
    }
    std::cout << "YES";
    return 0;
}