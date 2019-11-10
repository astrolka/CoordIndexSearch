#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct term {
    string &str;
    unsigned docId;
    unsigned pos;
};

class AVLTermNode {

public:
    string term;
    unsigned count;
    map<unsigned, vector<unsigned>> docIdMap;

    AVLTermNode *leftChild = nullptr;
    AVLTermNode *rightChild = nullptr;

    size_t height = 0;

    size_t leftHeight() {
        if (leftChild == nullptr) {
            return -1;
        }
        return leftChild->height;
    }
    size_t rightHeight() {
        if (rightChild == nullptr) {
            return -1;
        }
        return rightChild->height;
    }
    int balanceFactor() {
        return leftHeight() - rightHeight();
    }

    AVLTermNode(struct term t) {
        term = t.str;
        docIdMap[t.docId].push_back(t.pos);
        count = 1;
    }

    ~AVLTermNode() {
        delete this;
    }

};