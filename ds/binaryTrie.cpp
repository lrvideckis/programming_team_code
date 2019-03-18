#include <bits/stdc++.h>
using namespace std;

const int Log = 20;

struct binaryTrie {
    struct node {
        int minElem;
        node *left, *right;
        node() {
            minElem = 1e8;
            left = right = nullptr;
        }
    };
    node *root;
    binaryTrie() {
        root = new node();
    }
    void insert(int num) {
        node *curr = root;
        for(int bit = Log-1; bit >= 0; --bit) {
            curr->minElem = min(curr->minElem, num);
            if(num&(1<<bit)) {//insert into right subtree
                if(curr->right == nullptr) {
                    curr->right = new node();
                }
                curr = curr->right;
            } else {//insert into left subtree
                if(curr->left == nullptr) curr->left = new node();
                curr = curr->left;
            }
            curr->minElem = min(curr->minElem, num);
        }
    }
    int query(int constant, int x) {
        int sum = 0;
        node *curr = root;
        if(curr->minElem > constant) return -1;
        for(int bit = Log-1; bit >= 0; --bit) {
            if(x&(1<<bit)) {
                if(curr->left != nullptr) {
                    curr = curr->left;
                } else if(curr->right != nullptr && curr->right->minElem <= constant) {
                    curr = curr->right;
                    sum += (1<<bit);
                } else { 
                    return -1;
                }
            } else {
                if(curr->right != nullptr && curr->right->minElem <= constant) {
                    curr = curr->right;
                    sum += (1<<bit);
                } else if(curr->left != nullptr) {
                    curr = curr->left;
                } else {
                    return -1;
                }
            }
        }
        return sum;
    }
};

int main() {
    return 0;
}
















