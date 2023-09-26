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
		this->adjacencyMatrix[adjList.key()] = j["vertices"][adjList.key()].get<map<string, int32_t>>();
	}
}

Graph::Graph(const Graph& copiedValue)
{
	this->isOriented = copiedValue.isOriented;
	this->adjacencyMatrix = copiedValue.adjacencyMatrix;
}

void Graph::PrintVertices()
{
	for (auto& list : adjacencyMatrix)
	{
		std::cout << list.first << '\n';
		for (auto& el : list.second)
		{
			std::cout << "(" << el.first << ", " << el.second << ") ";
		}
		std::cout << '\n';
	}
}

void Graph::AddVertice(const string& vertice)
{
	adjacencyMatrix[vertice];
}

bool Graph::AddEdge(const string& startVertice, const string& endVertice, const int32_t& weight)
{
	if (adjacencyMatrix.find(startVertice) != adjacencyMatrix.end()
		&& adjacencyMatrix.find(endVertice) != adjacencyMatrix.end())
	{
		adjacencyMatrix[startVertice][endVertice] = weight;
		if (!isOriented)
			adjacencyMatrix[endVertice][startVertice] = weight;
		//success
		return true;
	}
	else
	{
		//fail
		return false;
		std::cout << "No such vertices in graph" << '\n';
	}
	
}

bool Graph::RemoveVertice(const string& vertice)
{
	if (adjacencyMatrix.find(vertice) != adjacencyMatrix.end())
	{
		//cleaning other vertices and their edges
		
		/*
		for (auto it1 = adjacencyMatrix.begin(); it1 != adjacencyMatrix.end(); it1++)
		{
			for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
			{
				if (it2->first == vertice)
				{
					adjacencyMatrix[it1->first].erase(vertice);
				}
			}
		}
		*/
		adjacencyMatrix.erase(vertice);
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
	if (adjacencyMatrix.find(startVertice) != adjacencyMatrix.end()
		&& adjacencyMatrix.find(endVertice) != adjacencyMatrix.end())
	{
		adjacencyMatrix[startVertice].erase(endVertice);
		if (!isOriented)
		{
			adjacencyMatrix[endVertice].erase(startVertice);
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
	for (auto const& mapEl : graph.adjacencyMatrix)
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