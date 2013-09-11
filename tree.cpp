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
    if (s=="outlook") {
        leftBranch = "sunny";
        centerBranch = "overcast";
        rightBranch = "rain";
    } else if (s=="temperature") {
        leftBranch = "hot";
        centerBranch = "mild";
        rightBranch = "cool";
    } else if (s=="humidity") {
        leftBranch = "high";
        centerBranch = "";
        rightBranch = "normal";
    } else if (s=="wind") {
        leftBranch = "strong";
        centerBranch = "";
        rightBranch = "weak";
    }
    left = NULL;
    center = NULL;
    right = NULL;
    data = s;
}

void Tree::setLeft(Tree t) {
    left = &t;
}

void Tree::setCenter(Tree t) {
    center = &t;
}

void Tree::setRight(Tree t) {
    right = &t;
}

void Tree::setLeftBranch(string s) {
    leftBranch = s;
}

void Tree::setCenterBranch(string s) {
    centerBranch = s;
}

void Tree::setRightBranch(string s) {
    rightBranch = s;
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

void Tree::addNode(string s) {
   
}

bool Tree::isLeaf() {
    if (left==NULL && center==NULL && right==NULL) {
        return true;
    } else {
        return false;
    }
}

bool Tree::isNode() {
    if (this!=NULL) {
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
    cout << "(";
    if (isLeaf()) {
        cout << data;
    } else {
        cout << data;
        cout << "(";

        cout << leftBranch << "(";
        if (left->isNode()) {
            left->printTree();
        } else {
            cout << left->getData() << "),";
        }
        if (centerBranch!="") {
            cout << centerBranch << "(";
            if (center->isNode()) {
                center->printTree();
            } else {
                cout << center->getData() << "),";
            }
        } else {
            cout << rightBranch << "(";
            if (right->isNode()) {
                right->printTree();
            } else {
                cout << right->getData() << ")";
            }
            cout << ")";
        }
    }
    cout << ")";
}



