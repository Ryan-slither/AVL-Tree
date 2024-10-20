/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include "AVL.h"

using namespace std;

bool checkCharacters(string name) {
    for (auto c : name) {
        if (c < 'a' || c > 'z' || c < 'A' || c > 'Z' || c != ' ') {
            return false;
        }
    }
    return true;
}

bool checkNumbers(string possibleNumbers) {
    for (auto c : possibleNumbers) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Incorrect Commands", "[flag]") {
    istringstream testInput(
                "5 "
                "insert \"Gh0st\" 32432122 "
                "insert \"Ghost\" 324ab122 "
                "remove 123451 "
                "removeInorder -5 "
                "printWhat "
            );
    streambuf *cinBuff = cin.rdbuf();
    cin.rdbuf(testInput.rdbuf());

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

    vector<int> vec;
    vector<int> result {};
    tree.inOrderList(nullptr, vec);
    REQUIRE(vec == result);
    cin.rdbuf(cinBuff);
}

TEST_CASE("Edge Cases", "[flag]"){
    AVL tree(nullptr);
    bool success = false;
    tree.root = new Node(1, "a");
    vector<int> vec;
    vector<int> result {0, 1, 2, 3};
    tree.insert(tree.root, 0, "b", success);
    tree.insert(tree.root, 2, "c", success);
    tree.insert(tree.root, 3, "d", success);
    SECTION("Remove Non-existent Node") {
        tree.removeId(tree.root, 15);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
    SECTION("Search for ID not in the tree") {
        tree.searchId(tree.root, 6);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
    SECTION("Removing an N node not in the list") {
        tree.removeInorderN(6);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
}

TEST_CASE("Rotations", "[flag]") {
    AVL tree(nullptr);
    bool success = false;
    tree.root = new Node(3, "a");
    vector<int> vec;
    SECTION("Left Rotation") {
        vector<int> result{3, 4, 5};
        tree.insert(tree.root, 4, "c", success);
        tree.insert(tree.root, 5, "d", success);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
    SECTION("Right Rotation") {
        vector<int> result{1, 2, 3};
        tree.insert(tree.root, 2, "c", success);
        tree.insert(tree.root, 1, "d", success);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
    SECTION("Left Right Rotation") {
        vector<int> result{1, 2, 3};
        tree.insert(tree.root, 1, "c", success);
        tree.insert(tree.root, 2, "d", success);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
    SECTION("Right Left Rotation") {
        vector<int> result{3, 4, 5};
        tree.insert(tree.root, 5, "c", success);
        tree.insert(tree.root, 4, "d", success);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
}

TEST_CASE("Deletions", "[flag]"){
	AVL tree(nullptr);
    bool success = false;
    tree.root = new Node(1, "a");
    SECTION("No Children") {
        vector<int> vec;
        vector<int> result {1};
        tree.insert(tree.root, 2, "b", success);
        tree.removeId(tree.root, 2);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
    SECTION("One Child") {
        vector<int> vec;
        vector<int> result {0, 1, 3};
        tree.insert(tree.root, 0, "b", success);
        tree.insert(tree.root, 2, "c", success);
        tree.insert(tree.root, 3, "d", success);
        tree.removeId(tree.root, 2);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
    SECTION("Two Children") {
        vector<int> vec;
        vector<int> result {0, 2, 3};
        tree.insert(tree.root, 0, "b", success);
        tree.insert(tree.root, 2, "c", success);
        tree.insert(tree.root, 3, "d", success);
        tree.removeId(tree.root, 1);
        tree.inOrderList(tree.root, vec);
        REQUIRE(vec == result);
    }
}

TEST_CASE("Too Many Nodes", "[flag]") {
    AVL tree(new Node(100, "g"));
    bool success = false;
    vector<int> vec;
    for (int i = 1; i < 100; ++i) {
        tree.insert(tree.root, i, "a", success);
    }

    for (int i = 0; i < 10; ++i){
        vec.clear();
        int removed = rand() % 100 + 1;
        tree.inOrderList(tree.root, vec);
        tree.removeInorderN(removed);
    };
    vec.clear();
    tree.inOrderList(tree.root, vec);
    REQUIRE(is_sorted(vec.begin(), vec.end()));
    REQUIRE(vec.size() == 90);
}
*/