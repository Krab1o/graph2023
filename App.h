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
	unweightGraph,

	task2 = 10,
	task3,
	task4,
	task5,
	task6,
	task7,
	task8,
	task9,
	task10,
	task11,

	help = 30,
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
void Unweight(Graph* graph);
