#include <iostream>
#include <string>
#include <sstream>
#include "AVLTree.h"

using namespace std;

int main() {
    string line;
    if (!getline(cin, line)) return 0;

    while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t')) {
        line.pop_back();
    }

    stringstream ss(line);
    int numCommands = 0;
    AVLTree tree;

    if (ss >> numCommands && ss.eof()) {
        for (int i = 0; i < numCommands; ++i) {
            if (!getline(cin, line)) break;
            tree.execute(line);
        }
    } else {
        tree.execute(line);
        while (getline(cin, line)) {
            tree.execute(line);
            if (line == "exit") break;
        }
    }

    return 0;
}
