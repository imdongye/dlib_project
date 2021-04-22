//
//	dlib.h
//	Build my data structures
//
//  Create by 임동예 on 2021/04/17.
//

//#pragma once
#ifndef dlib_hpp
#define dlib_hpp

#include <iostream>

// 올드
#define MIN(X,Y) ((X)<(Y)?(X):(Y))
// 뉴 + 요즘은 언더바 없이 inline로 쓸수있음
template <typename T>
__inline T min(T a, T b) {
	if (a < b) return a;
	return b;
}

namespace dtd
{
	template<typename T>
	class dfront_list {
		template<typename T>
		class node {
			T data;
			node<T>* next = nullptr;
			friend class dfront_node;
		public:
			node(T _data) : data(_data), next(nullptr) {}
			node(T _data, node<T>* _next) : data(_data), next(_next) {}
			T getData() const {
				return data;
			}
			void setData(const T& _data) {
				data = _data;
			}
			node<T>* getNext() const {
				return next;
			}
			void setNext(node<T>*& _next) {
				next = _next;
			}
		};
		node<T>* front = nullptr;
		size_t size = 0;
		node<T>* move_node(node<T>* cur, size_t count) {
			if (count == 0)
				return cur;
			else {
				if (cur->next != nullptr)
					return move_node(cur->next, count--);
				else
					return cur;
			}
		}
	public:
		dfront_list() {}
		dfront_list(size_t _size) {
			for (int i = 0; i < _size; i++) {
				push_front(nullptr);
			}
		}
		void push_front(T _data) {
			if (front == nullptr) {
				node<T>* newNode = new node<T>(_data);
				front = newNode;
			}
			else {
				node<T>* newNode = new node<T>(_data, front);
				front = newNode;
			}
			size++;
		}
		// 랜덤 접근 읽기
		const T& operator [] (const size_t n) const {
			return move_node(n)->data;
		}
		// 랜덤 접근 쓰기
		T& operator [] (const size_t n) {
			return move_node(n)->data;
		}
	};

	// 템플릿 클래스는 정의가 hpp파일에 있어야 컴파일때 인식할수있음
	template <typename T>
	class dvec {
		T* data = nullptr;
		// size_t 는 unsigned int
		size_t n;
		// 여유있는 배열공간 잡기 capacity
		size_t capacity;
		static const size_t more_size = 10;
	public:
		dvec() : n(0) {
			capacity = n + more_size;
			data = new T[capacity];
		}
		dvec(size_t _n) : n(_n) {
			capacity = n + more_size;
			data = new T[n + capacity];
		}
		~dvec() {
			if (data != nullptr)
				delete[] data;
		}
		// 랜덤 접근 수정할때는 레퍼런스를 보내줘야함
		T& operator [] (size_t k) {
			// 반환형이 레퍼런스타입이므로 값을 읽지않고 주소가 반환됨
			return data[k];
		}
		// 그냥 값을 확인할때
		const T& operator [] (const size_t k) const {
			return data[k];
		}
		T& at(size_t index) {
			if (index < n)
				return data[index];
			throw "Index out of range";
		}
		size_t size() const {
			return n;
		}
		// for( const auto& item : list ) == for( auto it = list.begin(); it!=list.end(); it++ )
		// sort, remove_if는 이터레이터만 만들어져있으면 동작함
		// iterator에 레퍼런스가 아니라 포인터를 반환하는 이유는 
		// -> 포인터에는 + -로 자료형의 크기만큼 건너뛰면서 가리키는 기능이 있음
		T* begin() {
			return data;
		}
		T* end() {
			// data 첫주소에서 크기만큼 뒤로 가리킴
			return data + n;
		}
		const T* begin() const {
			return data;
		}
		const T* end() const {
			return data + n;
		}
		void resize(size_t k) {
			//새로운크기가 캡패시티 보다 커질때
			T* newData = nullptr;
			if (k > capacity) {
				capacity = k + more_size;
				newData = new T[capacity];
				for (size_t i = 0; i < n; i++)
					newData[i] = data[i];
				if (data) delete[] data;
				data = newData;
				n = k;
			}
			else {
				// 새로운크기가 캡패시티 보다 작을때 깊은복사를 하지 않고 뒷 원소를 삭제
				for (int i = k; i < n; i++) {
				}
				n = k;
			}
		}
		void push_back(const T& a) { // 상수가 입력되는데 메모리참조하고 변경하지 않기위해
			resize(n + 1);
			data[n - 1] = a; // 복사
		}
		bool erase(T* it) {
			// O(n) 딥카피
			if (it == end()) // ??remove_if에서 지울게 검색되지 않으면 마지막iter을 반환하는듯??
				return false;
			for (; it + 1 != end(); it++) {
				*it = *(it + 1);
			}
			resize(n - 1);
			return true;
		}
		bool erase(T* begin, T* end) {
			// 예정
		}
		void insert(const T* it, const T& a) {
			// 예정
		}
		void clear() {
			// 예정
		}
		bool empty() const {
			// 예정
			return false;
		}
	};

	// root, internal node, leaf node
	// degrees : number of children
	// level : distance from the root
	// depth of tree : level of the deepest leaf

	class dtree {
		class node {
			std::string position;
			dvec<node*> branches;
			friend class dtree;
		public:
			node(const std::string& pos) : position(pos) {}
		};
		node* root = nullptr;

		// static함수는 객체마다 가지고 있는것이 아니라 같은 클래스들끼리의 전역변수 같이 공용으로 사용되는것같다.
		// 재귀함수로 찾기위해서는 매개변수로 현재의 root를 받아와야하고 그렇게되면 find함수안에서 자기자신을 참조하지않아 this포인터도 사용하지 않아서
		// static 정적 함수로 선언할수있고 객체마다 함수를 가지고 있지 않아도 돼서 메모리를 오버헤드를 줄일수있다(?) 그리고 외부에는 pos만 받는 함수를 노출시켜
		// 사용편의성도 챙길수있다.
		static node* find(node* root, const std::string& pos) {
			if (root == nullptr)
				return nullptr;
			if (root->position.compare(pos) == 0)
				return root;
			//recursion trivial solution
			for (node* child : root->branches) {
				node* found = find(child, pos);
				if (found != nullptr) return found;
			}
			return nullptr;
		}
	public:
		dtree(const std::string& pos) {
			root = new node(pos);
		}
		node* find(const std::string& pos) {
			return find(root, pos);
		}
		bool addSub(const std::string& manager, const std::string& sub) {
			node* managerNode = find(manager);
			if (!managerNode) return false;
			managerNode->branches.push_back(new node(sub));
		}
	};
}
#endif // !dlib_hpp