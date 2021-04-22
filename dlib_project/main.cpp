//
//	main.cpp
//	Build my data structures
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
	int mid;
	int fin;
public:
	Student()
		: id(0), name(""), mid(0), fin(0) {}
	Student(long _id, string _name, int _mid = 0, int _fin = 0)
		: id(_id), name(_name), mid(_mid), fin(_fin) { }
	~Student() {

	}

	// private멤버 ostream을 수정하기위해서 friend 함수로 정의
	friend ostream& operator << (ostream& os, const Student& s) {
		os << "[" << s.id << ", " << s.name << ", " << s.mid << ", " << s.fin << ", " << s.getAverage() << "]";
		return os;
	}
	const long& getId() const {
		return id;
	}
	const string& getName() const {
		return name;
	}
	const double getAverage() const {
		return (mid + fin) / 2.0;
	}
	void setMid(int _mid) {
		mid = _mid;
	}
	void setFin(int _fin) {
		fin = _fin;
	}
};

template <typename T> void print(const T& list) {
	for (const auto& item : list) {
		cout << item << " ";
	}
	cout << endl;
}

int main()
{
	//dtd::dvec<Student> students = { {123, "John"}, {312, "Jane"}, {111, "Jacob"}, {311, "Jack"} };
	dtd::dvec<Student> students;

	students.push_back({ 201821089, "임동예", 50, 60 });
	students.push_back({ 201712312, "김동예", 80, 70 });
	students.push_back({ 201112312, "이동예", 47, 19 });
	students.push_back({ 202212313, "박동예", 48, 19 });
	students.push_back({ 202212313, "신동예", 77, 66 });

	bool termination = false;
	while (!termination)
	{
		print(students);
		int operationCode = 0;
		cout << "Enter Operation Code: ";
		cin >> operationCode;
		switch (operationCode) {
		case 1: { // add
			cout << "Enter ID, name, mid, final scores: ";
			long id;
			string name;
			int mid, fin;
			cin >> id >> name >> mid >> fin;
			Student student(id, name, mid, fin); // student = {id, name..};
			students.push_back(student);
		} break;
		case 2: { // delete by id
			cout << "Enter ID: ";
			long id;
			cin >> id;
			// remove_if에서 student를 수정하지 못해서 remove_if의 반환값으로 erase함수를 다시 호출함
			// ??find_if를 안쓰는이유??
			students.erase(remove_if(students.begin(), students.end(), [id](const Student& a) { return a.getId() == id; }));
		} break;
		case 3: { // delete by name
			cout << "Enter Name: ";
			string name;
			cin >> name;
			students.erase(remove_if(students.begin(), students.end(), [name](const Student& a) { return a.getName().compare(name) == 0; }));
		} break;
		case 4: { // update mid by id
			cout << "Enter ID and Midterm Score:";
			long id;
			int mid;
			cin >> id >> mid;
			Student* student = find_if(students.begin(), students.end(), [id](const Student& a) { return a.getId() == id; });
			student->setMid(mid);
		} break;
		case 5: { // update mid by id
			cout << "Enter ID and Final Score:";
			long id;
			int fin;
			cin >> id >> fin;
			Student* student = find_if(students.begin(), students.end(), [id](const Student& a) { return a.getId() == id; });
			student->setFin(fin);
		} break;
		case 6: { // sort by id
			// ??remove_if는 student를 수정하지 못하는데 똑같이 이터레이터를 받는 sort는 어떻게 수정하는지??
			sort(students.begin(), students.end(), [](const Student& a, const Student& b) {return a.getId() < b.getId(); });
		} break;
		case 7: { // sort by average
			sort(students.begin(), students.end(), [](const Student& a, const Student& b) {return a.getAverage() > b.getAverage(); });
		} break;
		case 8: { // end program
			termination = true;
		} break;
		default: {
			cout << "Wrong operation code !!\n";
		} break;
		}
		if (cin.fail()) { cin.clear(); cin.ignore(10, '\n'); } // 입력잘못했을때 무한루프 빠짐 -> 입력버퍼 지워주기
	}
	return 0;
}
