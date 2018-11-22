/*Задача 1.4
В круг выстроено N человек, пронумерованных числами от 1 до N. Будем исключать каждого k-ого до тех пор,
пока не уцелеет только один человек. Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.
Необходимо определить номер уцелевшего.
N, k ≤ 10000.*/

#include <iostream>
#include <cassert>

//TODO: правило пяти

class Node {
public:
    Node *head = nullptr;
    int value;
    Node *next;

    Node(): value (0), next(nullptr) {}

    Node(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(const Node&) = delete;
    Node& operator=(Node&&) = delete;

    Node * addElem(int valToAdd, Node *current) {
        Node *newNode = new Node();
        newNode->value = valToAdd;
        if (head == nullptr){
            head = newNode;
            head->next = head;
            return head;
        }
        newNode->next = current->next;
        current->next = newNode;
        return newNode;
    }

    void deleteElem(Node *valToDel) {
        Node *node = valToDel->next;
        if (valToDel == node)
            head = nullptr;
        else {
            if (head == node && head != valToDel) {
                head = head->next;
            }
            valToDel->next = node->next;
        }
        delete node;
        return;
    }

    Node * getHead () {
        return head;
    }

    Node * getNext(Node *node) {
        if (node == nullptr)
            return head;
        return node->next;
    }

    ~Node(){
        while(head != nullptr)
            deleteElem(head);
    }
};

int Counter(int TotalVals, int delInd) {
    Node node;
    assert (TotalVals > 0);
    assert (delInd > 0);
    Node *curr = node.getHead();
    for (int i = 1; i <= TotalVals; i++) {
        curr = node.addElem(i, curr);
    }
    curr = nullptr;
    do{
        for (int i = 0; i < delInd; i++) {
            curr = node.getNext(curr);
            if (i == delInd - 1)
                node.deleteElem(curr);
        }
    }
    while (curr != node.getNext(curr));
    return curr->value;
}

int main(){
    int N = 0;
    int k = 0;
    std::cin >> N >> k;
    assert (N<=10000);
    assert (k<=10000);
    Node node;
    int result = 0;
    result = Counter(N, k);
    std::cout << result;
}