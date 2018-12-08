//
// Created by Pavel Pupchin on 2018-11-08.
//
//Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
//Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
//Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
//Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
//При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
//Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
//а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y).
//Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi.
//Равные ключи добавляйте в правое поддерево.
//Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
//Вывести их разницу. Разница может быть отрицательна.

#include <iostream>
#include <stack>
#include <queue>
#include <functional>

struct Node {
    int value;
    int priority;
    Node* leftChild;
    Node* rightChild;

    Node(int value, int priority = 0) : value(value), priority(priority), leftChild(nullptr), rightChild(nullptr) {};
};

template <class T>
int getWidth(T node) {
    int maxWidth = 0;
    int currentWidth = 0;

    std::queue<Node*> Nodes;
    Node* currentNode = nullptr;
    Nodes.push(node);

    while (Nodes.size() > 0) {
        if ((currentWidth = static_cast<int>(Nodes.size())) > maxWidth)
            maxWidth = currentWidth;

        for (int i = 0; i < currentWidth; i++) {
            currentNode = Nodes.front();
            if (currentNode->leftChild != nullptr)
                Nodes.push(currentNode->leftChild);
            if (currentNode->rightChild != nullptr)
                Nodes.push(currentNode->rightChild);
            Nodes.pop();
        }
    }
    return maxWidth;
};

class binaryTree {
private:
    Node* root;

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
    binaryTree() : root(nullptr) {};

    binaryTree(const binaryTree&) = delete;
    binaryTree(binaryTree&&) = delete;
    binaryTree& operator=(const binaryTree&) = delete;
    binaryTree& operator=(binaryTree&&) = delete;

    ~binaryTree() {
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

    void insert(int &value) {
        Node* newNode = new Node(value);
        Node* current = root;
        Node* parent;

        if (root == nullptr) {
            root = newNode;
        } else {
            while (true) {
                parent = current;
                if (value < current->value) {
                    current = current->leftChild;
                    if (current == nullptr) {
                        parent->leftChild = newNode;
                        return;
                    }
                } else {
                    current = current->rightChild;
                    if (current == nullptr) {
                        parent->rightChild = newNode;
                        return;
                    }
                }
            }
        }
    };

    int getWidthBinary() {
        int maxWidth = 0;
        maxWidth = getWidth(root);
        return maxWidth;
    };
};

class decTree{
private:
    Node* root;

    void split(Node* currentNode, int &value, Node* &leftChild, Node* &rightChild) {
        if (currentNode == nullptr) {
            leftChild = nullptr;
            rightChild = nullptr;
        } else if (currentNode->value <= value) {
            split(currentNode->rightChild, value, currentNode->rightChild, rightChild);
            leftChild = currentNode;
        } else {
            split(currentNode->leftChild, value, leftChild, currentNode->leftChild);
            rightChild = currentNode;
        }
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
    explicit decTree() : root(nullptr) {}

    decTree(const decTree&) = delete;
    decTree(decTree&&) = delete;
    decTree& operator=(const decTree&) = delete;
    decTree& operator=(decTree&&) = delete;

    ~decTree() {
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

    void insert(int &value, int priority) {
        Node* newNode = new Node(value, priority);
        Node* currentNode = root;
        Node* prevNode = root;

        if (currentNode == nullptr) {
            root = newNode;
            return;
        }

        while (currentNode != nullptr && priority <= currentNode->priority) {
            prevNode = currentNode;
            if (value <= currentNode->value)
                currentNode = currentNode->leftChild;
            else
                currentNode = currentNode->rightChild;
        }

        split(currentNode, value, newNode->leftChild, newNode->rightChild);

        if (currentNode == root)
            root = newNode;
        else if (value <= prevNode->value)
            prevNode->leftChild = newNode;
        else
            prevNode->rightChild = newNode;
    };

    int getWidthDec() {
        int maxWidth = 0;
        maxWidth = getWidth(root);
        return maxWidth;
    };
};

int main(){
    binaryTree binary;
    decTree dec;
    int value = 0;
    int priority = 0;
    int numOfPairs = 0;
    int result = 0;

    std::cin >> numOfPairs;
    for (int i = 0; i < numOfPairs; i++) {
        std::cin >> value >> priority;
        binary.insert(value);
        dec.insert(value, priority);
    }

    result = dec.getWidthDec() - binary.getWidthBinary();
    std::cout << result;

    return 0;
}