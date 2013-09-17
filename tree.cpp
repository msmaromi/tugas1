#include "tree.h"

Tree::Tree() {
    left = NULL;
    center = NULL;
    right = NULL;
    leftBranch = "";
    centerBranch = "";
    rightBranch = "";
    data = "";
}

Tree::Tree(string s) {   
    left = NULL;
    center = NULL;
    right = NULL;
    leftBranch = "";
    centerBranch = "";
    rightBranch = "";
    data = s;
}

Tree::~Tree() {
    
}

void Tree::addTree(Tree* t)  {
    if (left==NULL) {
        left = t;
    } else if (center==NULL) {
        center = t;
    } else if (right==NULL) {
        right = t;
    }
}

void Tree::addBranch(string s) {
    if (leftBranch=="") {
        leftBranch = s;
    } else if (centerBranch=="") {
        centerBranch = s;
    } else if (rightBranch=="") {
        rightBranch = s;
    }
}


Tree* Tree::getLeft() {
    return left;
}

Tree* Tree::getCenter() {
    return center;
}

Tree* Tree::getRight() {
    return right;
}

string Tree::getLeftBranch() {
    return leftBranch;
}

string Tree::getCenterBranch() {
    return centerBranch;
}

string Tree::getRightBranch() {
    return rightBranch;
}

bool Tree::isLeaf() {
    if (left==NULL && center==NULL && right==NULL) {
        return true;
    } else {
        return false;
    }
}

void Tree::setData(string s) {
    data = s;
}

string Tree::getData() {
    return data;
}

void Tree::printTree() {  
    if (isLeaf()) {
        cout << data << endl;
        
    } else {
        cout << "--";
        cout << data;
        cout << "=";
        cout << leftBranch;
        if (left->isLeaf()) {
            cout << " ";
        } else {
            cout << endl;
            //cout << "--";
        }
        left->printTree();
        
        if (centerBranch!="") {
            cout << "--";
            cout << data;
            cout << "=";
            cout << centerBranch;
            if (center->isLeaf()) {
                cout << " ";
            } else {
                cout << endl;
                //cout << "--";
            }
            center->printTree();
            
            if (rightBranch!="") {
                cout << "--";
                cout << data;
                cout << "=";
                cout << rightBranch;
                if (right->isLeaf()) {
                    cout << " ";
                } else {
                    cout << endl;
                    //cout << "--";
                }
                right->printTree();
            }
        }
    }
}



