//
//  main.cpp
//  Build my data structures
//
//  Create by �ӵ��� on 2021/04/17.
//


#include <iostream>
#include <algorithm>
#include "dlib.h"
using namespace std;

int main() {
	dtd::BST tree;
	tree.insert(3);
	tree.visit([](dtd::BST::Node* node) {cout << node->val << endl; });
	return 0;
}