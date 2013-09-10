
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>

using namespace std;

class tree{
	private:

	public:
		tree* parent;
		tree* left;
		string left_con;
		tree* center;
		string center_con;
		tree* right;
		string right_con;
		
		string data;
		
		tree();
		tree(string s);
		~tree();
		void insert_child(string s, tree* v);
};


#endif