/*
 * FSTreeTraversal.cpp
 * Authors: Caleb Johnson and Owen Short
 * Date: 11/30/23
 * Purpose: TODO
 */

#include "DirNode.h"
#include "FSTree.h"

using namespace std;
#include <iostream>

// Function Declarations:
void preOrderTraversal(DirNode *root, string parentsString);

int main(int argc, char *argv[]) {
    // check usage
    if (argc != 2) {
        cerr << "Usage: ./treeTraversal Directory\n";
        exit(EXIT_FAILURE);
    }

    FSTree rootDirectory(argv[1]);
    DirNode *root = rootDirectory.getRoot();
    preOrderTraversal(root, argv[1]);

    return 0;
}

void preOrderTraversal(DirNode *root, string parentsString) {
    int numSubDirs = root->numSubDirs();
    int numFiles = root->numFiles();
    if (not root->hasSubDir()) {
        for (int i = 0; i < numFiles; i++) {
            cout << parentsString << "/" << root->getFile(i) << endl;
        }
        return;
    }
    else {
        for (int i = 0; i < numFiles; i++) {
            cout << parentsString << "/" << root->getFile(i) << endl;
        }
        for (int i = 0; i < numSubDirs; i++) {
            DirNode *subDirectory(root->getSubDir(i));
            string subDirectoryName = subDirectory->getName();
            string newParentsString = parentsString + "/" + subDirectoryName;
            preOrderTraversal(subDirectory, newParentsString);
        }
    }
}