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

	Graph(bool orient = true);
	Graph(ifstream& file);
	Graph(const Graph& copiedValue);

	void PrintVertices();

	void AddVertice(const string& value);
	bool AddEdge(const string& startVertice, const string& endVertice, const int32_t& weight);

	bool RemoveVertice(const string& vertice);
	bool RemoveEdge(const string& startVertice, const string& endVertice);

	void Save(string fileName);

private:
	map<string, map<string, int32_t>> adjacencyMatrix;
	bool isOriented;
};

