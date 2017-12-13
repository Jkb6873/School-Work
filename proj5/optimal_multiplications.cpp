#include "MatMultiOrdering.h"

void ReadFile(std::vector<int>&input, std::string filename);

int main(int argc, char*argv[]){
    try{
    if (argc != 2){
       throw std::runtime_error(
       "Improper usage of program. Correct usage:\n/optimal_multiplications <dimensions_file>");
    }
    std::vector<int>matrices;
    ReadFile(matrices, argv[1]);
    MatMultiOrdering order(matrices);
    order.print();
    } catch (std::ios_base::failure &e){
        std::cerr << e.what() << std::endl;
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    } catch (...){
        std::cerr << "Unnamed Error\n" << std::endl;
    }
}

void ReadFile(std::vector<int>&input, std::string filename){
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
        throw std::ios_base::failure("Graph file unable to open");
    int line;
    while(file >> line)
        input.push_back(line);
    file.close();
    if (input.size() < 3)
        throw std::runtime_error("Incorrect format, not enough values in dimension file");
}
