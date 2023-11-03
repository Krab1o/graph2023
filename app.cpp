#include "App.h"

using std::string;
using std::getline;
using std::cin;
using std::cout;

string_code Hashing(std::string const& inString) {
	if (inString == "1") return printVertices;
	if (inString == "2") return addVertice;
	if (inString == "3") return removeVertice;
	if (inString == "4") return addEdge;
	if (inString == "5") return removeEdge;
	if (inString == "6") return changeWeight;
	if (inString == "7") return saveGraph;
	if (inString == "8") return unweightGraph;

	if (inString == "T2") return task2;
	if (inString == "T3") return task3;
	if (inString == "T4") return task4;
	if (inString == "T5") return task5;
	if (inString == "T6") return task6;
	if (inString == "T7") return task7;
	if (inString == "T8") return task8;
	if (inString == "T9") return task9;
	if (inString == "T10") return task10;
	if (inString == "T11") return task11;

	if (inString == "h") return help;
	if (inString == "q") return quit;
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
		<< "7 - Save graph\n"
		<< "8 - Unweight graph\n"
		<< '\n'
		<< "T2 - task 2\n"
		<< "T3 - task 3\n"
		<< "T4 - task 4\n"
		<< "T5 - task 5\n"
		<< "T6 - task 6\n"
		<< "T7 - task 7\n"
		<< "T8 - task 8\n"
		<< "T9 - task 9\n"
		<< "T10 - task 10\n"
		<< "T11 - task 11\n"
		<< '\n'
		<< "'h' to print this message\n"
		<< "'q' to exit program\n";
}

Graph* CreateGraph(string& command)
{
	while (true)
	{
		std::cout << "No graph found. Choose directed or undirected graph\n"
			<< "1 - Directed graph\n"
			<< "2 - Undirected graph\n";
		getline(std::cin, command);
		switch (Graph::Hashing(command))
		{
		case Graph::undirected:
			std::cout << "Created a new undirected graph\n";
			return new Graph(false);
		case Graph::directed:
			std::cout << "Created a new directed graph\n";
			return new Graph(true);
		default:
			break;
		}
	}
}

//Hidden
bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && (std::isdigit(*it) || (*it) == '-')) ++it;
	return !s.empty() && it == s.end();
}

void PrintVertices(Graph* graph)
{
	auto adjacencyList = graph->getAdjacencyList();

	for (auto& list : adjacencyList)
	{
		std::cout << list.first << ": ";
		for (auto& el : list.second)
		{
			std::cout << "(" << el.first << ", " << el.second << ") ";
		}
		std::cout << '\n';
	}
}

void AddVertice(Graph* graph)
{
	string vertice;
	std::cout << "Enter vertice to add: ";
	getline(cin, vertice);
	switch (graph->AddVertice(vertice))
	{
	case Graph::code_error::no_error:
		std::cout << "Vertice added succesfully\n";
		break;
	case Graph::code_error::vertice_exists:
		std::cout << "Vertice already exists\n";
		break;
	}	
}

void RemoveVertice(Graph* graph)
{
	string vertice;
	std::cout << "Enter vertice to remove: ";
	getline(cin, vertice);
	switch (graph->RemoveVertice(vertice))
	{
	case Graph::code_error::no_error:
		std::cout << "Vertice removed successfully\n";
		break;
	case Graph::code_error::no_vertice1:
		std::cout << "No such vertice in graph\n";
		break;
	}
}

//TODO: переписать is_number
void AddEdge(Graph* graph)
{
	string vertice1;
	string vertice2;
	string weightMsg;
	std::cout << "Enter start vertice: ";
	getline(cin, vertice1);
	std::cout << "Enter end vertice: ";
	getline(cin, vertice2);
	std::cout << "Enter edge weight (default = 1): ";
	getline(cin, weightMsg);
	if (weightMsg.empty())
		weightMsg = "1";
	while (!is_number(weightMsg))
	{
		std::cout << "Wrong weight value! Enter integer: ";
		getline(cin, weightMsg);
		if (weightMsg.empty())
			weightMsg = "1";
	}

	switch (graph->AddEdge(vertice1, vertice2, std::stoi(weightMsg)))
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
}

void RemoveEdge(Graph* graph)
{
	string vertice1;
	string vertice2;
	std::cout << "Enter start vertice: ";
	getline(cin, vertice1);
	std::cout << "Enter end vertice: ";
	getline(cin, vertice2);

	switch (graph->RemoveEdge(vertice1, vertice2))
	{
	case Graph::code_error::no_edge:
		std::cout << "No such edge in graph\n";
		break;
	case Graph::code_error::no_error:
		std::cout << "Edge removed successfully\n";
		break;
	}
}

void ChangeWeight(Graph* graph)
{
	string vertice1;
	string vertice2;
	string weightMsg;
	std::cout << "Enter start vertice: ";
	getline(cin, vertice1);
	std::cout << "Enter end vertice: ";
	getline(cin, vertice2);
	std::cout << "Enter edge weight (default = 1): ";
	getline(cin, weightMsg);
	if (weightMsg.empty())
		weightMsg = "1";
	while (!is_number(weightMsg))
	{
		std::cout << "Wrong weight value! Enter integer: ";
		getline(cin, weightMsg);
	}

	switch (graph->ChangeWeight(vertice1, vertice2, std::stoi(weightMsg)))
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
		std::cout << "Weight changed successfully\n";
		break;
	}
}

void Unweight(Graph* graph)
{
	graph->Unweight();
	std::cout << "Weight of all edges changed to 1\n";
}