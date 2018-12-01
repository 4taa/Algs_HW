//
// Created by Pavel Pupchin on 2018-11-08.
//
//Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N.
//Требуется построить бинарное дерево, заданное наивным порядком вставки.
//Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
//то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
//Выведите элементы в порядке post-order (снизу вверх).
//Рекурсия запрещена.

#include <iostream>
#include <stack>

struct Node {
    int value;
    Node* leftChild;
    Node* rightChild;

    Node(int value) : value(value) {};

};

class Tree {
private:
    Node* root;
    int size = 0;

    void static displayElement(Node* node) {
        std::cout << node->value << ' ';
    };

    void postOrderProcess(std::function<void(Node*)> processElement) {
        if (root == nullptr)
            return;

        Node* localRoot = root;
        std::stack<Node*> temp;
        temp.push(root);

        while (temp.size() > 0) {
            Node* topElem = temp.top();
            if (topElem->leftChild == nullptr && topElem->rightChild == nullptr) {
                localRoot = topElem;
                processElement(topElem);
                temp.pop();
                continue;
            } else {
                if (topElem->leftChild == localRoot || topElem->rightChild == localRoot) {
                    localRoot = topElem;
                    processElement(topElem);
                    temp.pop();
                    continue;
                }
                if (topElem->rightChild != nullptr)
                    temp.push(topElem->rightChild);
                if (topElem->leftChild != nullptr)
                    temp.push(topElem->leftChild);
            }
        }
    };

public:
    Tree () : root(nullptr) {};
    
    Tree(const Tree&) = delete;
    Tree(Tree&&) = delete;
    Tree& operator=(const Tree&) = delete;
    Tree& operator=(Tree&&) = delete;
    
    ~Tree() {
        std::stack<Node*> temp;
        postOrderProcess([&temp](Node* element) {
            temp.push(element);
        });
        while (temp.size() > 0) {
            Node* toRemove = temp.top();
            temp.pop();
            delete toRemove;
        }
    };

    void postOrderDisplay() {
        postOrderProcess(displayElement);
    };

    void insert(int &value) {
        Node* newNode = new Node(value);
        Node* current = root;
        Node* parent;

        if (root == nullptr) {
            root = newNode;
            size++;
        } else {
            while (true) {
                parent = current;
                if (value < current->value) {
                    current = current->leftChild;
                    if (current == nullptr) {
                        parent->leftChild = newNode;
                        size++;
                        return;
                    }
                } else {
                    current = current->rightChild;
                    if (current == nullptr) {
                        parent->rightChild = newNode;
                        size++;
                        return;
                    }
                }
            }
        }
    };
};

int main(){
    int size;
    Tree* tree = new Tree();
    int data = 0;

    std::cin >> size;
    for (int i = 0; i < size; i++) {
        std::cin >> data;
        tree->insert(data);
    }
    tree->postOrderDisplay();
    return 0;
}