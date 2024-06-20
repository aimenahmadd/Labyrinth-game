#pragma once
#include<iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"Audio.h"
#include"Animation.h"
#include"Player.h"
#include"Item.h"

using namespace sf;
using namespace std;

template <typename T>
class Node
{
public:
    T* item;
    Node<T>* left;
    Node<T>* right;
    int height;

    Node()
    {
        left = nullptr;
        right = nullptr;
        height = 1;
    }
    Node(T* item) : item(item), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class inventory {

public:
    Node<T>* root;

private:

    int height(Node<T>* node)
    {
        if (node == nullptr) return 0;
        return node->height;
    }

    int balanceFactor(Node<T>* node)
    {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node<T>* node)
    {
        if (node == nullptr) return;
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    Node<T>* rotateRight(Node<T>* y)
    {
        Node<T>* x = y->left;
        Node<T>* T = x->right;

        x->right = y;
        y->left = T;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node<T>* rotateLeft(Node<T>* x)
    {
        Node<T>* y = x->right;
        Node<T>* T = y->left;

        y->left = x;
        x->right = T;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node<T>* minValueNode(Node<T>* node)
    {
        Node<T>* current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    Node<T>* insert(Node<T>* node, T* item)
    {

        if (node == nullptr)
        {
            item->numofitems++;

            return new Node<T>(item);
        }

        else if (item->key < node->item->key)
        {
            node->left = insert(node->left, item);
        }

        else if (item->key > node->item->key)
        {
            node->right = insert(node->right, item);
        }

        else if (item->key == node->item->key)
        {
            node->item->value += item->value;
            node->item->numofitems++;
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && item->key < node->left->item->key) {
            return rotateRight(node);
        }

        if (balance < -1 && item->key > node->right->item->key) {
            return rotateLeft(node);
        }

        if (balance > 1 && item->key > node->left->item->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && item->key < node->right->item->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node<T>* remove1(Node<T>* node, T& key)
    {
        if (node == nullptr) return nullptr;

        if (key < node->item->key)
        {
            node->left = remove(node->left, key);
        }

        else if (key > node->item->key)
        {
            node->right = remove(node->right, key);
        }

        else
        {
            if (node->item->value <= 0)
            {
                Node<T>* temp = node->left ? node->left : node->right;
                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp->item;
                delete temp;
            }
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
        {
            return rotateRight(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
        {
            return rotateLeft(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node<T>* search1(Node<T>* node, const int key) const
    {
        if (node == nullptr || node->item->key == key)
        {
            return node;
        }

        if (key < node->item->key)
        {
            return search1(node->left, key);
        }

        return search1(node->right, key);
    }

    void display(Node<T>* node)
    {
        if (node == nullptr) return;

        display(node->left);

        std::cout << node->item->name << " Key: " << node->item->key << ", Value: " << node->item->value << std::endl;

        display(node->right);
    }

public:

    inventory() : root(nullptr) {}

    ~inventory()
    {
        destroyTree(root);
    }

    void insert(T* item)
    {
        root = insert(root, item);
    }

    void remove(const int key)
    {
        root = remove(root, key);
    }

    bool search(const int key) const
    {
        return search1(root, key) != nullptr;
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    int size() const
    {
        return getSize(root);
    }

    void display1()
    {
        display(root);
    }

    void removenum(const int key) 
    {
        Node<T>* node = search1(root, key);
        if (node != nullptr) 
        {
            node->item->numofitems--;
           
        }
    }


    int search(const int key)
    {
        Node<T>* node = search1(root, key);
        if (node != nullptr) {
            return node->item->numofitems;
        }
        return 0;
    }

    void destroyTree(Node<T>* node)
    {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
};
