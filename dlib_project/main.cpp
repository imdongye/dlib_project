//
//  main.cpp
//  Build my data structures
//
//  Create by 임동예 on 2021/04/17.
//
#include "dlib.h"


int main() {
	dtd::Graph<int> graph;
	for (int i = 0; i < 8; i++)
		graph.addNode(i);

	graph.addEdges(0, { {1,1},{2,3} });
	graph.addEdges(1, { {2,7},{3,4},{5,1.2} });
	graph.addEdges(2, { {3,2} });
	graph.addEdges(3, { {4,3},{5,5},{6,4} });
	graph.addEdges(4, { {5,4},{7,5} });
	graph.addEdges(6, { {7,6} });

	//graph.DFS(0, [](int, const int& t) {std::cout << t << ' '; return false; });
	//std::cout << "\n\n";
	//graph.MST();
	dtd::dvec<int> path = graph.Dijkstra(0, 4);
	if (path == dtd::dvec<int>())
		std::cout << "실패";
	else
		for (int i = 0; i < path.size(); i++)
			std::cout << path[i] << std::endl;

	return 0;
}