#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Graph.h"
#include "App.h"
#include "Tasks.h"

using std::cin;
using std::getline;
const string DATA_FILE1 = "data4.json";
const string DATA_FILE2 = "data5.json";

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

			//add enum
		case string_code::addVertice:
			AddVertice(graph);
			break;

			//add enum
		case string_code::removeVertice:
			RemoveVertice(graph);
			break;

		case string_code::addEdge:
			AddEdge(graph);
			break;

			//add enum
		case string_code::removeEdge:
			RemoveEdge(graph);
			break;

			//Think of uniting with AddEdge
		case string_code::changeWeight:
			ChangeWeight(graph);
			break;

		case string_code::saveGraph:
			graph->Save(DATA_FILE1);
			std::cout << "Graph saved succesfully\n";
			break;


		case string_code::task1:
			task1_14(graph);
			break;
		case string_code::task2:
			task2_9(graph);
			break;
		case string_code::task3:
			task3_10(graph, graph2);
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