// DS_Mini_Waslny.cpp : This file contains the 'main' function. Program execution begins and ends there.
#pragma once
#include <iostream>
#include <string>
#include "graph.h"
#include "algorithms.h"
#include "homePage.h"
#include <list>
#include <utility>
#include <unordered_map>
#include "files.h"
#include "dashboard.h"
#include <queue>
#include <windows.h>
#include "coloredOutput.cpp"
#include <chrono>
#include <thread>
using namespace std;

unordered_map<string, graph> maps;

/**
* @brief This function saves changes to the files and print message to the use before the console is closed*
* @return void
*/
void closingFunction() 
{
    writeMultipleGraphs(maps, ".\\");
    successMessage("\t\t\t\t\t\t GOODBYE MI AMIGAS =)");
    std::this_thread::sleep_for(std::chrono::seconds(3));

}

int main() {
    SetConsoleTitle(TEXT("Mini Waslny =)"));

    /*  
        TO save changes when closing the console suddenly =)

        1-Create closingFunction() that save changes in files when the console is closed.
        2-Call the SetConsoleCtrlHandler(), it takes two parameters:
            * A pointer to a function that will be called when the (CTRL_CLOSE_EVENT) event occurs.
            * A Boolean value that specifies whether the function should be called recursively.
            * The expression (BOOL(__stdcall*)(DWORD)) is a function pointer declaration. 
              It declares a pointer to a function that takes a single parameter of type DWORD and returns a value of type BOOL.
              The __stdcall keyword specifies that the function should be called using the stdcall calling convention.
    */

    SetConsoleCtrlHandler((BOOL(__stdcall*)(DWORD))closingFunction, TRUE);

    maps = readMultipleGraphs(".\\");
    homePage(maps);


    return 0;
}


