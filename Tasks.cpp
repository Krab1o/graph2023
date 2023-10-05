#include "Tasks.h"

using std::string;
using std::getline;
using std::cin;
using std::cout;

void task1_14(Graph* graph)
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

void task2_9(Graph* graph)
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

void task3_10(Graph* graph1, Graph* graph2)
{
	auto list1 = graph1->getAdjacencyList();
	auto list2 = graph2->getAdjacencyList();

	map<string, map<string, int32_t>> newMap;
	for (auto it : list1)
		newMap[it.first];
	for (auto it : list2)
		newMap[it.first];

	Graph* newGraph = new Graph(newMap, graph1->getOrientation());

}