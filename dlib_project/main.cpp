//
//  main.cpp
//  Build my data structures
//
//  Create by ÀÓµ¿¿¹ on 2021/04/17.
//
#include "dlib.h"
using namespace std;


int main() {
	dtd::Graph<int> graph;
	graph.addNode(0);
	graph.addNode(1);
	graph.addNode(2);
	graph.addNode(3);
	graph.addNode(4);
	graph.addNode(5);
	graph.addNode(6);
	graph.addNode(7);
	graph.addNode(8);

	graph.addEdges(0, { {1,1},{2,3} });
	graph.addEdges(1, { {2,7},{3,4},{5,1.2} });
	graph.addEdges(2, { {3,2} });
	graph.addEdges(3, { {4,3},{5,5},{6,4} });
	graph.addEdges(4, { {5,4},{7,5} });
	graph.addEdges(6, { {7,6} });

	//graph.DFS(0, [](int, const int& t) {std::cout << t << ' '; return false; });
	graph.MST();
	
	return 0;
}