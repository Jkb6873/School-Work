#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Graph.h"
#include "DisjSets.h"
using namespace std;


void LoadGraph(Graph &graphObj, int numObj);

int main(int argc, char *argv[]){
    try{
    if (argc != 2){
       throw std::runtime_error(
       "Improper usage of program. Correct usage:\n/TestRandomGraph <max size>");
    }
    int maxNodes = atoi(argv[1]);
    Graph graphObj(maxNodes);
    LoadGraph(graphObj, maxNodes);
    int maxOut, minOut;
    double avgOut;
    graphObj.GetOutDeg(minOut, maxOut, avgOut);

    cout << "Smallest Out-degree for a vertex: " << minOut << endl
         << "Largest Out-degree for a vertex: " << maxOut << endl
         << "Average Out-degree for a vertex: " << avgOut << endl;

    } catch (std::ios_base::failure &e){
        std::cerr << e.what() << std::endl;
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    } catch (...){
        std::cerr << "Unnamed Error\n" << std::endl;
    }
}

void LoadGraph(Graph &graphObj, int numObj){
    DisjSets connectivitySet(numObj);
    srand(time(0));
    int in1, in2, roots;
    do{
        in1 = rand() % numObj;
        in2 = rand() % numObj;
        if (!connectivitySet.unionSets(in1, in2))
            continue;
        graphObj.InsertConnection(in1, in2);
        graphObj.InsertConnection(in2, in1);
        roots = connectivitySet.GetRoots();
    }while (roots > 1);
    return;
}
