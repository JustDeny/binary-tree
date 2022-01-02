#include "Btree.h"
#include <iostream>
Tree::Tree():
    root{nullptr}, m_count{0}
{}

Tree::Tree(std::initializer_list<int> il):
    root{nullptr}, m_count{0}
{
    for (auto& item: il) {
        insert(item);
    }
}

void Tree::insert(int data) {
    if(!root){
        root = new Node{data, nullptr, nullptr};
    }
    else{
        Node* current = root;
        while(true)
        {
            if(data < current->data)
            {
                //if free place has been reached
                if(current->left == nullptr)
                {
                    current->left = new Node{data, nullptr, nullptr};
                    break;
                }
                    //else go on searching
                    current = current->left;
            }

            else if(data > current->data)
            {
                if(current->right == nullptr)
                {
                    current->right = new Node{data, nullptr, nullptr};
                    break;
                }
                current = current->right;
            }
        }
    }
    ++m_count;
}

Node *Tree::search(int data) {
    Node* current = root;
    bool isFound = false;
    while(current)
    {
        if(current->data == data)
        {
            isFound = true;
            break;
        }
        if(data < current->data) {
            current = current->left;
        }
        else if(data > current->data) {
            current = current->right;
        }
    }
    if(isFound)
        return current;
    return nullptr;
}

int Tree::count() const {
    return m_count;
}

bool Tree::contains(int data) {
    return search(data)!= nullptr;
}

bool Tree::remove(int data) {
    Node* current, *parent;
    current = find_with_parent(data, parent);
    if(current == nullptr)
    {
        return false;
    }
    // 1st case when deleted node doesn't have a right child
    if(current->right == nullptr)
    {
        if(parent == nullptr)
        {
            root = current->left;
        }
        else
        {
            // current is a right branch of parent
            if(parent->data < current->data)
            {
                parent->right = current->left;
            }
            else if(parent->data > current->data)
            {
                parent->left = current->left;
            }
        }
    }
    // 2nd case when right child doesn't have left child but has a right one
    else if(current->right->left == nullptr)
    {
        current->right->left = current->left;
        if(parent == nullptr)
        {
            root = current->right;
        }
        else
        {
            if(parent->data < current->data)
            {
                parent->right = current->right;
            }
            else if(parent->data > current->data)
            {
                parent->left = current->right;
            }
        }
    }
    // 3rd case when deleted node has a right child which has a left one
    else
    {
        Node* most_left = current->right->left;
        Node* most_left_parent = current->right;
        while(most_left != nullptr)
        {
            most_left_parent = most_left; most_left = most_left->left;
        }
        most_left_parent->left = most_left->right;
        most_left->left = current->left;
        most_left->right = current->right;
        if(parent == nullptr)
            root = most_left;

        else if(parent->data < current->data)
        {
            parent->right = most_left;
        }
        else if(parent->data > current->data)
        {
            parent->left = most_left;
        }
    }
    delete current;
    --m_count;
    return true;
}

Node *Tree::find_with_parent(int data, Node*& parent) {
    Node* current = root;
    parent = nullptr;
    while(current != nullptr)
    {
        if(current->data == data)
            break;
        parent = current;
        if(data < current->data)
            current = current->left;
        else if(data > current->data)
            current = current->right;
    }
    return current;
}

void Tree::clear() {
    delete_tree();
    root = nullptr;
    --m_count;
}

void Tree::delete_tree(Node *leaf) {
    if(leaf != nullptr)
    {
        delete_tree(leaf->right);
        delete_tree(leaf->left);
        delete leaf;
    }
}

void Tree::delete_tree() {
    delete_tree(root);
}

Tree::~Tree() {
    delete_tree();
}

void Tree::inorder_print() {
    inorder_print(root);
}

void Tree::inorder_print(Node *leaf) {
    if(leaf != nullptr)
    {
        inorder_print(leaf->left);
        std::cout << leaf->data << " ";
        inorder_print(leaf->right);
    }
}

