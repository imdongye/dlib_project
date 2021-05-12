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

class Student {
private:
	long id;
	string name;
	double mid;
	double fin;
public:
	Student(long _id = 0, string _name = "", double _mid = 0.0, double _fin = 0.0)
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
		return a.id == b.id;
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
	bool termination = false;
	while (!termination)
	{
		int operationCode = 0;
		cout << "Enter Operation Code: ";
		cin >> operationCode;
		// 1: add
		// 2: delete by id
		// 3: print with id order ( in order )
		// 4: find student with id and print
		// 5: end program
		switch (operationCode) {
			// add
			case 1: { 
				cout << "Enter ID, name, mid, final scores: ";
				long id;
				string name;
				double mid, fin;
				cin >> id >> name >> mid >> fin;
				Student student(id, name, mid, fin);
				if (bsTree.insert(student) == false) // insert with same key is fatal
					cout << "Duplicated ID" << endl;
			} break;
			// delete by id
			case 2: { 
				cout << "Enter ID: ";
				long id;
				cin >> id;
				if (bsTree.find(Student(id)) == Student()) // Student(id) == {id} private member also can Brace initialization
					cout << "No matching student" << endl;
				else
					bsTree.remove(Student(id)); // remove with missing key is not fatal
			} break;
			// print with id order ( in order )
			case 3: { 
				bsTree.visit([](const Student& s) {cout << s << ","; });
				cout << endl;
			} break;
			// find student with id and print
			case 4: { 
				cout << "Enter ID: ";
				long id;
				cin >> id;
				Student s = bsTree.find(Student(id));
				if (s == Student())
					cout << "No matching student" << endl;
				else
					cout << s << endl;
			} break;
			// end program
			case 5: { 
				termination = true;
			} break;
			default: {
				cout << "Wrong operation code !!\n";
			} break;
		}
		// wrong input make infinity that above roop
		// so erase input state and buffer to clear
		if (cin.fail()) { cin.clear(); cin.ignore(10, '\n'); }
	}
	return 0;
}