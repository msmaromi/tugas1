
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>

using namespace std;

class Tree{
private:
    Tree* left;
    string leftBranch;
    Tree* center;
    string centerBranch;
    Tree* right;
    string rightBranch;
    
    string data;

public:
    Tree();
    Tree(string);
    
    void setLeft(Tree);
    void setCenter(Tree);
    void setRight(Tree);
    
    void setLeftBranch(string);
    void setCenterBranch(string);
    void setRightBranch(string);
    
    Tree* getLeft();
    Tree* getCenter();
    Tree* getRight();
    
    string getLeftBranch();
    string getCenterBranch();
    string getRightBranch();
    
    void addNode(string);
    bool isLeaf();
    bool isNode();
    void setData(string);
    string getData();
    
    void printTree();
};


#endif