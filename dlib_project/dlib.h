//
//  dlib.h
//  Build my data structures
//
//  Create by �ӵ��� on 2021/04/17.
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
			// ����
		}
		void insert(const T* it, const T& a) {
			// ����
		}
		void clear() {
			// ����
		}
		bool empty() const {
			// ����
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

		// static�Լ��� ��ü���� ������ �ִ°��� �ƴ϶� ���� Ŭ�����鳢���� �������� ���� �������� ���Ǵ°Ͱ���.
		// ����Լ��� ã�����ؼ��� �Ű������� ������ root�� �޾ƿ;��ϰ� �׷��ԵǸ� find�Լ��ȿ��� �ڱ��ڽ��� ���������ʾ� this�����͵� ������� �ʾƼ�
		// static ���� �Լ��� �����Ҽ��ְ� ��ü���� �Լ��� ������ ���� �ʾƵ� �ż� �޸𸮸� ������带 ���ϼ��ִ�(?) �׸��� �ܺο��� pos�� �޴� �Լ��� �������
		// ������Ǽ��� ì����ִ�.
		// 
		// * Pre-order traversal �θ���� �˻� - ���� for
		// * Post-order traversal �ڽĸ��� �˻� - for �� ��
		// * Level order traversal �������� �Ʒ������� Ž�� ( ť ��� )
		// * In-order traversal �켱������ ���� �θ� ������ ( ������������ ��� )
		// 
		// ���� Depth : pre, post, in
		// �ʺ� Breath : level

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
			queue<node*> q; // stack �̶��?
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
	// ���� Ž��, ���� �߰�����
	// ���� �ڽ��� �۰� �������ڽ��� ũ��
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
		template<typename Func> // �Լ�������, ���� ��� ��밡��
		static void vist_rec(Node* node, Func func) {

		}
		static Node* leftSuccessor(Node* node) {
			return node;
		}
		// remove�Ҷ� ����°����� successor(leaf)���� �����ϰ� leaf�� �����
		// �ڽ��� �ϳ��̸� �θ����� �ڽ����� �ٲ���ٰ� �˷���
		// ��������� leaf�ΰ�� ��ü�����ʰ� �θ��� dangling pointer�� ó���ϰ� ����
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