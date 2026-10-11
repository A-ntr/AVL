// Name: An Tran
// UFID: 78249429
// Created by An on 9/18/2026.
//

#ifndef PROJECT1_AVLTREE_H
#define PROJECT1_AVLTREE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <queue>
#include <regex>
#include <unordered_set>
#include <iomanip>
#include <stack>

using namespace std;

struct Node {
    std::string name, ID;
    Node* left;
    Node* right;
    int height;

    Node();
    Node(std::string name, std::string ID);
};

class AVLTree {
    Node* root;

    int height(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLR(Node* node);
    Node* rotateRL(Node* node);
    void inorder(Node* node, vector<string>& result);
    void preorder(Node* node, vector<string>& result);
    void postorder(Node* node, vector<string>& result);
    Node* inorderSuccessor(Node* node);
    Node* inorderPredecessor(Node* node);
    void getInorderNodes(Node* node, vector<Node*>& nodes);
    void getNodes(Node* node, vector<Node*>& result, string target, string category = "ID");
    void getNames(Node* node, vector<Node*>& result, string target);
    bool containsID(Node* node, const string& id);

public:
    AVLTree();
    ~AVLTree();

    void clear(Node*& node);
    Node* insert(Node* node, string name, string id);
    Node* remove(Node*& node, string id);
    void removeInorder(int n);
    void printLevelCount();
    void display(string traversal);
    void execute(string &command);
    vector<string> getInorderNames();
    vector<string> getPreorderNames();
    vector<string> getPostorderNames();
    bool search(Node* node, string target, string category = "ID");
};

#endif //PROJECT1_AVLTREE_H