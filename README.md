# AVL-Tree
- An AVL Tree implementation to store and retrieve student id's efficiently through the command line
- Created with C++ and uses Catch2 Unit Testing

# Available Commands:
- First, enter the number of the amount of commands you will use. Then, use the following commands to interact with the AVL tree
- insert "NAME" ID: Add a student with specified name and GatorID. Prints "successful" if successful, "unsuccessful" otherwise.
- remove ID: Remove the student with the specified GatorID. Prints "successful" or "unsuccessful."
- search ID: Search for a student by GatorID. Prints their name or "unsuccessful" if not found.
- search "NAME": Search for a student by name. Prints their GatorID(s) or "unsuccessful" if not found.
- printInorder: Print a comma-separated inorder traversal of the student names.
- printPreorder: Print a comma-separated preorder traversal of the student names.
- printPostorder: Print a comma-separated postorder traversal of the student names.
- printLevelCount: Print the number of levels in the tree (prints 0 if tree is empty).
- removeInorder N: Remove the Nth student (by GatorID) from the inorder traversal. Prints "successful" or "unsuccessful."
