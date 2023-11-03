#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Graph.h"
#include "App.h"
#include "Tasks.h"

using std::cin;
using std::getline;
const string DATA_FILE1 = "task11_1.json";
const string DATA_FILE2 = "data4.json";

int main()
{
	string command;

	Graph* graph;
	std::ifstream file(DATA_FILE1);
	if (file.is_open())
		graph = new Graph(file);
	else
		graph = CreateGraph(command);
	file.close();

	file.open(DATA_FILE2);
	Graph* graph2 = new Graph(file);
	file.close();

	CommandMessage();
	while (true)
	{
		std::cout << "Command: ";
		getline(cin, command);
		switch (Hashing(command))
		{
		case string_code::printVertices:
			PrintVertices(graph);
			break;
		case string_code::addVertice:
			AddVertice(graph);
			break;
		case string_code::removeVertice:
			RemoveVertice(graph);
			break;
		case string_code::addEdge:
			AddEdge(graph);
			break;
		case string_code::removeEdge:
			RemoveEdge(graph);
			break;
		case string_code::changeWeight:
			ChangeWeight(graph);
			break;
		case string_code::unweightGraph:
			Unweight(graph);
			break;

		case string_code::saveGraph:
			graph->Save(DATA_FILE1);
			std::cout << "Graph saved succesfully\n";
			break;


		case string_code::task2:
			task2_14(graph);
			break;
		case string_code::task3:
			task3_9(graph);
			break;
		case string_code::task4:
			task4_10(graph, graph2);
			break;
		case string_code::task5:
			task5_2(graph);
			break;
		case string_code::task6:
			task6_20(graph);
			break;
		case string_code::task7:
			PrintVertices(task7_prim(graph));
			break;
		case string_code::task8:
			task8_11(graph);
			break;
		case string_code::task9:
			task9_17(graph);
			break;
		case string_code::task10:
			task10_1(graph);
			break;
		case string_code::task11:
			task11_net(graph);
			break;

		case string_code::help:
			CommandMessage();
			break;

		case string_code::quit:
			graph->Save(DATA_FILE1);
			return 0;

		default:
			std::cout << "Wrong Command Number\n";
		}		
	}
}