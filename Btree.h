#ifndef UNTITLED_BTREE_H
#define UNTITLED_BTREE_H
#include <initializer_list>

struct Node
{
    int data;
    Node* left;
    Node *right;
};

class Tree
{
private:
    Node *root;
    int m_count;
    void delete_tree(Node* leaf);
    void inorder_print(Node* leaf);
public:
    Tree();
    Tree(std::initializer_list<int> il);
    ~Tree();
    void insert(int data);
    bool remove(int data);
    Node* search(int data);
    Node* find_with_parent(int data, Node*& parent);
    void delete_tree();
    void inorder_print();
    bool contains(int data);
    int count() const;
    void clear();

};
#endif //UNTITLED_BTREE_H
