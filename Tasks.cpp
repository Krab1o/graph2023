#include<algorithm>

#include "Tasks.h"
#include "App.h"
#include "algos.h"

using std::string;
using std::set;
using std::getline;
using std::cin;
using std::cout;

//just prints adjacent vertices
void task2_14(Graph* graph)
{
	string vertice;
	std::cout << "Enter vertice to print: ";
	getline(cin, vertice);

	auto list = graph->getAdjacencyList();
	auto map = list[vertice];
	if (map.empty())
	{
		std::cout << "No adjacent vertices!\n";
	}
	else
	{
		std::cout << vertice << ": ";
		for (auto& el : map)
		{
			std::cout << "(" << el.first << ", " << el.second << ") ";
		}
		std::cout << '\n';
	}
}

//oriented graphs: only vertices which are reachable from current
void task3_9(Graph* graph)
{
	string vertice;
	std::cout << "Enter vertice: ";
	getline(cin, vertice);

	auto list = graph->getAdjacencyList();
	if (list.find(vertice) == list.end())
	{
		std::cout << "No such vertice in graph\n";
		return;
	}
	auto mapTarget = list[vertice];
	uint16_t counter = 0;
	{
		for (auto el : list)
		{
			if (el.second.size() > mapTarget.size())
			{
				std::cout << el.first << ' ';
				++counter;
			}
		}
		if (!counter)
			std::cout << "No such vertices!";
		std::cout << '\n';
	}
}

void task4_10(Graph* graph1, Graph* graph2)
{
	if (graph1->getOrientation() != graph2->getOrientation())
	{
		std::cout << "Graphs are incompatible\n";
		return;
	}

	auto list1 = graph1->getAdjacencyList();
	auto list2 = graph2->getAdjacencyList();

	map<string, map<string, int32_t>> newMap;
	for (auto it : list1)
		newMap[it.first];
	for (auto it : list2)
		newMap[it.first];

	for (auto it1 : newMap)
	{
		for (auto it2 : newMap)
		{
			auto f1 = list1[it1.first].find(it2.first);
			auto f2 = list2[it1.first].find(it2.first);

			if (f1 != list1[it1.first].end() && f2 == list2[it1.first].end())
			{
				newMap[it1.first][it2.first] = list1[it1.first][it2.first];
			}
			else if (f1 == list1[it1.first].end() && f2 != list2[it1.first].end())
			{
				newMap[it1.first][it2.first] = list2[it1.first][it2.first];
			}

		}
	}
	Graph* newGraph = new Graph(newMap, graph1->getOrientation());
	PrintVertices(newGraph);
}

void task5_2(Graph* graph)
{
	string vertice;
	std::cout << "Enter target vertice: ";
	getline(cin, vertice);
	map<string, bool> used;
	auto list = graph->getAdjacencyList();
	for (auto it : list)
	{
		used[it.first] = false;
	}
	bfs(list, vertice, used);
	for (auto it : used)
	{
		if (!used[it.first])
			std::cout << it.first << ' ';
	}
	std::cout << '\n';
}


void task6_20(Graph* graph)
{
	string startVertice;
	string endVertice;
	auto list = graph->getAdjacencyList();
	std::cout << "Enter start vertice: ";
	getline(cin, startVertice);
	std::cout << "Enter end vertice: ";
	getline(cin, endVertice);
	if (list.find(startVertice) == list.end())
	{
		std::cout << "No vertice 1 represented in graph\n";
		return;
	}
	if (list.find(endVertice) == list.end())
	{
		std::cout << "No vertice 2 represented in graph\n";
		return;
	}
	map<string, bool> used;
	vector<string> path;
	int32_t ans = 0;

	for (auto it : list)
	{
		used[it.first] = false;
	}
	dfs_modified(list, startVertice, endVertice, used, path, ans);
	if (!ans)
		std::cout << "No paths between these 2 vertices!\n";
}

Graph* task7_prim(Graph* graph)
{
	return prim(graph, "D");
}

void task8_11(Graph* graph)
{
	map<string, map<string, int32_t>> minimalDistance;
	auto list = graph->getAdjacencyList();
	for (auto vert : list)
	{
		minimalDistance[vert.first] = dijkstra(graph, vert.first);
	}
	map<string, int32_t> eccentricity;
	int32_t radius = INT32_MAX;
	for (auto vert : minimalDistance)
	{
		eccentricity[vert.first] = std::max_element(vert.second.begin(), vert.second.end(), 
			[&](const auto p1, const auto p2) {return p1.second < p2.second; })->second;
		radius = std::min(eccentricity[vert.first], radius);
	}
	
	if (radius == INT32_MAX)
	{
		std::cout << "No center vertice in graph (graph is not connected)\n";
		return;
	}

	for (auto vert : eccentricity)
	{
		if (vert.second == radius)
			std::cout << vert.first << ' ';
	}
	cout << '\n';
	return;
}

void task9_17(Graph* graph)
{
	auto floydRes = floyd(graph);
	map<string, map<string, int32_t>> minimalDistance = floydRes.first;
	map<string, map<string, string>> pathVertices = floydRes.second;

	auto list = graph->getAdjacencyList();
	std::stack<string> path;
	for (auto vert1 : list)
	{
		for (auto vert2 : list)
		{
			cout << vert1.first << "->" << vert2.first << ": ";
			if (minimalDistance[vert1.first][vert2.first] == INT32_MAX)
			{
				cout << "No path between these vertices\n";
			}
			else
			{
				WayBack(vert1.first, vert2.first, path, pathVertices);
				cout << path.top();
				path.pop();
				while (!path.empty())
				{
					cout << "->" << path.top();
					path.pop();
				}
				cout << " (" << minimalDistance[vert1.first][vert2.first] << ")" << '\n';
			}
		}
		cout << '\n';
	}
}

