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

void Graph::PrintVertices()
{
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

const map<string, map<string, int32_t>> Graph::getAdjacencyList() const
{
	return adjacencyList;
}

Graph::graph_orientation Graph::Hashing(std::string const& inString)
{
	if (inString == "0") return undirected;
	else return directed;
}

bool Graph::AddVertice(const string& vertice)
{
	if (adjacencyList.find(vertice) == adjacencyList.end())
	{
		adjacencyList[vertice];
		return true;
	}
	else
	{
		return false;
	}
}

//OPTIMIZE (MAYBE ADD REPLACE METHOD)
uint8_t Graph::AddEdge(const string& startVertice, const string& endVertice, const int32_t& weight)
{
	auto k = adjacencyList[startVertice];
	if (adjacencyList.find(startVertice) == adjacencyList.end()
		&& adjacencyList.find(endVertice) == adjacencyList.end())
	{
		//fail: no such vertices
		return code_error::no_vertices;
	}
	if (adjacencyList[startVertice].find(endVertice) != adjacencyList[startVertice].end())
	{
		//fail: edge already exists 
		if (adjacencyList[startVertice][endVertice] == weight)
			return code_error::edge_exists;
		else
		{
			adjacencyList[startVertice][endVertice] = weight;
			if (!isOriented)
				adjacencyList[endVertice][startVertice] = weight;
			//success
			return code_error::replacement;
		}
	}
	adjacencyList[startVertice][endVertice] = weight;
	if (!isOriented)
		adjacencyList[endVertice][startVertice] = weight;
	//success
	return code_error::no_error;
}

bool Graph::RemoveVertice(const string& removedVertice)
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
		return true;
	}
	else
	{
		//fail
		return false;
	}
}

bool Graph::RemoveEdge(const string& startVertice, const string& endVertice)
{
	if (adjacencyList[startVertice].find(endVertice) != adjacencyList[startVertice].end())
	{
		adjacencyList[startVertice].erase(endVertice);
		if (!isOriented)
		{
			adjacencyList[endVertice].erase(startVertice);
		}
		//success
		return true;
	}
	else
	{
		//fail
		return false;
	}
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