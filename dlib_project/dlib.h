#pragma once

#include<functional>
#include <iostream>
#include <string>

#include <queue>
#include <stack>
#include <vector>

// old method
#define MIN(X,Y) ((X)<(Y)?(X):(Y))
// you can use inline to
template <typename T>
__inline T min(T a, T b) {
	if (a < b) return a;
	return b;
}

// template class definition is must in hpp file
namespace dtd
{
	// <�ܹ��� ��ũ�� ����Ʈ>
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

	// <�������� �迭>
	template <typename T>
	class dvec {
		friend class dvec;
		size_t n = 0;
		size_t capacity = 0;
		T* data = nullptr;
	public:
		dvec() {
			recapacity(21);
		}
		dvec(size_t _n) {
			resize(_n);
		}
		dvec(size_t _n, T init) {
			resize(_n);
			for (int i = 0; i < n; i++)
				data[i] = init;
		}
		// ���������
		dvec(const dvec<T>& p) {
			if (p.data == nullptr)
				return;
			recapacity(p.capacity);
			n = p.n;
			for (auto i = 0; i < n; i++)
				data[i] = p.data[i];
		}
		// data[i] = init;�� ���
		dvec& operator = (const dvec<T>& p) {
			//this->dvec(p); �־ȵ�?
			if (p.data == nullptr)
				return *this;
			recapacity(p.capacity);
			n = p.n;
			for (auto i = 0; i < n; i++)
				data[i] = p.data[i];
			return *this;
		}
		virtual ~dvec() {
			if (data != nullptr) {
				delete[] data;
				data = nullptr;
			}
		}
		friend bool operator == (const dvec<T>& a, const dvec<T>& b) {
			if (a.size() != b.size())
				return false;
			for (int i = 0; i < a.size(); i++) {
				if (a[i] != b[i])
					return false;
			}
			return true;
		}
		T& operator [] (size_t k) {
			if (k < n)
				return data[k];
			throw "Index out of range";
		}
		const T& operator [] (const size_t k) const {
			if (k < n)
				return data[k];
			throw "Index out of range";
		}
		T& at(size_t k) {
			if (k < n)
				return data[k];
			throw "Index out of range";
		}
		size_t size() const {
			return n;
		}
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
		T front() const {
			return this[0];
		}
		void recapacity(size_t k = capacity) {
			capacity = k;
			// 0������� �����Ҵ��ϸ� �ȵ�.
			if (k < 1) {
				if (data != nullptr)
					delete[] data;
				return;
			}
			T* newData = new T[capacity];
			for (auto i = 0; i < n; i++)
				newData[i] = data[i];
			if (data != nullptr)
				delete[] data;
			data = newData;
		}
		void resize(size_t k, T init = T()) {
			if (k > capacity) {
				recapacity(2 * k);
			}
			for (size_t i = n; i < k; i++) {
				data[i] = init;
			}
			n = k;
		}
		void pop_front() const { // O(n)
			this.erase(this.begin());
			resize(n - 1);
		}
		void push_back(const T& a) {
			resize(n + 1);
			data[n - 1] = a;
		}
		bool erase(T* it) {
			if (it == end())
				return false;
			// O(N)
			for (; it + 1 != end(); it++)
				*it = *(it + 1);
			resize(n - 1);
			return true;
		}
		bool erase_with_remove_if(T* it) {
			// remove_if�� �˻��� ��Ҹ� ���������� �����ϰ�
			// ���� ���� ���� ���ͷ����͸� ��ȯ
			int en = end() - it;
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

	// <Ʈ��>
	class dtree {
		/*
		��� ���� : root, internal node, leaf node
		degrees : �ڽ��� ����
		level : root������ �Ÿ�
		depth of tree : ���� �ָ��ִ� leef node�� level

		static�Լ��� ��ü���� ������ �ִ°��� �ƴ϶� ���� Ŭ�����鳢���� �������� ���� �������� ���Ǵ°Ͱ���.
		����Լ��� ã�����ؼ��� �Ű������� ������ root�� �޾ƿ;��ϰ� �׷��ԵǸ� find�Լ��ȿ��� �ڱ��ڽ��� ���������ʾ� this�����͵� ������� �ʾƼ�
		static ���� �Լ��� �����Ҽ��ְ� ��ü���� �Լ��� ������ ���� �ʾƵ� �ż� �޸𸮸� ������带 ���ϼ��ִ�(? ) �׸��� �ܺο��� pos�� �޴� �Լ��� �������
		������Ǽ��� ì����ִ�.

		* Pre - order traversal �θ���� �˻� - ���� for
		* Post - order traversal �ڽĸ��� �˻� - for �� ��
		* In - order traversal �켱������ ���� �θ� ������(������������ ���)
		* Level order traversal �������� �Ʒ������� Ž��(ť ���)

		���� Depth : pre, post, in
		�ʺ� Breath : level
		*/
	private:
		class Node {
			std::string position;
			dvec<Node*> branches;
			friend class dtree;
		public:
			Node(const std::string& pos) : position(pos) {}
			~Node() {}
		};
		Node* root = nullptr;

		// * Pre-order traversal
		static Node* find(Node* r, const std::string& pos) {
			if (r == nullptr)
				return nullptr;
			if (r->position.compare(pos) == 0)
				return r;
			for (Node* child : r->branches) {
				Node* found = find(child, pos);
				if (found != nullptr) return found;
			}
			return nullptr;
		}
		// * post
		static void print(Node* r) {
			for (Node* child : r->branches)
				print(child);
			std::cout << r->position << std::endl;
		}
	public:
		dtree(const std::string& pos) {
			root = new Node(pos);
		}
		void print() {
			print(root);
		}
		// * level
		void printLevelOrder() {
			std::queue<Node*> q; // stack �̶��???
			q.push(root);
			while (!q.empty()) {
				const Node* n = q.front();
				q.pop();
				std::cout << n->position << " " << std::endl;
				for (Node* branch : n->branches)
					q.push(branch);
			}
		}
		Node* find(const std::string& pos) {
			return find(root, pos);
		}
		bool addSub(const std::string& manager, const std::string& pos) {
			Node* managerNode = find(manager);
			if (!managerNode) return false;
			managerNode->branches.push_back(new Node(pos));
			return true;
		}
	};

	// <���� Ʈ��>
	template<typename T>
	class BST {
		// Binary Tree ( N-ary Tree )
		// fast search, fast add delete
		// left is small, right is big
	private:
		template<typename T>
		class Node {
		private:
			T val;
			Node<T>* left = nullptr;
			Node<T>* right = nullptr;
			friend BST;
		public:
			Node(const T& _val = T(), Node<T>* _left = nullptr, Node<T>* _right = nullptr)
				: val(_val), left(_left), right(_right) {}

		};
		Node<T>* root = nullptr;
	private:
		// pre-order logn
		static Node<T>* find_rec(Node<T>* node, const T& key) {
			if (node == nullptr)
				return nullptr;
			if (key == node->val)
				return node;
			if (key < node->val)
				return find_rec(node->left, key);
			else
				return find_rec(node->right, key);
		}
		// in-order (left middle right) sort effect
		// template<typename Func> => use func pointer and ramda fuction
		// new version => function<void(const T&)>
		static void visit_rec(Node<T>* node, std::function<void(const T&)> func) {
			if (node == nullptr)
				return;
			if (node->left)
				visit_rec(node->left, func);
			func(node->val);
			if (node->right)
				visit_rec(node->right, func);
		}
		// right subtree of leftest leaf
		static Node<T>* leftSuccessor(Node<T>* start) {
			if (start->left)
				return leftSuccessor(start->left);
			else
				return start;
		}
		// left subtree of rightest leaf
		static Node<T>* rightSuccessor(Node<T>* start) {
			if (start->right)
				return rightSuccessor(start->right);
			else
				return start;
		}
		// recursive
		static Node<T>* remove_rec(Node<T>* node, const T& key) {
			if (!node)
				return nullptr;
			if (node->val > key)
				node->left = remove_rec(node->left, key); // -- 1
			else if (node->val < key)
				node->right = remove_rec(node->right, key); // -- 2
			else if (node->left == nullptr) { // both is null return null so it doesn't matter
				Node<T>* ret = node->right;
				if (node)
					delete node;
				return ret;
			}
			else if (node->right == nullptr) {
				Node<T>* ret = node->left;
				if (node)
					delete node;
				return ret;
			}
			else { // match key and left, right is contain
				Node<T>* successorNode = leftSuccessor(node->right);
				node->val = successorNode->val;
				node->right = remove_rec(node->right, successorNode->val);
			}
			return node; // -- 1, 2 �״�� �����ϱ� ����
		}
		// Node*& is show **effect
		static void insert_ref(Node<T>*& node, const T& val) {
			if (node == nullptr) {
				node = new Node<T>(val);
				return;
			}
			if (node->val < val) {
				insert_ref(node->right, val);
			}
			else {
				insert_ref(node->left, val);
			}
		}
	public:
		// O(log n)
		T find(const T& key) {
			Node<T>* found = find_rec(root, key);
			if (found) return found->val;
			else return T();
		}
		// O(Depth) -> O(log n)
		bool insert(T val) {
			if (!root)
				root = new Node<T>(val);
			else if (find(val) == T())
				insert_ref(root, val);
			else // has same val
				return false;
			return true;
		}
		//  O(log n)
		void remove(T key) {
			root = remove_rec(root, key);
		}
		// O(N)???
		void visit(std::function<void(const T&)> func) {
			visit_rec(root, func);
		}
	};
	template<typename T>
	class Heap {

	};

	// <���� Ž��>
	template<typename IT, typename T>
	IT search(const T& val, IT first, IT last) {
		if (first == last) return last;
		IT center = first;
		advance(center, floor(distance(first, last) / 2));
		if (*center == val) return center;
		else if (*center > val) {
			IT found = serch(val, first, center);
			if (found == center) return last;
			else return found;
		}
		else
			return search(val, ++center, last);
	};
	// <���� ����>
	template<typename T>
	dvec<T>merge(const dvec<T>& a, const dvec<T>& b) {
		dvec<T> merged;
		T* it1 = a.begin();
		T* it2 = b.begin();
		while (it1 != a.end() || it2 != b.end()) {
			if (it1 != a.end() && (it2 == b.end || *it1 < *(it2)))
				merged.push_back(*it1++);
			else
				merged.push_back(*it2++);
		}
		return merged;
	};
	// ��ͻ������ �ʰ� Joma ??
	template<typename T>
	dvec<T> merge_sort(const dvec<T>& I) {
		if (I.size() < 2) return I;
		T* center = I.begin();
		advance(center, floor(distance(I.begin(), I.end()) / 2));

		// ���α׷� ������ ������Ȳ�� �����
		T* left = merge_sort(dvec<T>(I.begin(), center));
		T* right = merge_sort(dvec<T>(center, I.end()));

		return merge(left, right);
	};

	template<typename T1, typename T2>
	class pair {
	public:
		T1 first;
		T2 second;
		pair() {
		}
		pair(T1 f, T2 s) :first{ f }, second{ s } {}
	};
	// <�׷���>
	template<typename T>
	class Graph {
		dvec<T> nodes;
		// **non-weight
		// adjacency list
		//dvec<dvec<int>> adjList;
		// adjacency matrix
		//bool adjMat[100][100];
		// **weight

		dvec<dvec<pair<int, float>>> adjList;
		//float adjMat[100][100];
	public:
		void addNode(const T& v) {
			nodes.push_back(v);
			adjList.resize(nodes.size());
		}
		void addEdge(int from, int to, float w) {
			adjList[from].push_back(pair(to, w));
			//both side pointer
			adjList[to].push_back(pair(from, w));
		}
		void addEdges(int from, const std::vector<std::pair<int, float>>& to_s) {
			for (auto to : to_s)
				addEdge(from, to.first, to.second);
		}
		// O(N) breath first search traversal
		void BFS(int start, std::function<bool(int, const T&)> func) {
			dvec<bool> closed(nodes.size(), false);
			std::deque<int> open;
			open.push_back(start);
			while (!open.empty()) {
				int theNode = open.front();
				open.pop_front();
				closed[theNode] = true;
				if (func(theNode, nodes[theNode]) == true)
					break;
				for (std::pair<int, float> e : adjList[theNode]) {
					int dst = e.first;
					float w = e.second;
					if (!closed[dst] &&
						std::find(open.begin(), open.end(), dst) == open.end())
						open.push_back(dst);
				}
			}
		}
		// ���� �켱 Ž�� depth first traversal ??? ��ͷ�
		void DFS(int start, std::function<bool(int, const T&)> func) {
			dvec<bool> closed(nodes.size(), false);
			std::deque<int> open;
			open.push_front(start);
			while (!open.empty()) {
				int theNode = open.front();
				open.pop_front();
				closed[theNode] = true;
				if (func(theNode, nodes[theNode]) == true)
					break;
				for (std::pair<int, float> e : adjList[theNode]) {
					int dst = e.first;
					float w = e.second;
					if (!closed[dst] &&
						std::find(open.begin(), open.end(), dst) == open.end())
						open.push_front(dst);
				}
			}
		}
		// weighted graph
		// �ּ� ��� ���� ����
		// ����Ŭ�� ���� = Ʈ��
		// spanning�Ѵ�

		// Prim's Algorithm Ʈ�������� �Ÿ�
		// ���ͽ�Ʈ�� ������� ������������ �Ÿ�
		// val: ���ݱ��� �˷����ִ� Ʈ������ �Ÿ�. �ʱⰪ:����. ���۳��:0
		// Min Spanning Tree
	private:
		struct MST_NodeInfo {
			int node;
			float dist;
		};
		struct MST_NodeCompare {
			bool operator() (const MST_NodeInfo& a, const MST_NodeInfo& b) {
				return a.dist > b.dist;
			}
		};
	public:
		//Prim��s Algorithm
		void MST() {
			// flag ��ü�� ���
			dvec<bool> visited(nodes.size(), false);
			dvec<float> distance(nodes.size(), 1E20);
			dvec<int> parent(nodes.size(), -1);
			std::priority_queue<MST_NodeInfo, std::vector<MST_NodeInfo>, MST_NodeCompare> queue;

			int s = 0;
			distance[s] = 0;
			queue.push({ s,0 });
			int counter = 0; // �� 0 �� �ȵǴ� ��
			while (counter < nodes.size()) {
				auto [theNode, w] = queue.top(); // c++17 decomposition ??? auto �� �ڷ�����?
				queue.pop();
				if (visited[theNode] == false) {
					counter++;
					visited[theNode] = true;
					std::cout << parent[theNode] << "->" << theNode << std::endl;
					for (auto [dst, edgeDist] : adjList[theNode]) {
						if (distance[dst] > edgeDist) {
							distance[dst] = edgeDist;
							parent[dst] = theNode;
							queue.push({ dst,distance[dst] });
						}
					}
				}
			}
		}
		//gridy
		//���ͽ�Ʈ��� counter ���ƴ� queue�� empty �϶� destination node ����������
		dvec<T> Dijkstra(int start, int end) {
			dvec<bool> visited(nodes.size(), false);
			dvec<float> sDist(nodes.size(), 1E20);
			dvec<int> parent(nodes.size(), -1);
			std::priority_queue<MST_NodeInfo, std::vector<MST_NodeInfo>, MST_NodeCompare> queue;

			dvec<T> result;
			sDist[start] = 0;
			queue.push({ start,0 });
			while (queue.empty() == false) {
				auto [cur, w] = queue.top();
				queue.pop();
				if (visited[cur] == false) {
					visited[cur] = true;
					if (cur == end) {// ����
						int c = end;
						while (c != -1) {
							result.push_back(nodes[c]);
							c = parent[c];
						}
						std::reverse(result.begin(), result.end());
						return  result;
					}
					for (auto [dst, edgeDist] : adjList[cur]) {
						// ���������� �Ÿ�
						float compDist = sDist[cur] + edgeDist;
						if (sDist[dst] > compDist) {
							sDist[dst] = compDist;
							parent[dst] = cur;
							queue.push({ dst, sDist[dst] });
						}
					}
				}
			}
			// ����
			return result;
		}
	};
	// �� �����ڷ� �ٽú���
	// �ؽ����̺�
	// �������
	// Ǫ���� ��ȯ
	// �ε��Ҽ��� �� ���� ���

	// hashtable load factor
	// hash�� ��ġ�� chaining, open addressing(linear probing)

	/* Todo:
	*	c++ array initialization
	*	c++ struct initialization
	*	���� ť ����
	*	Ʈ��, �׷���, ����, �ð����⵵
	*/
}
