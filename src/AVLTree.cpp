// Name: An Tran
// UFID: 78249429
// Created by An on 9/18/2026.
//

#include "AVLTree.h"

Node::Node() : name(""), ID(""), left(nullptr), right(nullptr), height(0) {}

Node::Node(std::string name, std::string ID) : name(name), ID(ID), left(nullptr), right(nullptr), height(1) {}

int AVLTree::height(Node* node) {
    if (!node)
        return 0;
    return node->height;
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    node->height = 1 + max(height(node->left), height(node->right));
    rightChild->height = 1 + max(height(rightChild->left), height(rightChild->right));
    return rightChild;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    node->height = 1 + max(height(node->left), height(node->right));
    leftChild->height = 1 + max(height(leftChild->left), height(leftChild->right));
    return leftChild;
}

Node* AVLTree::rotateLR(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* AVLTree::rotateRL(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

void AVLTree::inorder(Node* node, vector<string>& result) {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->name);
    inorder(node->right, result);
}

void AVLTree::preorder(Node* node, vector<string>& result) {
    if (!node) return;
    result.push_back(node->name);
    preorder(node->left, result);
    preorder(node->right, result);
}

void AVLTree::postorder(Node* node, vector<string>& result) {
    if (!node) return;
    postorder(node->left, result);
    postorder(node->right, result);
    result.push_back(node->name);
}

AVLTree::AVLTree() : root(nullptr) {}

void AVLTree::clear(Node*& node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
}

AVLTree::~AVLTree() {
    clear(root);
}

bool AVLTree::containsID(Node* node, const string& id) {
    if (!node) return false;
    if (id == node->ID) return true;
    if (id < node->ID) return containsID(node->left, id);
    return containsID(node->right, id);
}

Node* AVLTree::insert(Node* node, string name, string id) {
    if (!node) return new Node(name, id);
    if (id < node->ID)
        node->left = insert(node->left, name, id);
    else if (id > node->ID)
        node->right = insert(node->right, name, id);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int bf = height(node->left) - height(node->right);

    // Left Left
    if (bf > 1 && id < node->left->ID)
        return rotateRight(node);

    // Right Right
    if (bf < -1 && id > node->right->ID)
        return rotateLeft(node);

    // Left Right
    if (bf > 1 && id > node->left->ID)
        return rotateLR(node);

    // Right Left
    if (bf < -1 && id < node->right->ID)
        return rotateRL(node);

    return node;
}

Node* AVLTree::inorderSuccessor(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* AVLTree::inorderPredecessor(Node* node) {
    while (node && node->right != nullptr) {
        node = node->right;
    }
    return node;
}

Node* AVLTree::remove(Node*& node, string id) {
    if (!node) return nullptr;
    if (id < node->ID) {
        node->left = remove(node->left, id);
    }
    else if (id > node->ID) {
        node->right = remove(node->right, id);
    }
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                delete node;
                node = nullptr;
                return nullptr;
            }
            else {
                Node* toDelete = node;
                node = temp;
                delete toDelete;
            }
        }
        else {
            Node* successor = inorderSuccessor(node->right);
            node->ID = successor->ID;
            node->name = successor->name;
            node->right = remove(node->right, successor->ID);
        }
    }

    if (!node) return nullptr;

    node->height = 1 + max(height(node->left), height(node->right));
    int bf = height(node->left) - height(node->right);

    if (bf > 1) {
        int leftBf = height(node->left->left) - height(node->left->right);
        if (leftBf >= 0)
            return rotateRight(node);
        else
            return rotateLR(node);
    }
    if (bf < -1) {
        int rightBf = height(node->right->left) - height(node->right->right);
        if (rightBf <= 0)
            return rotateLeft(node);
        else
            return rotateRL(node);
    }

    return node;
}

void AVLTree::getInorderNodes(Node* node, vector<Node*>& nodes) {
    if (!node) return;
    getInorderNodes(node->left, nodes);
    nodes.push_back(node);
    getInorderNodes(node->right, nodes);
}

void AVLTree::removeInorder(int n) {
    vector<Node*> nodes;
    getInorderNodes(root, nodes);

    if (n < 0 || static_cast<size_t>(n) >= nodes.size()) {
        cout << "unsuccessful\n";
        return;
    }

    string targetID = nodes[n]->ID;
    root = remove(root, targetID);
    cout << "successful\n";
}

void AVLTree::printLevelCount() {
    cout << height(root) << "\n";
}

void AVLTree::display(string traversal) {
    if (!root) {
        return;
    }
    if (traversal == "inorder") {
        getInorderNames();
    }
    else if (traversal == "preorder") {
        getPreorderNames();
    }
    else if (traversal == "postorder") {
        getPostorderNames();
    }
    else if (traversal == "display") {
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                Node* curr = q.front();
                cout << curr->name << ": " << curr->ID << " h=" << curr->height << "\n";
                q.pop();
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
    }
    cout << "\n";
}

void AVLTree::execute(std::string& command) {
    string cmd = command;
    while (!cmd.empty() && (cmd.back() == '\r' || cmd.back() == ' ' || cmd.back() == '\t' || cmd.back() == '\n')) {
        cmd.pop_back();
    }
    size_t start = 0;
    while (start < cmd.size() && (cmd[start] == ' ' || cmd[start] == '\t')) {
        start++;
    }
    if (start > 0) {
        cmd = cmd.substr(start);
    }
    if (cmd.empty()) {
        cout << "unsuccessful\n";
        return;
    }

    stringstream ss(cmd);
    string word;
    vector<string> commandLine;
    while (ss >> quoted(word)) {
        commandLine.push_back(word);
    }

    if (ss.fail() && !ss.eof()) {
        cout << "unsuccessful\n";
        return;
    }

    if (commandLine.empty()) {
        cout << "unsuccessful\n";
        return;
    }

    if (commandLine[0] == "insert") {
        if (commandLine.size() == 3 && cmd.find('"') != string::npos) {
            regex ufIDRegex("^[0-9]{8}$");
            regex nameRegex("^[A-Za-z\\s]+$");
            bool isUFID = regex_match(commandLine[2], ufIDRegex);
            bool isName = regex_match(commandLine[1], nameRegex);
            if (isUFID && isName) {
                if (!containsID(root, commandLine[2])) {
                    root = insert(root, commandLine[1], commandLine[2]);
                    cout << "successful\n";
                }
                else {
                    cout << "unsuccessful\n";
                }
            }
            else {
                cout << "unsuccessful\n";
            }
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "printInorder" || commandLine[0] == "printinorder") {
        if (commandLine.size() == 1) {
            display("inorder");
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "printPreorder" || commandLine[0] == "printpreorder") {
        if (commandLine.size() == 1) {
            display("preorder");
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "printPostorder" || commandLine[0] == "printpostorder") {
        if (commandLine.size() == 1) {
            display("postorder");
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "printLevelCount" || commandLine[0] == "printlevelcount") {
        if (commandLine.size() == 1) {
            printLevelCount();
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "display") {
        display("display");
    }
    else if (commandLine[0] == "remove") {
        if (commandLine.size() == 2) {
            regex ufIDRegex("^[0-9]{8}$");
            if (regex_match(commandLine[1], ufIDRegex)) {
                if (containsID(root, commandLine[1])) {
                    root = remove(root, commandLine[1]);
                    cout << "successful\n";
                }
                else {
                    cout << "unsuccessful\n";
                }
            }
            else {
                cout << "unsuccessful\n";
            }
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "removeInorder" || commandLine[0] == "removeinorder") {
        if (commandLine.size() == 2) {
            regex numRegex("^[0-9]+$");
            if (regex_match(commandLine[1], numRegex)) {
                removeInorder(stoi(commandLine[1]));
            }
            else {
                cout << "unsuccessful\n";
            }
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "search") {
        if (commandLine.size() == 2) {
            regex ufIDRegex("^[0-9]{8}$");
            regex nameRegex("^[A-Za-z\\s]+$");
            bool hasQuotes = (cmd.find('"') != string::npos);
            if (!hasQuotes && regex_match(commandLine[1], ufIDRegex)) {
                if (!search(root, commandLine[1], "ID")) {
                    cout << "unsuccessful\n";
                }
            }
            else if (hasQuotes && regex_match(commandLine[1], nameRegex)) {
                if (!search(root, commandLine[1], "name")) {
                    cout << "unsuccessful\n";
                }
            }
            else {
                cout << "unsuccessful\n";
            }
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    else if (commandLine[0] == "exit") {command = "exit";}
    else {
        cout << "unsuccessful\n";
    }
}

vector<string> AVLTree::getInorderNames() {
    vector<string> names;
    inorder(root, names);
    for (size_t i = 0; i < names.size(); i++) {
        if (i > 0) cout << ", ";
        cout << names[i];
    }
    return names;
}

vector<string> AVLTree::getPreorderNames() {
    vector<string> names;
    preorder(root, names);
    for (size_t i = 0; i < names.size(); i++) {
        if (i > 0) cout << ", ";
        cout << names[i];
    }
    return names;
}

vector<string> AVLTree::getPostorderNames() {
    vector<string> names;
    postorder(root, names);
    for (size_t i = 0; i < names.size(); i++) {
        if (i > 0) cout << ", ";
        cout << names[i];
    }
    return names;
}

bool AVLTree::search(Node* node, string target, string category) {
    vector<Node*> results;
    if (category == "ID")
        getNodes(node, results, target, category);
    else if (category == "name")
        getNames(node, results, target);

    if (results.empty())
        return false;

    for (size_t i = 0; i < results.size(); i++) {
        if (category == "ID") {
            cout << results[i]->name << "\n";
        }
        else if (category == "name") {
            cout << results[i]->ID << "\n";
        }
    }
    return true;
}

void AVLTree::getNodes(Node* node, vector<Node*>& result, string target, string category) {
    if (!node) return;
    if (category == "ID") {
        if (target == node->ID) {
            result.push_back(node);
            return;
        }
        if (target < node->ID)
            getNodes(node->left, result, target, category);
        else
            getNodes(node->right, result, target, category);
        return;
    }
    if (node->name == target)
        result.push_back(node);
    getNodes(node->left, result, target, category);
    getNodes(node->right, result, target, category);
}

void AVLTree::getNames(Node* node, vector<Node*>& result, string target) {
    if (!node) return;
    if (node->name == target)
        result.push_back(node);
    getNames(node->left, result, target);
    getNames(node->right, result, target);
}