#include "tree.h"

tree::tree(){
	data="";
}
tree::tree(string s){
	this->data = s;
}
tree::~tree(){}

void tree::insert_child(string s, tree* t){
	if(this->left_con == ""){
		this->left = t;
		t->parent = this;
	} else if (this->center_con==""){
		this->center = t;
		t->parent = this;
	} else if (this->right_con==""){
		this->right = t;
		t->parent = this;
	}
}
int main(){
	return 0;
}
