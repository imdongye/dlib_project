//
//  dlib.h
//  Build my data structures
//
//  Create by 임동예 on 2021/04/17.
//
//#pragma once
#ifndef dlib_hpp
#define dlib_hpp

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
	// <단방향 링크드 리스트>
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

	// <가변길이 배열>
	template <typename T>
	class dvec {
		T* data = nullptr;
		// size_t == unsigned int
		T init;
		size_t n;
		size_t capacity;
		static const size_t SPARE_SIZE = 10;
	public:
		dvec() : n(0), init(T()) {
			capacity = n + SPARE_SIZE;
			data = new T[capacity];
		}
		dvec(size_t _n) : n(_n) {
			capacity = n + SPARE_SIZE;
			data = new T[capacity];
		}
		dvec(size_t _n, T _init) : n(_n), init(_init) {
			capacity = n + SPARE_SIZE;
			data = new T[capacity];
			for (int i = 0; i < capacity; i++)
				data[i] = init;
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
		T front() const {
			return data[0];
		}
		void pop_front() const{
			this.erase(this.begin());
			this.resize(this.size() - 1);
		}
		void resize(size_t k) {
			T* newData = nullptr;
			if (k > capacity) {
				capacity = k + SPARE_SIZE;
				newData = new T[capacity];
				for (size_t i = 0; i < capacity; i++) {
					if (i < n)
						newData[i] = data[i];
					else
						newData[i] = init;
				}
					
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

	// <트리>
	class dtree {
		/*
		노드 종류 : root, internal node, leaf node
		degrees : 자식의 개수
		level : root까지의 거리
		depth of tree : 가장 멀리있는 leef node의 level

		static함수는 객체마다 가지고 있는것이 아니라 같은 클래스들끼리의 전역변수 같이 공용으로 사용되는것같다.
		재귀함수로 찾기위해서는 매개변수로 현재의 root를 받아와야하고 그렇게되면 find함수안에서 자기자신을 참조하지않아 this포인터도 사용하지 않아서
		static 정적 함수로 선언할수있고 객체마다 함수를 가지고 있지 않아도 돼서 메모리를 오버헤드를 줄일수있다(? ) 그리고 외부에는 pos만 받는 함수를 노출시켜
		사용편의성도 챙길수있다.

		* Pre - order traversal 부모먼저 검색 - 비교후 for
		* Post - order traversal 자식먼저 검색 - for 후 비교
		* In - order traversal 우선순위가 왼쪽 부모 오른쪽(내림차순으로 출력)
		* Level order traversal 윗층부터 아래층으로 탐색(큐 사용)

		깊이 Depth : pre, post, in
		너비 Breath : level
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
			std::queue<Node*> q; // stack 이라면???
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

	// <이진 트리>
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
				delete node;
				return ret;
			}
			else if (node->right == nullptr) {
				Node<T>* ret = node->left;
				delete node;
				return ret;
			}
			else { // match key and left, right is contain
				Node<T>* successorNode = leftSuccessor(node->right);
				node->val = successorNode->val;
				node->right = remove_rec(node->right, successorNode->val);
			}
			return node; // -- 1, 2 그대로 대입하기 위해
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

	// <이진 탐색>
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
	// <병합 정렬>
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
	// 재귀상용하지 않고 Joma ??
	template<typename T>
	dvec<T> merge_sort(const dvec<T>& I) {
		if (I.size() < 2) return I;
		T* center = I.begin();
		advance(center, floor(distance(I.begin(), I.end()) / 2));

		// 프로그램 스택이 이전상황을 기억함
		T* left = merge_sort(dvec<T>(I.begin(), center));
		T* right = merge_sort(dvec<T>(center, I.end()));

		return merge(left, right);
	};

	// <그래프>
	template<typename T>
	class Graph {
		dvec<T> nodes;
		// **non-weight
		// adjacency list
		//dvec<dvec<int>> adjList;
		// adjacency matrix
		//bool adjMat[100][100];
		// **weight 
		dvec<dvec<std::pair<int, float>>> adjList;
		//float adjMat[100][100];
	public:
		void addNode(const T& v) {
			nodes.push_back(v);
			adjList.resize(nodes.size());
		}
		void addEdge(int from, int to, float w) {
			adjList[from].push_back({ to,w });
			//both side pointer
			adjList[to].push_back({ from,w });
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
		// 깊이 우선 탐색 depth first traversal ??? 재귀로
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
		// 최소 비용 연결 문제
		// 사이클이 없음 = 트리
		// spanning한다

		// Prim's Algorithm 트리에서의 거리
		// 다익스트라 경로저장 시작점에서의 거리
		// val: 지금까지 알려져있는 트리까지 거리. 초기값:무한. 시작노드:0
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
		//Prim’s Algorithm
		void MST() {
			// flag 우체통 깃발
			dvec<bool> visited(nodes.size(), false);
			dvec<float> distance(nodes.size(), 1E20);
			dvec<int> parent(nodes.size(), -1);
			std::priority_queue<MST_NodeInfo, std::vector<MST_NodeInfo>, MST_NodeCompare> queue;

			int s = 0;
			distance[s] = 0;
			queue.push({ s,0 });
			int counter = 1;
			while (counter < nodes.size()) {
				auto [theNode, w] = queue.top(); // c++17 decomposition ??? auto 의 자료형은?
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
		//다익스트라는 counter 가아닌 queue가 empty 일때 destination node 도착했을때
		dvec<T> Dijkstra(int start, int end) {
			dvec<bool> visited(nodes.size(), false);
			dvec<float> sDist(nodes.size(), 1E20);
			dvec<int> parent(nodes.size(), -1);
			std::priority_queue<MST_NodeInfo, std::vector<MST_NodeInfo>, MST_NodeCompare> queue;

			queue.push({ start,0 });
			while (queue.empty()) {
				auto [cur, w] = queue.top();
				queue.pop();
				if (visited[cur] == false) {
					visited[cur] = true;
					if (cur == end) {// 성공
						dvec<T> v;
						int c = end;
						v.push_back(nodes[c]);
						while (c != start) {
							c = parent[c];
							v.push_back(nodes[c]);
						}
						std::reverse(v.begin(), v.end());
						return v;
					}
					for (auto [dst, edgeDist] : adjList[cur]) {
						// 시작점에서 거리
						float compDist = sDist[cur] + edgeDist;
						if (sDist[dst] > compDist) {
							sDist[dst] = compDist;
							parent[dst] = cur;
							queue.push({ dst,sDist[dst] });
						}
					}
				}
			}
			// 실패
			return dvec<T>();
		}
	};
	// 힙 강의자료 다시보기
	// 해시테이블
	// 블룸필터
	// 푸리에 변환
	// 부동소수점 비교 문제 용어

	// hashtable load factor
	// hash값 겹치면 chaining, open addressing(linear probing)
}



#endif // !dlib_hpp

/* Todo:
*	c++ array initialization
*	c++ struct initialization
*	스택 큐 구현
*	트리, 그래프, 정렬, 시간복잡도
*/