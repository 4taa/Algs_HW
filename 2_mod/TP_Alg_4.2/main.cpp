//
// Created by Pavel Pupchin on 2018-11-08.
//
//Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел,
//а также запрос на получение k-ой порядковой статистики.
//Команда добавления числа A задается положительным числом A,
//команда удаления числа A задается отрицательным числом “-A”.
//Запрос на получение k-ой порядковой статистики задается числом k.
//Требуемая скорость выполнения запроса - O(log n).

#include <iostream>
#include <stack>
#include <cassert>
#include <functional>
#include <math.h>

struct Node {
    int value;
    int height;
    int size;
    Node *leftChild;
    Node *rightChild;

    explicit Node(int &value) : value(value), size(1), height(1), leftChild(nullptr), rightChild(nullptr) {};
};

class Tree {
private:
    Node *root;

    int factor(Node *node) {
        if (node == nullptr)
            return 0;

        int heightLeftChild = node->leftChild == nullptr ? 0 : node->leftChild->height;
        int heightRightChild = node->rightChild == nullptr ? 0 : node->rightChild->height;

        return heightRightChild - heightLeftChild;
    };

    void fix(Node *node) {
        if (node == nullptr)
            return;

        fixHeight(node);
        fixSize(node);
    };

    void fixSize(Node *node) {
        int sizeLeftChild = node->leftChild == nullptr ? 0 : node->leftChild->size;
        int sizeRightChild = node->rightChild == nullptr ? 0 : node->rightChild->size;

        node->size = sizeLeftChild + sizeRightChild + 1;
    };

    void fixHeight(Node *node) {
        int heightLeftChild = node->leftChild == nullptr ? 0 : node->leftChild->height;
        int heightRightChild = node->rightChild == nullptr ? 0 : node->rightChild->height;

        if (heightLeftChild > heightRightChild)
            node->height = heightLeftChild + 1;
        else
            node->height = heightRightChild + 1;
    };

    void rotateRight(Node *&node) {
        if (node == nullptr || node->leftChild == nullptr)
            return;

        Node *temp = node->leftChild;
        node->leftChild = temp->rightChild;
        temp->rightChild = node;
        node = temp;
        fix(node->rightChild);
        fix(temp);
    };

    void rotateLeft(Node *&node) {
        if (node == nullptr || node->rightChild == nullptr)
            return;

        Node *temp = node->rightChild;
        node->rightChild = temp->leftChild;
        temp->leftChild = node;
        node = temp;
        fix(node->leftChild);
        fix(node);
    };

    void balance(Node *&node) {
        fix(node);
        if (factor(node) == 2) {
            if (node == nullptr || node->rightChild == nullptr)
                return;
            rotateRight(node->rightChild);
            rotateLeft(node);
        }
        if (factor(node) == -2) {
            if (node == nullptr || node->leftChild == nullptr)
                return;
            rotateLeft(node->leftChild);
            rotateRight(node);
        }
    };

    Node* removeMax(Node *&node) {
        if (node == nullptr)
            return nullptr;

        Node *temp = nullptr;
        if (node->rightChild == nullptr) {
            temp = node;
            node = node->leftChild;
        } else {
            temp = removeMax(node->rightChild);
            balance(node);
        }
        return temp;
    };

    void insert(Node *&node, int value) {
        if (node != nullptr && node->value == value)
            return;

        if (node == nullptr)
            node = new Node(value);
        else {
            if (value < node->value)
                insert(node->leftChild, value);
            else
                insert(node->rightChild, value);

            balance(node);
        }
    };

    void removeNode(Node *&node, int value) {
        if (node == nullptr)
            return;

        if (value < node->value)
            removeNode(node->leftChild, value);
        else if (value > node->value)
            removeNode(node->rightChild, value);
        else if (value == node->value){
            Node *tempDel = node;
            if (node->leftChild != nullptr) {
                Node *max = removeMax(node->leftChild);

                max->leftChild = node->leftChild;
                max->rightChild = node->rightChild;
                node = max;
            } else
                node = node->rightChild;

            delete tempDel;
        }
        balance(node);
    };

    int kStatat(Node *node, int kStat) {
        int leftChildSize = node->leftChild == nullptr ? 0 : node->leftChild->size;

        if (leftChildSize == kStat)
            return node->value;
        else if (leftChildSize > kStat)
            return kStatat(node->leftChild, kStat);
        else
            return kStatat(node->rightChild, kStat - leftChildSize - 1);
    }

    void postOrderProcess(std::function<void(Node *)> processElement) {
        if (root == nullptr)
            return;

        Node *localRoot = root;
        std::stack<Node *> temp;
        temp.push(root);

        while (temp.size() > 0) {
            Node *topElem = temp.top();
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
    Tree() : root(nullptr) {};

    Tree(const Tree &) = delete;
    Tree(Tree &&) = delete;
    Tree &operator=(const Tree &) = delete;
    Tree &operator=(Tree &&) = delete;

    ~Tree() {
        std::stack<Node *> temp;
        postOrderProcess([&temp](Node *element) {
            temp.push(element);
        });
        while (temp.size() > 0) {
            Node *toRemove = temp.top();
            temp.pop();
            delete toRemove;
        }
    };

    void insertElem(int value) {
        insert(root, value);
    }

    void removeElem(int value) {
        removeNode(root, value);
    };

    int statistics(int kStat) {
        int temp = 0;
        temp = kStatat(root, kStat);
        return temp;
    };
};

int main() {
    Tree tree;
    int numOfPairs = 0;
    int value = 0;
    int kStat = 0;
    int result = 0;

    std::cin >> numOfPairs;
    for (int i = 0; i < numOfPairs; i++) {
        std::cin >> value >> kStat;
        if (value >= 0)
            tree.insertElem(value);
        else
            tree.removeElem(abs(value));
        result = tree.statistics(kStat);
        std::cout << result << std::endl;
    }
    return 0;
}