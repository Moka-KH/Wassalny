#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <list>
#include <fstream>
#include "graph.h"
#include "enumerators.cpp"
#include "coloredOutput.cpp"

using namespace std;

/*
	* unordered_map Notes:
	* map.at() -> returns a pointer to the value
	* map.insert() -> adds a new key-value
	* map.find() -> return an iterator pointing to bucket value (the vertex in our case)
	*				if it exists and to the last vertex if it doesn't
	* map.erase() -> return 1 if found key and erase it otherwise return 0
*/

// Constructors & Destructor
graph::graph()
{
	vertexNum = 0;
	edgeNum = 0;
}
graph::graph(string name)
{
	graph();
	this->name = name;
}
graph :: ~graph()
{
	for (auto& bucket : map)
		bucket.second.clear();

	map.clear();
}

// Getters
/**
* @return integer value (#vertices number)
*/
int graph::getVertexNum()
{
	return vertexNum;
}
/*
* @return integer value (vertices number)
*/
int graph::getEdgeNum()
{
	return edgeNum;
}
/**
* get the number of out-edges of the given vertex
*
* @param city1 city name
* @return integer value (#edges)
*/
int graph::getOutEdgesNumber(string city1)
{
	int counter = 0;
	list<pair<string, float>> adjacents = getOutAdjacents(city1);

	for (auto& x : adjacents)
		counter++;
	return counter;
}
/**
 * Gets distance From City1 To City2 (directional)
 *
 * @param city1 The first city.
 * @param city2 The second city.
 * @return distance if an edge between the two cities exists in the graph, -1 otherwise.
 */
float graph::getEdgeWieght(string city1, string city2)
{
	list<pair <string, float>> adjacents = getOutAdjacents(city1);
	for (auto& listPair : adjacents)
		if (listPair.first == city2)
			return listPair.second;

	return -1;
}

/**
* returns the adjacency list of the given vertex
*
* @city: the city to get its adjaceny list
* @adj: a list that to point to the desired list
* @return the adjacency list
*/
list<pair <string, float>> graph::getOutAdjacents(string city)
{
	return map.at(city);
}
/**
* returns a list filled with the in-adjacents of the given vertex.
*
* @param city the city to get its in-adjacents
* @return
*/
list<pair <string, float>> graph::getInAdjacents(string city)
{
	list<pair <string, float>> adjacents;
	float backDistance;
	for (auto& bucket : map)
	{
		// if you find a road from any city to the city we're getting its in-adjacents
		if (edgeExists(bucket.first, city))
		{
			// get the distance from that city to to city we're getting its in-adjacents
			for (auto& listPair : bucket.second)
				if (listPair.first == city)
					backDistance = listPair.second;

			// add the founded city with its distance to the adjaceny list we're filling
			adjacents.push_back(make_pair(bucket.first, backDistance));
		}
	}
	return adjacents;
}
/**
* returns a list of all the adjacent vertices (in & out) of the given vertex
*
* @param city the city to get its adjacents
* Return: a list filled with the adjacents
*/
list<pair <string, float>> graph::getAdjacents(string city) // to be refactored
{
	list<pair <string, float>> outAdjacents, inAdjacents;

	// put the out-adjacents in a list
	outAdjacents = getOutAdjacents(city);

	// put the in-adjacents in a list
	inAdjacents = getInAdjacents(city);

	// combine them into inAdjacents and don't take the duplicates
	for (auto& x : inAdjacents)
	{
		for (auto y : outAdjacents)
		{
			// if you find a repeated value, don't take it.. continue to the next one
			if (x.first == y.first && x.second == y.second)
				break;
			// non-repeated value
			else
				inAdjacents.push_back(make_pair(y.first, y.second));
		}
	}

	outAdjacents.clear();
	return inAdjacents;
}

// Cities
/**
* @brief Adds a new City
* 
*
* it exits with an ineteger representing an error if the city already exists
* otherwise, it adds a vertex and its list in the map
* 
* @city City Name
* @return returns an addCity_enum according to the ending state (success / failure)
*/
int graph::addCity(string city)
{
	if (vertexExists(city))
		return cityExists;

	list <pair <string, float>> newList;
	map[city] = newList;
	vertexNum++;

	return success;
}
/**
* @brief Deletes a City
*
* if the city doesn't exist, it gives an Error Message
* else it removes the list of adjacent vertices
* and finally removes the node itself
*
* @cityName: City Name to be deleted
* @return void
*/
int graph::deleteCity(string cityName)
{
	if (!vertexExists(cityName))
	{
		return noCity;
	}

	list<pair<string, float>> adjacents;

	// delete connections with its out-adjacents
	adjacents = getOutAdjacents(cityName);
	for (auto& listPair : adjacents)
	{
		if (edgeExists(cityName, listPair.first) && edgeExists(listPair.first, cityName))
		{
			if (getEdgeWieght(cityName, listPair.first) != getEdgeWieght(listPair.first, cityName))
			{
				// delete city2 from the adjacency list of city1 
				// AND delete city1 from the adjacency list of city2
				deleteEdge(cityName, listPair.first);
				deleteEdge(listPair.first, cityName);
			}
			else
				deleteRoad(listPair.first, cityName);
		}
		else
			deleteRoad(listPair.first, cityName);

	}

	// delete connections with its in-adjacents
	adjacents = getInAdjacents(cityName);
	for (auto& listPair : adjacents)
		deleteRoad(listPair.first, cityName);

	// remove city
	map.erase(cityName);
	vertexNum--;

	return Cdeleted;
}

// Roads
/**
* This function connects adds / updates the distancde between 2 cities
* 
*
* Description: makes sure both of them exist.
*			   if so, adds the road
* @param city1 first city
* @param city2 second city
* @param distance Distance
* @return returns a addRoad_enum according to the ending state
*/
int graph::addEditRoad(string city1, string city2, float distance)
{
	// if the first one doesn't exist
	if (!vertexExists(city1))
		return noCity1;

	// if the second one doesnt exist
	if (!vertexExists(city2))
		return noCity2;

	// if the road already exists , just update the distance
	if (edgeExists(city1, city2))
	{
		for (auto& x : map.at(city1))
		{
			if (city2 == x.first)
			{
				x.second = distance;
				break;
			}
		}
		return updatedRoad;
	}

	// no road between them.. add it
	map.at(city1).push_back(make_pair(city2, distance));
	return addedRoad;
}
/**
* @brief This function deletes a road between 2 cities
* 
*
* first makes sure that cities exist. if so, it makes sure they're conncected.
* if so, it deletes the connection depending on its type (one way or roundway)
*
* @param city1 first city
* @param city2 second city
* @return void
*/
int graph::deleteRoad(string city1, string city2)
{
	// if at least one city doesn't exist
	if (!vertexExists(city1))
		return NoCity1;
	if (!vertexExists(city2))
		return NoCity2;

	// no road
	if(!edgeExists(city1, city2))
		return noRoad;
	// one way road from city1 to city2
	else if (edgeExists(city1, city2) && !edgeExists(city2, city1))
	{
		// delete city2 from the adjacency list of city1
		deleteEdge(city1, city2);
		return Rdeleted;
	}
	
	// one way road from city2 to city1
	else if (edgeExists(city2, city1) && !edgeExists(city1, city2))
	{
		// delete city1 from the adjacency list of city2
		deleteEdge(city2, city1);
		return Rdeleted;
	}
	
	// 2 way road
	else if (edgeExists(city1, city2) && edgeExists(city2, city1))
	{
		// with the same distance
		if (getEdgeWieght(city1, city2) == getEdgeWieght(city2, city1))
		{
			// delete city2 from the adjacency list of city1 
		    // AND delete city1 from the adjacency list of city2
			deleteEdge(city1, city2);
			deleteEdge(city2, city1);
			return Rdeleted;
		}
		// with different distances
		else
		{
			int choice;
			while (true)
			{
				cout << "1- delete road from " << city1 << " to " << city2 << "\n"
					<< "2- delete road from " << city2 << " to " << city1 << "\n"
					<< "3- delete  both roads \n";
				cin >> choice;

				if (choice == 1)
					deleteEdge(city1, city2);
				else if (choice == 2)
					deleteEdge(city2, city1);
				else if (choice == 3)
				{
					deleteEdge(city1, city2);
					deleteEdge(city2, city1);
				}
				else
				{
					cout << "Invalid choice!  Try agian\n";
					continue;
				}
				break;
			}
		}
	}
	
	return Rdeleted;
}
/*
* @brief deletes the edge going from city1 to city2
* @description a helper function for deleteRoad()
* it deletes the edge without any checking. Use it with caution
* 
* @return void
*/
void graph::deleteEdge(string city1,string city2) 
{
	for (auto listIterator = map.at(city1).begin(); listIterator != map.at(city1).end(); listIterator++)
	{
		if (listIterator->first == city2)
		{
			listIterator = map.at(city1).erase(listIterator);
			break;
		}
	}
}

// Boolean Checkers
/**
 * Checks if there is a city with the provided name or not
 * 
 * @cityName: The name of the city to check
 * @return True if a city with the given name exists, false otherwise.
 */
bool graph::vertexExists(string city)
{
	for (auto& bucket : map)
		if (city == bucket.first)
			return true;

	return false;
}
/**
 * Checks if there is an edge going from city1 to city2
 *
 * @param city1 the first city name
 * @param city2 the secondcity name
 * @return True if an edge between the two cities exists in the graph, false otherwise.
 */
bool graph::edgeExists(string city1, string city2)
{
	if (!vertexExists(city1) || !vertexExists(city2))
		return false;

	list<pair <string, float>> adjacents;
	adjacents = getOutAdjacents(city1);
	for (auto& listPair : adjacents)
		if (listPair.first == city2)
			return true;

	return false;
}
/**
* @brief checks if graph empty or not
* @return true if empty false if not
*/
bool graph::empty()
{
	if (map.empty())
		return true;
	return false;
}

/**
* displays the adjacency list of all the nodes in the graph
*
* @return void
*/
void graph::display()
{
	if (map.empty())
	{
		failureMessage("You don't have any cities in this map yet!");
		return;
	}

	cout << "\n\tMap Cities:\n";
	for (auto& bucket : map)
	{
		cout << "City: " << bucket.first << endl;

		for (auto& listPair : bucket.second)
			cout << '\t' << listPair.first << " ( Distance =  " << listPair.second << " )" << endl;

		cout << "\t\t\t=======================================================================" << endl;
	}
}