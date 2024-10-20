#pragma once

#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
#endif //PROJECT1_AVL_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Node {
public:
    int GatorId;
    string name;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int _GatorId, string _name) {
        GatorId = _GatorId;
        name = _name;
    }
};

class AVL {
public:
    Node *root = nullptr;

    AVL() = default;

    AVL(Node *_root) {
        root = _root;
    }

    ~AVL() {
        clearAVL(root);
    }

    // Inserts new nodes into the AVL tree
    Node *insert(Node *node, int id, string name, bool &worked) {
        if (node == nullptr) return new Node(id, name);
        if (id < node->GatorId) {
            node->left = insert(node->left, id, name, worked);
        } else if (id > node->GatorId) {
            node->right = insert(node->right, id, name, worked);
        } else {
            cout << "unsuccessful" << endl;
            worked = false;
            return node;
        }

        int difference = balance(node);
        if (difference > 1) {
            if (id > node->left->GatorId) {
                node->left = rotateLeft(node->left);
                root = rotateRight(node);
                return root;
            }
            root = rotateRight(node);
            return root;
        } else if (difference < -1) {
            if (id < node->right->GatorId) {
                node->right = rotateRight(node->right);
                root = rotateLeft(node);
                return root;
            }
            root = rotateLeft(node);
            return root;
        } else {
            root = node;
            return root;
        }
    }

    Node *removeId(Node *node, int id) {
        // Case if the node to be removed is the root
        if (node == root) {
            if (removeSearch(root, id) == nullptr) {
                cout << "unsuccessful" << endl;
                return nullptr;
            } else if (node->GatorId == id) {
                cout << "successful" << endl;
                Node *deletedNode = node;
                if (deletedNode->left == nullptr && deletedNode->right == nullptr) {
                    delete deletedNode;
                    root = nullptr;
                } else if (deletedNode->left == nullptr) {
                    node = deletedNode->right;
                    root = node;
                    delete deletedNode;
                } else if (deletedNode->right == nullptr) {
                    node = deletedNode->left;
                    root = node;
                    delete deletedNode;
                } else if (deletedNode->left->right == nullptr) {
                    node->left->right = deletedNode->right;
                    node = deletedNode->left;
                    root = node;
                    delete deletedNode;
                } else if (deletedNode->right->left == nullptr) {
                    node->right->left = deletedNode->left;
                    node = deletedNode->right;
                    root = node;
                    delete deletedNode;
                } else {
                    Node *replacementAncestor = findLeftSuccessor(deletedNode->right);
                    node = replacementAncestor->left;
                    if (replacementAncestor->left->right != nullptr) {
                        replacementAncestor->left = replacementAncestor->left->right;
                    } else {
                        replacementAncestor->left = nullptr;
                    }
                    node->right = deletedNode->right;
                    node->left = deletedNode->left;
                    root = node;
                    delete deletedNode;
                }
                deletedNode = nullptr;
                return nullptr;
            }
        }
        if (node == nullptr) return nullptr;
        if (node->GatorId == id) {
            return node;
        }
        // Left recursive case to find ancestor of node to be removed
        if (removeId(node->left, id) != nullptr) {
            cout << "successful" << endl;
            Node *deletedNode = node->left;
            if (deletedNode->right == nullptr) {
                node->left = deletedNode->left;
                delete deletedNode;
            } else if (deletedNode->left == nullptr) {
                node->left = deletedNode->right;
                delete deletedNode;
            } else if (deletedNode->left->right == nullptr) {
                node->left = deletedNode->left;
                node->left->right = deletedNode->right;
                delete deletedNode;
            } else if (deletedNode->right->left == nullptr) {
                node->left = deletedNode->right;
                node->left->left = deletedNode->left;
                delete deletedNode;
            } else {
                Node *replacementAncestor = findLeftSuccessor(deletedNode->right);
                node->left = replacementAncestor->left;
                if (replacementAncestor->left->right != nullptr) {
                    replacementAncestor->left = replacementAncestor->left->right;
                } else {
                    replacementAncestor->left = nullptr;
                }
                node->left->right = deletedNode->right;
                node->left->left = deletedNode->left;
                delete deletedNode;
            }
            deletedNode = nullptr;
            return nullptr;
        }
        // Right recursive case to find ancestor of node to be removed
        if (removeId(node->right, id) != nullptr) {
            cout << "successful" << endl;
            Node *deletedNode = node->right;
            if (deletedNode->left == nullptr) {
                node->right = deletedNode->right;
                delete deletedNode;
            } else if (deletedNode->right == nullptr) {
                node->right = deletedNode->left;
                delete deletedNode;
            } else if (deletedNode->left->right == nullptr) {
                node->right = deletedNode->left;
                node->right->right = deletedNode->right;
                delete deletedNode;
            } else if (deletedNode->right->left == nullptr) {
                node->right = deletedNode->right;
                node->right->right = deletedNode->left;
                delete deletedNode;
            } else {
                Node *replacementAncestor = findRightSuccessor(deletedNode->left);
                node->right = replacementAncestor->right;
                if (replacementAncestor->right->left != nullptr) {
                    replacementAncestor->right = replacementAncestor->right->left;
                } else {
                    replacementAncestor->right = nullptr;
                }
                node->right->right = deletedNode->right;
                node->right->left = deletedNode->left;
                delete deletedNode;
            }
            deletedNode = nullptr;
            return nullptr;
        }
        return nullptr;
    }

    Node *searchId(Node *node, int id) {
        Node *returnNode = searchIdHelper(node, id);
        if (returnNode == nullptr) {
            cout << "unsuccessful" << endl;
        }
        return returnNode;
    }

    void searchName(Node *node, string name) {
        stringstream ids;
        searchNameHelper(node, name, ids);
        if (ids.str().empty()) {
            cout << "unsuccessful" << endl;
        } else {
            cout << ids.str();
        }
    }

    void printInorder(Node *node) {
        stringstream names;
        printInHelper(node, names);
        string showNames = names.str();
        cout << showNames.substr(0, showNames.size() - 2) << endl;
    }

    void printPreorder(Node *node) {
        stringstream names;
        printPreHelper(node, names);
        string showNames = names.str();
        cout << showNames.substr(0, showNames.size() - 2) << endl;
    }

    void printPostorder(Node *node) {
        stringstream names;
        printPostHelper(node, names);
        string showNames = names.str();
        cout << showNames.substr(0, showNames.size() - 2) << endl;
    }

    // Displays height of tree
    void printLevelCount() {
        cout << to_string(height(root)) << endl;
    }

    // Removes a node at position n of the in order traversal
    void removeInorderN(int n) {
        int nodeCount = 0;
        removeInorderNHelper(root, n, nodeCount);
        if (nodeCount != -1) {
            cout << "unsuccessful" << endl;
        }
    }

    // Function for unit tests that modifies an array with the in order id's of the tree
    void inOrderList(Node* node, vector<int> &vec) {
        if (node == nullptr) return;
        inOrderList(node->left, vec);
        vec.push_back(node->GatorId);
        inOrderList(node->right, vec);
    }

private:
    // Helper function to remove an in order node
    void removeInorderNHelper(Node *node, int n, int &count) {
        if (node == nullptr) return;
        removeInorderNHelper(node->left, n, count);
        if (count == n) {
            removeId(root, node->GatorId);
            count = -1;
            return;
        }
        if (count != -1) {
            count++;
        }
        removeInorderNHelper(node->right, n, count);
    }

    // Helper function to ensure a comma is not printed at the end and to collect names
    void printPostHelper(Node *node, stringstream &s) {
        if (node == nullptr) return;
        printPostHelper(node->left, s);
        if (node->left == nullptr && node->right == nullptr) {
            s << node->name << ", ";
            return;
        }
        printPostHelper(node->right, s);
        s << node->name << ", ";
    }

    // Helper function to ensure a comma is not printed at the end and to collect names
    void printPreHelper(Node *node, stringstream &s) {
        if (node == nullptr) return;
        s << node->name << ", ";
        printPreHelper(node->left, s);
        printPreHelper(node->right, s);
    }

    // Helper function to ensure a comma is not printed at the end and to collect names
    void printInHelper(Node *node, stringstream &s) {
        if (node == nullptr) return;
        printInHelper(node->left, s);
        s << node->name << ", ";
        printInHelper(node->right, s);
    }

    // Helper function for searchName that allows it to display "unsuccessful" and provides a stream to push values to,
    // so they can be printed
    void searchNameHelper(Node *node, string name, stringstream &s) {
        if (node == nullptr) return;
        if (node->name == name) {
            s << to_string(node->GatorId) << endl;
        }
        searchNameHelper(node->left, name, s);
        searchNameHelper(node->right, name, s);
    }

    // Helper function for searchId that allows it to display "unsuccessful"
    Node *searchIdHelper(Node *node, int id) {
        if (node == nullptr) return nullptr;
        if (node->GatorId == id) {
            return node;
        }
        if (id < node->GatorId) return searchIdHelper(node->left, id);
        else return searchIdHelper(node->right, id);
    }

    // Finds the ancestor of the inorder successor on the left
    Node *findLeftSuccessor(Node *node) {
        if (node->left->left == nullptr) {
            return node;
        }
        return findLeftSuccessor(node->left);
    }

    // Finds the ancestor of the inorder successor on the right
    Node *findRightSuccessor(Node *node) {
        if (node->right->right == nullptr) {
            return node;
        }
        return findRightSuccessor(node->right);
    }

    // Remove helper function that detects if the id is even in the tree
    Node *removeSearch(Node *node, int id) {
        if (node == nullptr) return nullptr;
        if (node->GatorId == id) {
            return node;
        }
        if (id < node->GatorId) return removeSearch(node->left, id);
        else return removeSearch(node->right, id);
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Finds the balance factor at a node
    int balance(Node *node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    // Gets the height of the tree from the node given
    int height(Node *node) {
        if (node == nullptr) return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    Node *rotateRight(Node *node) {
        Node *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    Node *rotateLeft(Node *node) {
        Node *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    // Recursively deletes the nodes of the tree
    void clearAVL(Node *node) {
        if (node == nullptr) return;
        clearAVL(node->left);
        clearAVL(node->right);
        delete node;
        node = nullptr;
        root = nullptr;
    }
};
