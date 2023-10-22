#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <iostream>
#include <map>
#include <stack>

#include "Graph.h"

void dfs_modified(
	map<string, map<string, int32_t>>& list,
	const string& current,
	const string& end,
	map<string, bool>& used,
	vector<string>& path,
	int32_t& counter);
void dfs(map<string, map<string, int32_t>>& list, const string& vertice, map<string, bool>& used);
void bfs(map<string, map<string, int32_t>>& list, const string& vertice, map<string, bool>& used);
Graph* prim(Graph* graph, string root);

void WayBack(const string& startSource, const string& targetSource, std::stack<string>& path,
	map<string, map<string, string>>& pathVertices);

map<string, int32_t> dijkstra(Graph* graph, string root);
pair<map<string, map<string, int32_t>>,
	map<string, map<string, string>>> floyd(Graph* graph);