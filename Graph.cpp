#include "Graph.h"
#include <iostream>

Graph::Graph(bool isOriented)
{
	this->isOriented = isOriented;
}

Graph::Graph(ifstream& file)
{
	json j;
	file >> j;
	this->isOriented = j["orient"];
	for (auto& adjList : j["vertices"].items())
	{
		this->adjacencyList[adjList.key()] = j["vertices"][adjList.key()].get<map<string, int32_t>>();
	}
}

Graph::Graph(const Graph& copiedValue)
{
	this->isOriented = copiedValue.isOriented;
	this->adjacencyList = copiedValue.adjacencyList;
}

Graph::Graph(map <string, map<string, int32_t>> list, bool isOriented)
{
	this->adjacencyList = list;
	this->isOriented = isOriented;
}

//getters
const map<string, map<string, int32_t>> Graph::getAdjacencyList() const
{
	return adjacencyList;
}

bool Graph::getOrientation()
{
	return isOriented;
}

Graph::graph_orientation Graph::Hashing(std::string const& inString)
{
	if (inString == "0") return graph_orientation::undirected;
	else return graph_orientation::directed;
}

//methods
uint8_t Graph::AddVertice(const string& vertice)
{
	if (adjacencyList.find(vertice) == adjacencyList.end())
	{
		adjacencyList[vertice];
		return code_error::no_error;
	}
	else
		return code_error::vertice_exists;
}

uint8_t Graph::ChangeWeight(const string& startVertice, const string& endVertice, const int32_t& weight)
{
	//fail: no first vertice
	if (adjacencyList.find(startVertice) == adjacencyList.end())
		return code_error::no_vertice1;

	//fail: no second vertice
	if (adjacencyList.find(endVertice) == adjacencyList.end())
		return code_error::no_vertice2;

	//fail: no such edge
	if (adjacencyList[startVertice].find(endVertice) == adjacencyList[startVertice].end())
		return code_error::no_edge;

	//success
	adjacencyList[startVertice][endVertice] = weight;
	if (!isOriented)
		adjacencyList[endVertice][startVertice] = weight;
	return code_error::no_error;	
}

uint8_t Graph::AddEdge(const string& startVertice, const string& endVertice, const int32_t& weight)
{
	//fail: no first vertice
	if (adjacencyList.find(startVertice) == adjacencyList.end())
		return code_error::no_vertice1;

	//fail: no second vertice
	if (adjacencyList.find(endVertice) == adjacencyList.end())
		return code_error::no_vertice2;

	//fail: edge already exists
	if (adjacencyList[startVertice].find(endVertice) != adjacencyList[startVertice].end())
		return code_error::edge_exists;

	//success
	adjacencyList[startVertice][endVertice] = weight;
	if (!isOriented)
		adjacencyList[endVertice][startVertice] = weight;
	return code_error::no_error;
}

uint8_t Graph::RemoveVertice(const string& removedVertice)
{
	if (adjacencyList.find(removedVertice) != adjacencyList.end())
	{
		//cleaning other vertices and their edges
		for (auto vert : adjacencyList)
		{
			this->RemoveEdge(vert.first, removedVertice);
			this->RemoveEdge(removedVertice, vert.first);
		}
		adjacencyList.erase(removedVertice);
		//success
		return code_error::no_error;
	}
	else
	{
		//fail
		return code_error::no_vertice1;
	}
}

uint8_t Graph::RemoveEdge(const string& startVertice, const string& endVertice)
{
	if (adjacencyList[startVertice].find(endVertice) != adjacencyList[startVertice].end())
	{
		adjacencyList[startVertice].erase(endVertice);
		if (!isOriented)
		{
			adjacencyList[endVertice].erase(startVertice);
		}
		//success
		return no_error;
	}
	else
		return code_error::no_edge;
}

void Graph::Save(string fileName)
{
	json j = *this;
	std::ofstream data(fileName);
	data << std::setw(4) << j;
}

//TODO: create json to_file and json from_file

void to_json(json& j, const Graph& graph)
{
	j["orient"] = graph.isOriented;
	for (auto const& mapEl : graph.adjacencyList)
	{
		j["vertices"][mapEl.first] = mapEl.second;
	}
}

/*
void from_json(const json& j, Graph& graph)
{
	j.at("orient").get_to(graph.isOriented);
	j.at("vertices").get_to(graph.adjacencyMatrix);
}
*/