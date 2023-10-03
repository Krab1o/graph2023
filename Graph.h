#pragma once

#include <list>
#include <map>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using std::string;
using std::map;
using std::vector;
using std::list; 
using std::pair;
using std::ofstream;
using std::ifstream;

class Graph
{
	friend void to_json(json& j, const Graph& graph);
public:

	enum graph_orientation
	{
		undirected = 0,
		directed = 1
	};

	enum code_error
	{
		no_error = 0,

		vertice_exists,
		no_vertice1,
		no_vertice2,

		replacement,
		edge_exists,
		no_edge
	};

	Graph(bool orient = true);
	Graph(ifstream& file);
	Graph(const Graph& copiedValue);
	const map<string, map<string, int32_t>> getAdjacencyList() const;

	static graph_orientation Hashing(string const& inString);

	void PrintVertices();

	bool AddVertice(const string& value);
	uint8_t AddEdge(const string& startVertice, const string& endVertice, const int32_t& weight);

	bool RemoveVertice(const string& vertice);
	bool RemoveEdge(const string& startVertice, const string& endVertice);

	uint8_t ChangeWeight(const string& startVertice, const string& endVertice, const int32_t& weight);

	void Save(string fileName);
private:
	map<string, map<string, int32_t>> adjacencyList;
	bool isOriented;
};

