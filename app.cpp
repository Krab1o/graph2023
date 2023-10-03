#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Graph.h"

using std::cin;
using std::getline;
const string DATA_FILE = "data4.json";

enum string_code
{
	printVertices = 1,
	addVertice,
	removeVertice,
	addEdge,
	removeEdge,
	changeWeight,
	saveGraph,

	task1 = 10,
	task2,

	help = 20,
	quit
};

string_code Hashing(std::string const& inString) {
	if (inString == "1") return printVertices;
	if (inString == "2") return addVertice;
	if (inString == "3") return removeVertice;
	if (inString == "4") return addEdge;
	if (inString == "5") return removeEdge;
	if (inString == "6") return changeWeight;
	if (inString == "7") return saveGraph;

	if (inString == "T1") return task1;
	if (inString == "T2") return task2;

	if (inString == "h") return help;
	if (inString == "q") return quit;
}

void task1_14(Graph* graph, const string& vertice)
{
	auto list = graph->getAdjacencyList();
	auto map = list[vertice];
	std::cout << vertice << ": ";
	for (auto& el : map)
	{
		std::cout << "(" << el.first << ", " << el.second << ") ";
	}
	std::cout << '\n';
}

void task2_9(Graph* graph, const string& vertice)
{
	auto list = graph->getAdjacencyList();
	auto mapTarget = list[vertice];
	for (auto el : list)
	{
		if (el.second.size() > mapTarget.size())
		{
			std::cout << el.first << ' ';
		}
	}
	std::cout << '\n';
}

void CommandMessage()
{
	std::cout << "Select command:\n"
		<< "1 - Print Vertices\n"
		<< "2 - Add vertice\n"
		<< "3 - Remove vertice\n"
		<< "4 - Add edge\n"
		<< "5 - Remove edge\n"
		<< "6 - Change edge's weight\n"
		<< "7 - Save graph\n\n"
		<< "T1 - task 1\n"
		<< "T2 - task 2\n"
		<< '\n'
		<< "'h' to print this message\n"
		<< "'q' to exit program\n";
}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

Graph* CreateGraph(string& command)
{
	while (true)
	{
		std::cout << "No graph found. Choose directed or undirected graph\n"
			<< "1 - Directed graph\n"
			<< "2 - Undirected graph\n";
		getline(cin, command);
		switch (Graph::Hashing(command))
		{
		case Graph::undirected:
			std::cout << "Created a new directed graph\n";
			return new Graph(true);
		case Graph::directed:
			std::cout << "Created a new undirected graph\n";
			return new Graph(false);
		default:
			break;
		}
	}
}

int main()
{
	string command;
	string verticeTitle1;
	string verticeTitle2;
	string weightMsg;
	uint8_t code;

	Graph* graph;
	std::ifstream file(DATA_FILE);
	if (file.is_open())
		graph = new Graph(file);
	else
		graph = CreateGraph(command);
	file.close();

	//copy-constructor test
	Graph k = Graph(*graph);

	CommandMessage();
	while (true)
	{
		std::cout << "Command: ";
		getline(cin, command);
		switch (Hashing(command))
		{
		case string_code::printVertices:
			graph->PrintVertices();
			break;

			//add enum
		case string_code::addVertice:
			std::cout << "Enter vertice to add: ";
			getline(cin, verticeTitle1);
			if (graph->AddVertice(verticeTitle1))
				std::cout << "Vertice added succesfully\n";
			else
				std::cout << "Vertice already exists\n";
			break;

			//add enum
		case string_code::removeVertice:
			std::cout << "Enter vertice to remove: ";
			getline(cin, verticeTitle1);
			if (graph->RemoveVertice(verticeTitle1))
				std::cout << "Vertice removed successfully\n";
			else
				std::cout << "No such vertice in graph\n";
			break;

		case string_code::addEdge:
			std::cout << "Enter start vertice: ";
			getline(cin, verticeTitle1);
			std::cout << "Enter end vertice: ";
			getline(cin, verticeTitle2);
			std::cout << "Enter edge weight (default = 1): ";
			getline(cin, weightMsg);
			if (weightMsg.empty())
				weightMsg = "1";
			while (!is_number(weightMsg))
			{
				std::cout << "Wrong weight value! Enter integer: ";
				getline(cin, weightMsg);
			}

			code = graph->AddEdge(verticeTitle1, verticeTitle2, std::stoi(weightMsg));
			switch (code)
			{
			case Graph::no_vertice1:
				std::cout << "No vertice 1 represented in graph\n";
				break;
			case Graph::no_vertice2:
				std::cout << "No vertice 2 represented in graph\n";
				break;
			case Graph::edge_exists:
				std::cout << "Edge already exists between these 2 vertices\n";
				break;
			case Graph::no_error:
				std::cout << "Edge added successfully\n";
				break;
			}
			break;

		case string_code::removeEdge:
			std::cout << "Enter start vertice: ";
			getline(cin, verticeTitle1);
			std::cout << "Enter end vertice: ";
			getline(cin, verticeTitle2);
			if (graph->RemoveEdge(verticeTitle1, verticeTitle2))
				std::cout << "Edge removed successfully\n";
			else
				std::cout << "No such edge in graph\n";
			break;

			//Think of uniting with AddEdge
		case string_code::changeWeight:
			std::cout << "Enter start vertice: "; 
			getline(cin, verticeTitle1);
			std::cout << "Enter end vertice: ";
			getline(cin, verticeTitle2);
			std::cout << "Enter edge weight (default = 1): ";
			getline(cin, weightMsg);
			if (weightMsg.empty())
				weightMsg = "1";
			while (!is_number(weightMsg))
			{
				std::cout << "Wrong weight value! Enter integer: ";
				getline(cin, weightMsg);
			}
			code = graph->ChangeWeight(verticeTitle1, verticeTitle2, std::stoi(weightMsg));
			switch (code)
			{
			case Graph::no_vertice1:
				std::cout << "No vertice 1 represented in graph\n";
				break;
			case Graph::no_vertice2:
				std::cout << "No vertice 2 represented in graph\n";
				break;
			case Graph::no_edge:
				std::cout << "No edge exists between these 2 vertices\n";
				break;
			case Graph::no_error:
				std::cout << "Edge added successfully\n";
				break;
			}
			break;

		case string_code::saveGraph:
			graph->Save(DATA_FILE);
			std::cout << "Graph saved succesfully\n";
			break;

		case string_code::task1:
			std::cout << "Enter vertice to print: ";
			getline(cin, verticeTitle1);
			task1_14(graph, verticeTitle1);
			break;
		case string_code::task2:
			std::cout << "Enter vertice: ";
			getline(cin, verticeTitle1);
			task2_9(graph, verticeTitle1);
			break;

		case string_code::help:
			CommandMessage();
			break;

		case string_code::quit:
			graph->Save(DATA_FILE);
			return 0;

		default:
			std::cout << "Wrong Command Number\n";
		}		
	}
	graph->Save(DATA_FILE);
	return 0;
}