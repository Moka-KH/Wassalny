// DS_Mini_Waslny.cpp : This file contains the 'main' function. Program execution begins and ends there.
#pragma once
#include <iostream>
#include <string>
#include "graph.h"
#include "algorithms.h"
#include "consolUI.h"
#include <list>
#include <utility>
#include <unordered_map>
#include "GraphFileHandler.h"

using namespace std;
unordered_map<string, graph> maps;

int main() {
   maps=readMultipleGraphs(".\\");
    graph myGraph;
    vector<string> path;



    //test case for getadjacent
    myGraph.addCity("A");
    myGraph.addCity("B");
    myGraph.addCity("C");
    myGraph.addCity("D");
    myGraph.addCity("E");
    myGraph.addCity("F");
    myGraph.addCity("G");
    myGraph.addCity("H");
    myGraph.addCity("I");

    
    myGraph.addRoad("I", "A", 4);

    myGraph.addRoad("I", "C", 1);


    myGraph.addRoad("C", "D", 4);
    myGraph.addRoad("D", "C", 4);

    myGraph.addRoad("C", "E", 3);
    myGraph.addRoad("E", "C", 4);

    myGraph.addRoad("C", "F", 3);
   

    list<pair <string, float>> Adjacents;
    Adjacents=myGraph.getAdjacentVertices("C");
    for (auto& x : Adjacents) {
        cout << x.first <<" " << x.second<<"\n";
    }

    // test case of dikstra
  /*  myGraph.addCity("A");
    myGraph.addCity("B");
    myGraph.addCity("C");
    myGraph.addCity("D");
    myGraph.addCity("E");
    myGraph.addCity("F");


    myGraph.addRoad("A", "B", 2);
    myGraph.addRoad("A", "C", 4);
    myGraph.addRoad("B", "C", 1);
    myGraph.addRoad("B", "E", 2);
    myGraph.addRoad("B", "D", 4);
    myGraph.addRoad("C", "E", 3);
    myGraph.addRoad("E", "D", 3);
    myGraph.addRoad("E", "F", 2);
    myGraph.addRoad("D", "F", 3);

    Find(myGraph);*/





    /*float x;
    myGraph.addCity("Aaaa");
    myGraph.addCity("Bbbb");
    myGraph.addCity("Cccc");
    myGraph.addCity("Dddd");
    myGraph.addCity("Eeee");
    myGraph.addCity("Ffff");*/



    // Roads
    /*myGraph.addRoad("A", "F", 15);
    myGraph.addRoad("F", "B", 20);
    myGraph.addRoad("F", "K", 10);
    myGraph.addRoad("F", "D", 60);
    myGraph.addRoad("B", "X", 25);
    myGraph.addRoad("D", "X", 10);

    myGraph.addRoad("F", "A", 15);
    my-Graph.addRoad("X", "B", 30);*/
    /*
    // Back Roads
    myGraph.addRoad("F", "A", 15);
    myGraph.addRoad("B", "F", 20);
    myGraph.addRoad("K", "F", 10);
    myGraph.addRoad("D", "F", 60);
    myGraph.addRoad("X", "B", 25);
    myGraph.addRoad("X", "D", 10);

    myGraph.display();

    myGraph.deleteCity("F");
    cout << "\nDeleted the City F\n";

    myGraph.display();
    */
    //myGraph.display();
    
    /*list<pair<string, float>> myList;
    myGraph.getOutAdjacent("F", myList);
    cout << "\tOut Adjacents: \n";
    for (auto& listPair : myList)
        cout << listPair.first << " (" << listPair.second << ")\n";

    myList.clear();
    myGraph.getInAdjacents("F", myList);
    cout << "\tIn Adjacents: \n";
    for (auto& listPair : myList)
        cout << listPair.first << " (" << listPair.second << ")\n";

    myList.clear();
    myGraph.getAdjacentVertices("F", myList);
    cout << "\tAll Adjacents: \n";
    for (auto& listPair : myList)
        cout << listPair.first << " (" << listPair.second << ")\n";*/

    /*myGraph.deleteCity("X");
    myGraph.display();*/

    //intro(maps);
    return 0;
}
