#pragma once

#include <map>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using std::string;
using std::map;
using std::vector;
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
		edge_exists,
		no_edge
	};

	Graph(bool orient = true);
	Graph(ifstream& file);
	Graph(const Graph& copiedValue);
	Graph(map<string, map<string, int32_t>>, bool isOriented);

	const map<string, map<string, int32_t>> GetAdjacencyList() const;
	bool GetOrientation();
	void ChangeOrientation();

	bool isVertice(string s);
	bool isEdge(string s1, string s2);
	
	static graph_orientation Hashing(string const& inString);

	uint8_t AddVertice(const string& value);
	uint8_t AddEdge(const string& startVertice, const string& endVertice, const int32_t& weight);

	uint8_t RemoveVertice(const string& vertice);
	uint8_t RemoveEdge(const string& startVertice, const string& endVertice);

	uint8_t ChangeWeight(const string& startVertice, const string& endVertice, const int32_t& weight);
	void Unweight();

	void Save(string fileName);
private:
	map<string, map<string, int32_t>> adjacencyList;
	bool isOriented;
};

