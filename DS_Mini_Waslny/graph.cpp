#pragma once
#include <iostream>
#include <string.h>
#include <utility>
#include <unordered_map>
#include <list>
#include "graph.h"

using namespace std;


/*
	* Notes:
	* map.at() -> returns a pointer to the value
	* map.insert() -> adds a new key-value
	* map.find() -> return an iterator pointing to the vertex if it exists
	*				and to the last vertex if it doesn't
	* map.erase() -> return 1 if found key and erase it otherwise return 0
*/

/**
* graph - the graph constructor
*
* Description: sets the #vertices to zero
*
* Return: nothing
*/
graph::graph()
{
	vertexNum = 0;
}

/**
* getVertexNum - returns #vertices
* Return: integer value -> #vertices
*/
int graph::getVertexNum()
{
	return vertexNum;
}

/**
* addCity - Adds a new City
* @newCity: City Name
*
* Description: if the city already exists, it gives an Error Message
*			   else it adds a new vertex for the city with an empty list of
*			   adjacent vertices
*
* Return: nothing
*/
void graph::addCity(string newCity)
{
	mapIterator = map.find(newCity);

	// if it already exists
	if (mapIterator != map.end())
		cout << "City " << newCity << "already exists = | \n";
	else //add the new city
	{
		//empty list
		list <pair <string, float>> newList;

		//make new list for the new city
		map[newCity] = newList;

		//increment number of cities
		vertexNum++;

		cout << newCity << " is Added Successfully =)\n";
	}
}

/**
* addCity - Adds a new City and connects it with another on
*			with a given distance
* @newCity: City Name to be added
* @adjCity: City Name to be connected with
* @distance: Distance
*
* Description: if the city already exists, it gives an Error Message
*			   else it adds a new vertex for the city and calls addRoad()
*			   to connect them
*
* Return: nothing
*/
void graph::addCity(string newCity, string adjCity, float distance)
{
	mapIterator = map.find(newCity);

	bool validInput = true;
	// if the vetex to be added already exists
	if (mapIterator != map.end())
	{
		cout << "City " << newCity << " already exists =| \n";
		validInput = false;
	}
	// if the vertex we'r connecting to doesn't exist
	if (map.find(adjCity) == map.end())
	{
		cout << "City " << adjCity << " doesn't exist. You can't link to it\n";
		validInput = false;
	}

	// add the new city
	if (validInput)
	{
		// empty list
		list <pair <string, float>> newList;
		// make new list for the new city
		map[newCity] = newList;
		addRoad(newCity, adjCity, distance);
	}
}

/**
* addRoad - Connects 2 cities
* @city1: first city
* @city2: second city
* @distance: Distance
*
* Description: makes sure both of them exist.
*			   if so, adds the road
*
* Return: nothing
*/
void graph::addRoad(string city1, string city2, float distance)
{

	bool validInput = true;
	// if the first one doesn't exist
	if (map.find(city1) == map.end())
	{
		cout << "City: " << city1 << " doesn't exist\n";
		validInput = false;
	}
	// if the second one doesnt exist
	if (map.find(city2) == map.end())
	{
		cout << "City: " << city2 << " doesn't exist\n";
		validInput = false;
	}

	// ===  both exist :) add the road  ===
	if (validInput)
	{
		// keep the city to be connected to & distance in a pair holder
		pairHolder.first = city2;
		pairHolder.second = distance;

		// then add this pair holder to the linked list
		map.at(city1).push_back(pairHolder);

		pairHolder.first = city1;
		map.at(city2).push_back(pairHolder);
	}
}

/**
* deleteCity - Deletes a City
* @cityName: City Name to be deleted
*
* Description: if the city doesn't exist, it gives an Error Message
*			   else it removes the city vertex and the list of
*			   adjacent vertices
*
* Return: nothing
*/
void graph::deleteCity(string cityName, graph& myGraph)
{
	// erase city if exists otherwise, show message
	/*if (map.erase(cityName) != 1)
	{
		cout << "The city you have entered does not exist :(\n"
			<< "Make sure you wrote the name right\n";
		return;
	}*/
	//
	if (!checkCity(cityName, myGraph))
	{
		cout << "The city you have entered does not exist :(\n"
			<< "Make sure you wrote the name right\n";
		return;
	}
	else
	{
		// delete adjacent cities
		list<pair <string, float>> adjacent;
		getAdjacentList(cityName, adjacent);
		for (listIterator = adjacent.begin(); listIterator != adjacent.end(); listIterator++)
		{
			deleteRoad(cityName, listIterator->first , myGraph);
		}

	}

	// remove city 
	map.erase(cityName);

	// decrement number of cities
	vertexNum--;
}

/**
* deleteRoad - deletes a road between 2 cities
* @city1: first city
* @city2: second city
*
* Description: first makes sure that cities exist. if so,
*			   it searches in city1 connections for city2,
*			   if it isn't there, gives a message NO edge between them
*			   else (it's there), it deletes it
*
*			   note: it assumes the graph is undirected
*
* Return: nothing
*/
void graph::deleteRoad(string city1, string city2, graph & myGraph)
{
	// if at least one city doesn't exist
	if (map.find(city1) == map.end())
	{
		cout << city1 << " doesn't exist :|\n";
		return;
	}
	else if (map.find(city2) == map.end())
	{
		cout << city2 << " doesn't exist :|\n";
		return;
	}
	else // cities exist. Search for city2 in city1 connections
	{
		
		
		// if there is no road give an error message
		if (!checkEdge(city1, city2, myGraph))
		{
			cout << "Ther is no road between " << city1 << " and " << city2 << endl;
			return;
		}


		// search for city 2 in city 1 connections and delete it
		for ( listIterator =map.at(city1).begin(); listIterator != map.at(city1).end(); listIterator++)
			if (listIterator->first == city2)
			{
				map[city1].erase(listIterator);
				break;
			}
		
		// search for city 1 in city 2 connections and delete it
		for ( listIterator = map.at(city2).begin(); listIterator != map.at(city2).end(); listIterator++)
			if (listIterator->first == city1) 
			{
				map[city2].erase(listIterator);
				break;
			}
				
		
	}
}


void graph::display()
{
	cout << "\n The elements in this Graph are: \n";
	//display the key value once
	for (mapIterator = map.begin(); mapIterator != map.end(); mapIterator++)
	{
		// itr works as a pointer to 
		// itr->first stores the key part and
		// itr->second stores the value part

		cout << "City: " << mapIterator->first << endl;
		cout << "Adjacent cities are: " << endl;


		//display the linked list compmnents "the value of the map's key"
		for (listIterator = mapIterator->second.begin(); listIterator != mapIterator->second.end(); ++listIterator)
		{
			cout << (*listIterator).first << " ( Distance =  " << (*listIterator).second << " )" << endl;
		}
		cout << "\t\t\t=======================================================================" << endl;
	}
}


//DINA AND MAYAR
/**
* getAdj - gives the adjacency list of the given node
* @city: the city to get its adjaceny list
* @adj: a list that to point to the desired list
*
* Return: nothing
*/
void graph::getAdjacentList(string city, list<pair <string, float>>& adj) {
	mapIterator = map.find(city);
	adj = mapIterator->second;
}

/**
 * Checks if a city with the given name exists in the graph.
 *
 * @param cityName The name of the city to check.
 * @return True if a city with the given name exists in the graph, false otherwise.
 */
bool graph::checkCity(string cityName, graph& myGraph) {
	for (mapIterator = map.begin(); mapIterator != map.end(); mapIterator++) {
		if (cityName == mapIterator->first) {
			return true;
		}
		return false;
	}
}

/**
 * Checks if an edge between two cities with the given names exists in the graph.
 *
 * @param city1 The name of the first city.
 * @param city2 The name of the second city.
 * @return True if an edge between the two cities exists in the graph, false otherwise.
 */
bool graph::checkEdge(string city1, string city2, graph & myGraph){
   list<pair <string, float>> adjacent;
   getAdjacentList(city1, adjacent);
   for (listIterator = adjacent.begin(); listIterator != adjacent.end(); listIterator++) {
	   if (city2 == listIterator->first)
		   return true;
   }
   return false;
}

graph :: ~graph()
{
	map.clear();
}