//
//  dlib.h
//  Build my data structures
//
//  Create by 임동예 on 2021/04/17.
//

//#pragma once
#ifndef dlib_hpp
#define dlib_hpp

#include <iostream>
#include <queue>
using namespace std;


// old method
#define MIN(X,Y) ((X)<(Y)?(X):(Y))
// you can use inline to
template <typename T>
__inline T min(T a, T b) {
	if (a < b) return a;
	return b;
}

namespace dtd
{
	// template class definition is must in hpp file
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
			~node() {}
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
		T pop_front() {
			T front_data = front->data;
			node<T>* next = front->next;
			delete front;
			front = next;
			return front_data;
		}
		const T& operator [] (const size_t n) const {
			return move_node(n)->data;
		}
		T& operator [] (const size_t n) {
			return move_node(n)->data;
		}
	};

	template <typename T>
	class dvec {
		T* data = nullptr;
		// size_t == unsigned int
		size_t n;
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
		T& operator [] (size_t k) {
			return data[k];
		}
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
		T* begin() {
			return data;
		}
		T* end() {
			return data + n;
		}
		const T* begin() const {
			return data;
		}
		const T* end() const {
			return data + n;
		}
		void resize(size_t k) {
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
				for (int i = k; i < n; i++) {
					data[i] = T();
				}
				n = k;
			}
		}
		void push_back(const T& a) {
			resize(n + 1);
			data[n - 1] = a;
		}
		bool erase(T* it) {
			if (it == end())
				return false;
			// O(N)
			for (; it + 1 != end(); it++) {
				*it = *(it + 1);
			}
			resize(n - 1);
			return true;
		}
		bool erase_with_remove_if(T* it) {
			// remove_if is finded ojb sort back and return leftest find obj 
			int en = end() - it; // how much erase obj, it can't use with find_if
			if (it == end())
				return false;
			resize(n - en);
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
	// subtree

	class dtree {
		class node {
			std::string position;
			dvec<node*> branches;
			friend class dtree;
		public:
			node(const std::string& pos) : position(pos) {}
			~node() {}
		};
		node* root = nullptr;

		// static함수는 객체마다 가지고 있는것이 아니라 같은 클래스들끼리의 전역변수 같이 공용으로 사용되는것같다.
		// 재귀함수로 찾기위해서는 매개변수로 현재의 root를 받아와야하고 그렇게되면 find함수안에서 자기자신을 참조하지않아 this포인터도 사용하지 않아서
		// static 정적 함수로 선언할수있고 객체마다 함수를 가지고 있지 않아도 돼서 메모리를 오버헤드를 줄일수있다(?) 그리고 외부에는 pos만 받는 함수를 노출시켜
		// 사용편의성도 챙길수있다.
		// 
		// * Pre-order traversal 부모먼저 검색 - 비교후 for
		// * Post-order traversal 자식먼저 검색 - for 후 비교
		// * Level order traversal 윗층부터 아래층으로 탐색 ( 큐 사용 )
		// * In-order traversal 우선순위가 왼쪽 부모 오른쪽 ( 내림차순으로 출력 )
		// 
		// 깊이 Depth : pre, post, in
		// 너비 Breath : level

		// * Pre-order traversal
		static node* find(node* r, const std::string& pos) {
			if (r == nullptr)
				return nullptr;
			if (r->position.compare(pos) == 0)
				return r;
			for (node* child : r->branches) {
				node* found = find(child, pos);
				if (found != nullptr) return found;
			}
			return nullptr;
		}
		// * post
		static void print(node* r) {
			for (node* child : r->branches)
				print(child);
			cout << r->position << endl;
		}
		// * level
		static node* print2(node* r) {
			if (!r) return nullptr;
			queue<node*> q; // stack 이라면?
			q.push(r);
			while (!q.empty()) {
				const node* n = q.front();
				q.pop();
				cout << n->position << " " << endl;
				for (node* branch : n->branches)
					q.push(branch);
			}
		}
		void print() {
			print(root);
		}
	public:
		dtree(const std::string& pos) {
			root = new node(pos);
		}
		node* find(const std::string& pos) {
			return find(root, pos);
		}
		bool addSub(const std::string& manager, const std::string& pos) {
			node* managerNode = find(manager);
			if (!managerNode) return false;
			managerNode->branches.push_back(new node(pos));
			return true;
		}
	};

	// Binary Tree ( N-ary Tree )
	// 빠른 탐색, 빠른 추가삭제
	// 왼쪽 자식은 작고 오른쪽자식은 크다
	class BST {
	public:
		class Node {
		public:
			int val;
			Node* left = nullptr;
			Node* right = nullptr;
			friend BST;
		};
	private:
		Node* root = nullptr;
		static Node* find_rec(Node* node, int key) {
			if (!node) return nullptr;
			if (key == node->val)
				return find_rec(node->left, key);
			else
				return find_rec(node->right, key);
		}
		// in-order
		template<typename Func> // 함수포인터, 람다 모두 사용가능
		static void vist_rec(Node* node, Func func) {

		}
		static Node* leftSuccessor(Node* node) {
			return node;
		}
		// remove할때 지우는공간을 successor(leaf)에서 복사하고 leaf는 지우기
		// 자식이 하나이면 부모한테 자식으로 바뀌었다고 알려줌
		// 지울공간이 leaf인경우 대체하지않고 부모의 dangling pointer을 처리하고 지움
		static Node* remove_rec(Node* node, int key) {
			if (!node)
				return nullptr;
			if (key < node->val)
				node->left = remove_rec(node->left, key);
			else if (key > node->val)
				node->right = remove_rec(node->right, key);
			else if (!node->left) {
				Node* ret = node->right;
				delete node;
				return ret;
			} else if (!node->right) {
				Node* ret = node->left;
				delete node;
				return ret;
			} else {
				Node* succNode = leftSuccessor(node->right);
				Node* left = node->left;
				Node* right = node->right;
				*node = *succNode;
				node->left = left;
				node->right = right;
				node->right = remove_rec(node->right, succNode->val);
			}
			return node;
		}
		public:
		void insert(int value) {
		}
		template<typename Func>
		void visit(Func func) {
		}
	};

}
#endif // !dlib_hpp