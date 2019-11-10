#include <stdlib.h>
#include "AVLTermNode.cpp"

using namespace std;

class AVLTermTree {

public:
    AVLTermNode *root = nullptr;
    size_t nodesCount = 0;

    void insert(term &term) {
        if (root == nullptr) {
            root = new AVLTermNode(term);
            nodesCount++;
            return;
        }
        root = insert(root, term);
    }

private:

    AVLTermNode *insert(AVLTermNode *node, term &term) {

        if (node == nullptr) {
            nodesCount++;
            return new AVLTermNode(term);
        }

        if (term.str.compare(node->term) == 0) {
            node->count++;
            node->docIdMap[term.docId].push_back(term.pos);
            return node;
        } else if (term.str.compare(node->term) < 0) {
            node->leftChild = insert(node->leftChild, term);
        } else {
            node->rightChild = insert(node->rightChild, term);
        }

        AVLTermNode *balancedNode = balanced(node);
        balancedNode->height = max(balancedNode->leftHeight(), balancedNode->rightHeight()) + 1;

        return balancedNode;
    }

    AVLTermNode *balanced(AVLTermNode *node) {
        if (node->balanceFactor() == 2 && node->leftChild != nullptr && node->leftChild->balanceFactor() == -1) {
            return leftRightRotate(node);
        } else if (node->balanceFactor() == 2) {
            return rightRotate(node);
        } else if (node->balanceFactor() == -2 && node->rightChild != nullptr && node->rightChild->balanceFactor() == 1) {
            return rightLeftRotate(node);
        } else if (node->balanceFactor() == -2) {
            return leftRotate(node);
        }
        return node;
    }

    AVLTermNode *leftRotate(AVLTermNode *node) {
        AVLTermNode *pivot = node->rightChild;

        node->rightChild = pivot->leftChild;
        pivot->leftChild = node;

        node->height = max(node->leftHeight(), node->rightHeight()) + 1;
        pivot->height = max(pivot->leftHeight(), pivot->rightHeight()) + 1;

        return pivot;
    }

    AVLTermNode *rightRotate(AVLTermNode *node) {
        AVLTermNode *pivot = node->leftChild;

        node->leftChild = pivot->rightChild;
        pivot->rightChild = node;

        node->height = max(node->leftHeight(), node->rightHeight()) + 1;
        pivot->height = max(pivot->leftHeight(), pivot->rightHeight()) + 1;

        return pivot;
    }

    AVLTermNode *rightLeftRotate(AVLTermNode *node) {
        if (node->rightChild == nullptr) {
            return node;
        }

        node->rightChild = rightRotate(node->rightChild);

        return leftRotate(node);
    }

    AVLTermNode *leftRightRotate(AVLTermNode *node) {
        if (node->leftChild == nullptr) {
            return node;
        }

        node->leftChild = leftRotate(node->leftChild);

        return rightRotate(node);
    }
    
};
