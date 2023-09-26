#include <iostream>
#include <fstream>
#include "Graph.h"
#include <string>
#include <map>

void CommandMessage()
{
	std::cout << "Select command:" << '\n'
		<< "1 - Print Vertices" << '\n'
		<< "2 - Add vertice" << '\n'
		<< "3 - Remove vertice" << '\n'
		<< "4 - Add edge" << '\n'
		<< "5 - Remove edge" << '\n'
		<< "6 - Save graph" << '\n'
		<< "Type 'q' to exit" << '\n';
}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

Graph* CreateGraph(string& message, uint8_t& comNumber)
{
	std::cout << "No graph found. Choose directed or undirected graph" << '\n'
		<< "1 - Directed graph" << '\n'
		<< "2 - Undirected graph" << std::endl;
	while (comNumber != 1 && comNumber != 2)
	{
		std::cin >> message;
		comNumber = std::stoi(message);
		switch (comNumber)
		{
		case 1:
			std::cout << "Created a new directed graph";
			return new Graph(true);
		case 2:
			std::cout << "Created a new undirected graph";
			return new Graph(false);
		default:
			std::cout << "Invalid value";
			break;
		}
	}
}

const string DATA_FILE = "data3.json";

int main()
{
	string message = "";
	string verticeTitle1;
	string verticeTitle2;
	string weightMsg;
	uint8_t comNumber;

	Graph* graph;
	std::ifstream file(DATA_FILE);
	if (file.is_open())
		graph = new Graph(file);
	else
		graph = CreateGraph(message, comNumber);
	file.close();

	Graph k = Graph(*graph);

	CommandMessage();
	while (message != "q")
	{
		std::cin >> message;
		if (message == "q")
			break;
		try
		{
			comNumber = std::stoi(message);
		}
		catch (std::invalid_argument)
		{
			std::cout << "Wrong command number" << '\n';
			continue;
		}
		switch (comNumber)
		{
		case 1:
			graph->PrintVertices();
			break;
		case 2:
			std::cout << "Enter vertice to add:" << '\n';
			std::cin >> verticeTitle1;
			graph->AddVertice(verticeTitle1);
			std::cout << "Vertice added succesfully" << '\n';
			break;
		case 3:
			std::cout << "Enter vertice to remove:" << '\n';
			std::cin >> verticeTitle1;
			if (graph->RemoveVertice(verticeTitle1))
			{
				std::cout << "Vertice removed successfully" << '\n';
			}
			else
			{
				std::cout << "No such vertice in graph" << '\n';
			}
			break;
		case 4:
			std::cout << "Enter start vertice:" << '\n';
			std::cin >> verticeTitle1;
			std::cout << "Enter end vertice:" << '\n';
			std::cin >> verticeTitle2;
			std::cout << "Enter edge weight (default = 1)" << '\n';
			std::cin >> weightMsg;
			if (graph->AddEdge(verticeTitle1, verticeTitle2,
				is_number(weightMsg) ? std::stoi(weightMsg) : 1))
			{
				std::cout << "Vertice added successfully" << '\n';
			}
			else
			{
				std::cout << "No such pair of vertices in graph" << '\n';
			}
			break;
		case 5:
			std::cout << "Enter start vertice:" << '\n';
			std::cin >> verticeTitle1;
			std::cout << "Enter end vertice:" << '\n';
			std::cin >> verticeTitle2;
			if (graph->RemoveEdge(verticeTitle1, verticeTitle2))
			{
				std::cout << "Edge removed successfully" << '\n';
			}
			else
			{
				std::cout << "No such pair of vertices in graph" << '\n';
			}
			break;
		case 6:
			graph->Save(DATA_FILE);
			std::cout << "Graph saved succesfully" << '\n';
			break;
		default:
			std::cout << "Wrong Command Number" << '\n';
		}
	}
	graph->Save(DATA_FILE);
	return 0;
}