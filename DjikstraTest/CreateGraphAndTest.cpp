#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "Graph.h"
using namespace std;

void QueryList(Graph &graphObj, ifstream &queryFile);


int main(int argc, char *argv[]){
    try{
    if (argc != 3)
       throw std::runtime_error(
        "Improper usage of program. Correct usage:\n/CreateGraphAndTest <graph file> <query file>");
    ifstream graphFile, queryFile;
    graphFile.open(argv[1]);        //("Graph1.txt");
    queryFile.open(argv[2]);
    Graph graphObj(graphFile);
    QueryList(graphObj, queryFile);
    } catch (std::ios_base::failure &e){
        std::cerr << e.what() << std::endl;
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    } catch (...){
        std::cerr << "Unnamed Error\n" << std::endl;
    }

}

void QueryList(Graph &graphObj, ifstream &queryFile){
    if (!queryFile.is_open())
        throw std::ios_base::failure("Query file unable to open");
    string line;
    int pointA, pointB;
    float result;
    while(std::getline(queryFile, line)){
        stringstream divider(line);
        divider >> pointA;
        divider >> pointB;
        result = graphObj.GetWeight(pointA, pointB);
        cout << pointA << " " << pointB << " ";
        if (result == -1)
            cout << "Not Connected" << endl;
        else
            cout << "Connected, weight of edge is " << result << endl;
    }
    queryFile.close();
}


