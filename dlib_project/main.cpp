//
//  main.cpp
//  Build my data structures
//
//  Create by 임동예 on 2021/04/17.
//
#include <iostream>
#include <algorithm>
#include "dlib.h"
using namespace std;

class Student {
private:
	long id;
	string name;
	double mid;
	double fin;
public:
	Student()
		: id(0), name(""), mid(0.0), fin(0.0) {}
	Student(long _id, string _name, double _mid = 0.0, double _fin = 0.0)
		: id(_id), name(_name), mid(_mid), fin(_fin) { }
	~Student() {
	}
	// friend is for editing ostream
	friend ostream& operator << (ostream& os, const Student& s) {
		os << "[" << s.id << ", " << s.name << ", " << s.mid << ", " << s.fin << ", " << s.getAverage() << "]";
		return os;
	}
	friend bool operator < (const Student& a, const Student& b) {
		return a.id < b.id;
	}
	friend bool operator > (const Student& a, const Student& b) {
		return a.id > b.id;
	}
	friend bool operator == (const Student& a, const Student& b) {
		return a.id == b.id && a.name == b.name;
	}
	const long& getId() const {
		return id;
	}
	const string& getName() const {
		return name;
	}
	const double getAverage() const {
		double sum = mid + fin;
		return sum / 2.0;
	}
	void setMid(const double _mid) {
		mid = _mid;
	}
	void setFin(const double _fin) {
		fin = _fin;
	}
};

int main() {
	dtd::BST<Student> bsTree;
	bsTree.insert(Student(1236, "eee"));
	bsTree.insert(Student(1231, "bbb"));
	bsTree.insert(Student(1232, "ccc"));
	bsTree.insert(Student(1237, "ccc"));
	bsTree.insert(Student(1233, "ddd"));
	bsTree.insert(Student(1235, "fff"));
	bsTree.insert(Student(1230, "aaa"));
	bsTree.insert(Student(1234, "eee"));
	// in-order 깊이우선 정렬된 결과
	bsTree.visit([](const Student& s) {cout << s << ","; });
	cout << endl;
	//bstree.remove({ 1233, "ddd" });
	//bstree.visit([](const Student& s) {cout << s << ","; });
	cout << bsTree.find(Student(1233, "ddd"));
	cout << endl;

	
	return 0;
}