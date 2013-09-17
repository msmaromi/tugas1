
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
    int depth;

public:
    Tree();
    Tree(string);
    ~Tree();
    
    void addTree(Tree*);
    void addBranch(string);
    
    Tree* getLeft();
    Tree* getCenter();
    Tree* getRight();
    
    string getLeftBranch();
    string getCenterBranch();
    string getRightBranch();
        
    bool isLeaf();
    bool isNode();
    void setData(string);
    string getData();
    
    void printTree();
};


#endif