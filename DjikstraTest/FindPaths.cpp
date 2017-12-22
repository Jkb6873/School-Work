#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Graph.h"
using namespace std;

//void GetPathLengths(Graph &graphObj, int start);

int main(int argc, char *argv[]){
    try{
    if (argc != 3)
        throw std::runtime_error(
        "Improper usage of program. Correct usage:\n/FindPaths <graph file> <starting vertex>");
    ifstream graphFile;
    graphFile.open(argv[1]);
    Graph graphObj(graphFile);
    int start = atoi(argv[2]);
    graphObj.print(start);
    } catch (std::ios_base::failure &e){
        std::cerr << e.what() << std::endl;
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    } catch (...){
        std::cerr << "Unnamed Error\n" << std::endl;
    }
}

