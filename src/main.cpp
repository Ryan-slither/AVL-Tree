#include "AVL.h"

using namespace std;

bool checkCharacters(string name) {
    for (auto c : name) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ') {
            continue;
        } else {
            return true;
        }
    }
    return false;
}

bool checkNumbers(string possibleNumbers) {
    for (auto c : possibleNumbers) {
        if (!isdigit(c)) {
            return true;
        }
    }
    return false;
}

void commandLine() {
    int commands;
    string line;
    AVL tree(nullptr);
    // Check number of commands
    getline(cin, line);
    commands = stoi(line);
    // Loop to process inputs
    for (int i = 0; i < commands; ++i) {
        bool success = true;
        line.clear();
        string command;
        string studentName;
        string searchInput;
        string studentId;
        string nodeNumber;
        getline(cin, line);
        stringstream ss(line);
        ss >> command;
        if (command == "insert") {
            getline(ss, studentName, '"');
            getline(ss, studentName, '"');
            getline(ss ,studentId, ' ');
            getline(ss ,studentId, ' ');
            if (studentId.size() != 8 || checkCharacters(studentName) || checkNumbers(studentId)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (tree.root == nullptr) {
                tree.root = tree.insert(tree.root, stoi(studentId), studentName, success);
            } else {
                tree.insert(tree.root, stoi(studentId), studentName, success);
            }
            if (success) {
                cout << "successful" << endl;
            }
        } else if (command == "remove") {
            getline(ss ,studentId, ' ');
            getline(ss ,studentId, ' ');
            if (studentId.size() != 8 && checkNumbers(studentId)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            tree.removeId(tree.root, stoi(studentId));
        } else if (command == "search") {
            getline(ss ,searchInput, ' ');
            getline(ss ,searchInput, ' ');
            if (!checkNumbers(searchInput)) {
                if (searchInput.size() != 8) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                Node *result = tree.searchId(tree.root, stoi(searchInput));
                if (result != nullptr) {
                    cout << result->name << endl;
                }
            } else {
                searchInput = searchInput.substr(1, searchInput.size() - 2);
                if (checkCharacters(searchInput)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                tree.searchName(tree.root, searchInput);
            }
        } else if (command == "printInorder") {
            tree.printInorder(tree.root);
        } else if (command == "printPreorder") {
            tree.printPreorder(tree.root);
        } else if (command == "printPostorder") {
            tree.printPostorder(tree.root);
        } else if (command == "printLevelCount") {
            tree.printLevelCount();
        } else if (command == "removeInorder") {
            getline(ss ,nodeNumber, ' ');
            getline(ss ,nodeNumber, ' ');
            if (!checkNumbers(nodeNumber) && stoi(nodeNumber) > -1) {
                tree.removeInorderN(stoi(nodeNumber));
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    }
}

int main() {
    commandLine();
    return 0;
}
