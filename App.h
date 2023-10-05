#pragma once

#include <string>
#include <iostream>

#include "Graph.h"

enum string_code
{
	printVertices = 1,
	addVertice,
	removeVertice,
	addEdge,
	removeEdge,
	changeWeight,
	saveGraph,

	task1 = 10,
	task2,
	task3,

	help = 20,
	quit
};

string_code Hashing(std::string const& inString);
void CommandMessage();
Graph* CreateGraph(string& command);

void PrintVertices(Graph* graph);
void AddVertice(Graph* graph);
void RemoveVertice(Graph* graph);
void AddEdge(Graph* graph);
void RemoveEdge(Graph* graph);
void ChangeWeight(Graph* graph);

