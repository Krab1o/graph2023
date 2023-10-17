#include "Tasks.h"
#include "App.h"

using std::string;
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

void dfs(map<string, map<string, int32_t>>& list, const string& vertice, map<string, bool>& used)
{	
	used[vertice] = true;
	for (auto it : list[vertice])
	{
		if (!used[it.first])
		{
			dfs(list, it.first, used);
		}
	}
}

void dfs_modified(
	map<string, map<string, int32_t>>& list,
	const string& current, 
	const string& end, 
	map<string, bool>& used,
	vector<string>& path,
	int32_t& counter)
{
	if (current == end)
	{
		for (auto it = path.begin(); it != path.end(); it++)
		{
			std::cout << *it << "->";
		}
		++counter;
		std::cout << end << '\n';
		return;
	}
		
	used[current] = true;
	for (auto it : list[current])
	{
		if (!used[it.first])
		{
			path.push_back(current);
			dfs_modified(list, it.first, end, used, path, counter);
			path.pop_back();
		}
	}
	used[current] = false;
}

void bfs(map<string, map<string, int32_t>>& list, const string& vertice, map<string, bool>& used)
{
	string cur;
	std::queue<string> q;
	used[vertice] = true;
	q.push(vertice);
	while (!q.empty())
	{
		cur = q.front();
		q.pop();
		for (auto it : list[cur])
		{
			if (!used[it.first])
			{
				used[it.first] = true;
				q.push(it.first);
			}
		}
	}
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

Graph* prim(Graph* graph, string root = "")
{
	Graph* tree = new Graph(graph->getOrientation());
	auto list = graph->getAdjacencyList();

	map<string, bool> used;
	map<string, int> minEdge;
	map<string, string> prevEdge;
	for (auto it : list)
	{
		used[it.first] = false;
		minEdge[it.first] = INT32_MAX;
		prevEdge[it.first] = "";
	}
	if (root == "")
	{
		minEdge[list.begin()->first] = 0;
		tree->AddVertice(list.begin()->first);
	}
	else
	{
		minEdge[root] = 0;
		tree->AddVertice(root);
	}
	
	for (auto it : list)
	{
		string v = "";
		for (auto minVert : list)
		{
			if (!used[minVert.first] && (v == "" || minEdge[minVert.first] < minEdge[v]))
				v = minVert.first;
		}
		if (v == "")
		{
			//no MST
			std::cout << "No MST\n";
			return new Graph();
		}

		used[v] = true;
		if (prevEdge[v] != "")
		{
			auto treeList = tree->getAdjacencyList();
			tree->AddVertice(v);
			tree->AddEdge(v, prevEdge[v], list[v][prevEdge[v]]);
			std::cout << v << ' ' << prevEdge[v] << '\n';
		}

		for (auto vert : list[v])
			if (vert.second < minEdge[vert.first])
			{
				minEdge[vert.first] = vert.second;
				prevEdge[vert.first] = v;
			}
	}
	return tree;
}

Graph* task7_prim(Graph* graph)
{
	return prim(graph, "D");
}

