#include "Graph.h"

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
const map<string, map<string, int32_t>> Graph::GetAdjacencyList() const
{
	return adjacencyList;
}

bool Graph::GetOrientation()
{
	return isOriented;
}

void Graph::ChangeOrientation()
{
	isOriented = !isOriented;
}

bool Graph::isVertice(string s)
{
	return !(adjacencyList.find(s) == adjacencyList.end());
}

bool Graph::isEdge(string s1, string s2)
{
	return adjacencyList[s1].find(s2) != adjacencyList[s1].end();
}


Graph::graph_orientation Graph::Hashing(std::string const& inString)
{
	if (inString == "0") 
		return graph_orientation::undirected;
	else 
		return graph_orientation::directed;
}

//methods
uint8_t Graph::AddVertice(const string& vertice)
{
	if (!isVertice(vertice))
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
	if (!isVertice(startVertice))
		return code_error::no_vertice1;

	//fail: no second vertice
	if (!isVertice(endVertice))
		return code_error::no_vertice2;

	//fail: no such edge
	if (!isEdge(startVertice, endVertice))
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
	if (!isVertice(startVertice))
		return code_error::no_vertice1;

	//fail: no second vertice
	if (!isVertice(endVertice))
		return code_error::no_vertice2;

	//fail: edge already exists
	if (isEdge(startVertice, endVertice))
		return code_error::edge_exists;

	//success
	adjacencyList[startVertice][endVertice] = weight;
	if (!isOriented)
		adjacencyList[endVertice][startVertice] = weight;
	return code_error::no_error;
}

uint8_t Graph::RemoveVertice(const string& removedVertice)
{
	//fail: no such vertice
	if (!isVertice(removedVertice))
		return code_error::no_vertice1;

	//success, cleaning other vertices and their edges
	for (auto vert : adjacencyList)
	{
		this->RemoveEdge(vert.first, removedVertice);
		this->RemoveEdge(removedVertice, vert.first);
	}
	adjacencyList.erase(removedVertice);
	return code_error::no_error;
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

void Graph::Unweight()
{
	for (auto vert1 = adjacencyList.begin(); vert1 != adjacencyList.end(); vert1++)
	{
		for (auto vert2 = adjacencyList.begin(); vert2 != adjacencyList.end(); vert2++)
		{
			if (isEdge(vert1->first, vert2->first))
				adjacencyList[vert1->first][vert2->first] = 1;
		}
	}
}

void Graph::Save(string fileName)
{
	json j = *this;
	std::ofstream data(fileName);
	data << std::setw(4) << j;
}

void to_json(json& j, const Graph& graph)
{
	j["orient"] = graph.isOriented;
	for (auto const& mapEl : graph.adjacencyList)
	{
		j["vertices"][mapEl.first] = mapEl.second;
	}
}