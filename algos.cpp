#include "algos.h"

void dfs_modified(
	map<string, map<string, int32_t>>& list,
	const string& current,
	const string& end,
	map<string, bool>& used,
	vector<string>& path,
	int32_t& counter)
{
	if (current == end)
	{
		for (auto it = path.begin(); it != path.end(); it++)
		{
			std::cout << *it << "->";
		}
		++counter;
		std::cout << end << '\n';
		return;
	}

	used[current] = true;
	for (auto it : list[current])
	{
		if (!used[it.first])
		{
			path.push_back(current);
			dfs_modified(list, it.first, end, used, path, counter);
			path.pop_back();
		}
	}
	used[current] = false;
}

void dfs(map<string, map<string, int32_t>>& list, const string& vertice, map<string, bool>& used)
{
	used[vertice] = true;
	for (auto it : list[vertice])
	{
		if (!used[it.first])
		{
			dfs(list, it.first, used);
		}
	}
}

void bfs(map<string, map<string, int32_t>>& list, const string& vertice, map<string, bool>& used)
{
	string cur;
	std::queue<string> q;
	used[vertice] = true;
	q.push(vertice);
	while (!q.empty())
	{
		cur = q.front();
		q.pop();
		for (auto it : list[cur])
		{
			if (!used[it.first])
			{
				used[it.first] = true;
				q.push(it.first);
			}
		}
	}
}

Graph* prim(Graph* graph, string root = "")
{
	Graph* tree = new Graph(graph->getOrientation());
	auto list = graph->getAdjacencyList();

	map<string, bool> used;
	map<string, int32_t> minEdge;
	map<string, string> prevEdge;
	for (auto it : list)
	{
		used[it.first] = false;
		minEdge[it.first] = INT32_MAX;
		prevEdge[it.first] = "";
	}
	if (root == "")
	{
		minEdge[list.begin()->first] = 0;
		tree->AddVertice(list.begin()->first);
	}
	else
	{
		minEdge[root] = 0;
		tree->AddVertice(root);
	}

	for (auto it : list)
	{
		string v = "";
		for (auto minVert : list)
		{
			if (!used[minVert.first] && (v == "" || minEdge[minVert.first] < minEdge[v]))
				v = minVert.first;
		}
		if (v == "")
		{
			//no MST
			std::cout << "No MST\n";
			return new Graph();
		}

		used[v] = true;
		if (prevEdge[v] != "")
		{
			auto treeList = tree->getAdjacencyList();
			tree->AddVertice(v);
			tree->AddEdge(v, prevEdge[v], list[v][prevEdge[v]]);
			//std::cout << v << ' ' << prevEdge[v] << '\n';
		}

		for (auto vert : list[v])
			if (vert.second < minEdge[vert.first])
			{
				minEdge[vert.first] = vert.second;
				prevEdge[vert.first] = v;
			}
	}
	return tree;
}

map<string, int32_t> dijkstra(Graph* graph, string root)
{
	auto list = graph->getAdjacencyList();
	map<string, int32_t> minimalDistance;
	//map<string, string> pathVertices;
	map <string, bool> used;
	for (auto vert1 : list)
	{
		minimalDistance[vert1.first] = INT32_MAX;
		//pathVertices[vert1.first] = "";
		used[vert1.first] = false;
	}
	minimalDistance[root] = 0;
	int32_t newDistance;
	string currentClosest;

	for (auto clos : list)
	{
		currentClosest = "";
		for (auto vert : minimalDistance)
		{
			if (!used[vert.first] &&
				(currentClosest == "" || minimalDistance[vert.first] < minimalDistance[currentClosest]))
			{
				currentClosest = vert.first;
			}
		}
		if (minimalDistance[currentClosest] == INT32_MAX)
			break;
		used[currentClosest] = true;
		for (auto vert : list[currentClosest])
		{
			newDistance = minimalDistance[currentClosest] + vert.second;
			if (newDistance < minimalDistance[vert.first])
			{
				minimalDistance[vert.first] = newDistance;
				//pathVertices[vert.first] = currentClosest;
			}
		}
	}
	return minimalDistance;
}

pair<map<string, map<string, int32_t>>,
	map<string, map<string, string>>> floyd(Graph* graph)
{
	auto list = graph->getAdjacencyList();
	map<string, map<string, int32_t>> minimalDistance;
	map<string, map<string, string>> pathVertices;
	for (auto vert1 : list)
	{
		minimalDistance[vert1.first];
		pathVertices[vert1.first];
		for (auto vert2 : list)
		{
			if (vert1.second.find(vert2.first) != vert1.second.end())
			{
				minimalDistance[vert1.first][vert2.first] = vert1.second[vert2.first];
				pathVertices[vert1.first][vert2.first] = vert1.first;
			}
			else
			{
				minimalDistance[vert1.first][vert2.first] = vert1.first == vert2.first ? 0 : INT32_MAX;
				pathVertices[vert1.first][vert2.first] = "";
			}	
		}
	}

	int32_t newDistance;
	int32_t edge1, edge2;
	for (auto relaxVertice : list)
	{
		for (auto vert1 : list)
		{
			for (auto vert2 : list)
			{
				edge1 = minimalDistance[vert1.first][relaxVertice.first];
				edge2 = minimalDistance[relaxVertice.first][vert2.first]; 
				if (edge1 != INT32_MAX && edge2 != INT32_MAX)
				{
					newDistance = edge1 + edge2;
					if (newDistance < minimalDistance[vert1.first][vert2.first])
					{
						minimalDistance[vert1.first][vert2.first] = newDistance;
						pathVertices[vert1.first][vert2.first] = pathVertices[relaxVertice.first][vert2.first];
					}
				}
			}
		}
	}
	return std::make_pair(minimalDistance, pathVertices);
}

void WayBack(const string& startSource, const string& targetSource, std::stack<string>& path,
	map<string, map<string, string>>& pathVertices)
{
	path.push(targetSource);
	if (targetSource == startSource)
		return;
	WayBack(startSource, pathVertices[startSource][targetSource], path, 
		pathVertices);
}