//
//  main.cpp
//  Build my data structures
//
//  Create by ÀÓµ¿¿¹ on 2021/04/17.
//
#include <iostream>
#include <algorithm>
#include "dlib.h"
using namespace std;


int main() {
	dtd::dtree dtr = dtd::dtree("a");
	dtr.addSub("a", "b");
	dtr.addSub("a", "c");
	dtr.addSub("c", "d");
	dtr.addSub("c", "e");
	dtr.addSub("c", "f");
	dtr.addSub("e", "g");
	dtr.print();
	return 0;
}