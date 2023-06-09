#pragma once
#include <iostream>
#include <string>
#include "files.h"
#include "graph.h"
#include <fstream>
#include <unordered_map>
#include "coloredOutput.cpp"

using namespace std;
/**
* writeGraphToFile-> write the graphs data in the files
* @param graph to be saved of datatype graph
* @param filename which is the file name of datatype stirng
* Return: void
*/
void writeGraphToFile(graph& g, const string& filename) {
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		failureMessage("Unable to open file for writing\n");
		return;
	}
	// write the number of vertices in the graph
	outFile << g.getVertexNum() << endl;
	// iterate over each city and its adjacent list
	for (const auto& cityPair : g.map) {
		// write the city name
		outFile << cityPair.first << endl;
		// write the number of adjacent vertices
		outFile << cityPair.second.size() << endl;
		// iterate over each adjacent vertex and its distance
		for (const auto& adjPair : cityPair.second)
		{
			// write the adjacent city name and its distance
			outFile << adjPair.first << " " << adjPair.second << endl;
		}
	}
	outFile.close();
}

/**
* readGraphFromFile-> read the graphs data from the files
* @param g to be filled with data of datatype graph
* @param filename which is the file name of datatype stirng
* Return: void
*/
void readGraphFromFile(graph& g, const string& filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		failureMessage("Unable to open file for reading\n");
		return;
	}

	int vertexNum;
	inFile >> vertexNum;

	string cityName, adjCityName;
	float distance;

	// Read all city names
	vector<string> cityNames;
	for (int i = 0; i < vertexNum; i++) {
		inFile >> cityName;
		inFile.ignore();
		inFile.ignore();
		cityNames.push_back(cityName);
	}

	// Add all cities to the graph
	for (const string& city : cityNames) {
		g.addCity(city);
	}
	// Read and add roads for each city
	inFile.seekg(0, ios::beg);
	inFile.ignore();
	for (int i = 0; i < vertexNum; i++) {
		inFile >> cityName;
		int adjNum;
		inFile >> adjNum;
		// Iterate over adjacent cities and distances
		for (int j = 0; j < adjNum; j++) {
			inFile >> adjCityName >> distance;
			g.addEditRoad(cityName, adjCityName, distance);
		}
	}
	inFile.close();
}

/**
* writeMultipleGraphs-> write the maps data in the files
* @param graphs to be saved of datatype unordered map
* @param directory which is the file name to read data from it with datatype stirng
* Return: void
*/
void writeMultipleGraphs( unordered_map<string, graph>& graphs, const string& directory) {
	ofstream fileList(directory + "/filelist.txt");
	for (const auto& graphPair : graphs) {
		const string& graphName = graphPair.first;
		graph g = graphPair.second;
		const string filename = directory + "/" + graphName + ".txt";
		writeGraphToFile(g, filename);
		fileList << graphName << ".txt" << endl; // Add the graph name to filelist.txt
	}
}

/**
* readMultipleGraphs-> read the map data from the files
* @param directory which is the file name to read data from it with datatype stirng
* Return: graphs of datatype unorder map which is the maps already saved in the system
*/
unordered_map<string, graph> readMultipleGraphs(const string& directory) {
	unordered_map<string, graph> graphs;
	ifstream fileList(directory + "/filelist.txt");
	if (!fileList.is_open()) {
		failureMessage("Unable to open filelist.txt for reading\n");
		return graphs;
	}
	string filename;
	while (getline(fileList, filename)) {
		const string graphName = filename.substr(0, filename.length() - 4); // Remove ".txt" extension
		const string filepath = directory + "/" + filename;
		graph g;
		readGraphFromFile(g, filepath);
		graphs[graphName] = g;
	}
	fileList.close();
	return graphs;
}
