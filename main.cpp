#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Graph.h"
#include "App.h"
#include "Tasks.h"

const string DATA_FILE1 = "task4_1.json";
const string DATA_FILE2 = "task4_1.json";

int main()
{
	string command;

	Graph* graph1;
	std::ifstream file(DATA_FILE1);
	if (file.is_open())
		graph1 = new Graph(file);
	else
		graph1 = CreateGraph(command);
	file.close();

	file.open(DATA_FILE2);
	Graph* graph2 = new Graph(file);
	file.close();

	CommandMessage();
	while (true)
	{
		std::cout << "Command: ";
		std::getline(std::cin, command);
		switch (Hashing(command))
		{
		case string_code::printVertices:
			PrintVertices(graph1);
			break;
		case string_code::addVertice:
			AddVertice(graph1);
			break;
		case string_code::removeVertice:
			RemoveVertice(graph1);
			break;
		case string_code::addEdge:
			AddEdge(graph1);
			break;
		case string_code::removeEdge:
			RemoveEdge(graph1);
			break;
		case string_code::changeWeight:
			ChangeWeight(graph1);
			break;
		case string_code::unweightGraph:
			Unweight(graph1);
			break;

		case string_code::saveGraph:
			graph1->Save(DATA_FILE1);
			std::cout << "Graph saved succesfully\n";
			break;

		case string_code::task2:
			task2_14(graph1);
			break;
		case string_code::task3:
			task3_9(graph1);
			break;
		case string_code::task4:
			task4_10(graph1, graph2);
			break;
		case string_code::task5:
			task5_2(graph1);
			break;
		case string_code::task6:
			task6_20(graph1);
			break;
		case string_code::task7:
			task7_prim(graph1);
			break;
		case string_code::task8:
			task8_11(graph1);
			break;
		case string_code::task9:
			task9_17(graph1);
			break;
		case string_code::task10:
			task10_1(graph1);
			break;
		case string_code::task11:
			task11_net(graph1);
			break;

		case string_code::help:
			CommandMessage();
			break;
		case string_code::quit:
			graph1->Save(DATA_FILE1);
			return 0;

		default:
			std::cout << "Wrong Command Number\n";
		}		
	}
}