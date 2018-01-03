#ifndef Graph_H_INCLUDED
#define Graph_H_INCLUDED
#include <list>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <random>
#include <time.h>
#include "BinaryHeap.h"
using namespace std;

size_t LineCount(ifstream &graphFile);
void EdgeDefine(const string &line, int &start, int &end, float &weight);

class vertex{
    friend class Graph;
    public:
        vertex(int name): name_{name}{};
        vertex():name_{0}{};
        bool operator < (vertex &right);
    private:
        int name_;
        map<vertex*, double> adjacent_;
        bool checked_ = false;
        double distance_ = 9999;
        vertex* previous_ = nullptr;
};

class Graph{
    public:
        explicit Graph(ifstream &graphFile);
        explicit Graph(int maxNodes);
        double shortestpath(int A, int B);
        void print(unsigned int start);
        void GetOutDeg(unsigned int &min, unsigned int &max, double &avg);
        void InsertConnection(int a, int b);
        vertex* Find(int name);
        double GetWeight(int a, int b);
        vertex* Input (int name);
    private:
        void shortestpath(vertex &PointA, vertex &PointB, vertex*prev, double & current, double & best);
        void GetAllDistances(vertex &PointA);
        list<vertex> graph_;
        int totalConnections_;
};

bool vertex::operator<(vertex &right){
    return (this->distance_ < right.distance_)?true:false;
}

Graph::Graph(ifstream &graphFile){
    totalConnections_ = 0;
    if (!graphFile.is_open())
        throw std::ios_base::failure("Graph file unable to open");
    string line;
    while (std::getline(graphFile, line)){
        stringstream broken(line);
        int start = 0, stop = 0;
        double weight = 0;
        //takes first element of the line as the vertex name
        broken >> start;
        vertex* connect, *current = Input(start);
        while(broken >> stop  && broken >> weight){
            connect = Input(stop);
            current->adjacent_.insert(pair<vertex*, double>(connect, weight));
            totalConnections_++;
        }
    }
    graphFile.close();
}

Graph::Graph(int maxNodes){
    totalConnections_ = 0;
    vertex temp(0);
    for (int i = 0; i < maxNodes; i++){
        temp.name_ = i;
        graph_.push_back(temp);
    }
}

vertex* Graph:: Input(int name){
    vertex temp(name);
    if (graph_.size() == 0){
        graph_.push_back(temp);
        return &(*graph_.begin());
    }
    auto i = graph_.begin();
    while (i != graph_.end() && (*i).name_ != name){
        if (name < (*i).name_){
            graph_.insert(i, temp);
            --i;
            break;
        }
        ++i;
    }

    //cout << "INPUT " << name << "= " << (*i).name_ << endl;
    return &(*i);
}
vertex* Graph:: Find(int name){
    auto i = graph_.begin();
    while (i != graph_.end() && (*i).name_ != name){i++;}
    if ((*i).name_ != name)
        return nullptr;
    return (&*i);
}


double Graph::GetWeight(int pointA, int pointB){
    auto i = graph_.begin();
    while (i != graph_.end() && (*i).name_ != pointA){i++;}
    if ((*i).name_ != pointA)
        return -1;
    //if no pointA, then return -1
    //search in pointA for pointB
    for(auto j = (*i).adjacent_.begin(); j != (*i).adjacent_.end(); j++){
        //cout << j->first->name_ << " " << j->second << endl;
        if(j->first->name_ == pointB)
            return j->second;
    }
    return -1;
}


void Graph::GetAllDistances(vertex &PointA){
    //a small struct, basically meant to copy a pair in a map
    struct Connection{
        Connection(vertex* inVert, double inDist): vert{inVert}, weight{inDist}{}
        bool operator < (Connection right){return this->weight < right.weight?true:false;}
        Connection():vert{nullptr},weight{9999}{}
        vertex* vert;
        double weight;
    };

    BinaryHeap<Connection> nextFocus(totalConnections_);
    PointA.distance_ = 0;
    vertex* focus = &PointA;

    do{
        if(focus != &PointA){
            if (nextFocus.isEmpty())
                return;
            nextFocus.deleteMin();
        }

        cout << "focus is now at: " << focus->name_ << endl;
        focus->checked_ = true;

        //for every pair within the adjacency map
        for( auto itr : focus->adjacent_){
            cout << "Comparing with " << itr.first->name_ << " distance is " << itr.first->distance_ << endl;
            //if the total distance is less than the distance set on the vertex
            if (focus->distance_ + itr.second < itr.first->distance_){
                //make the lesser distance the current distance
                itr.first->distance_ =  focus->distance_ + itr.second;
                itr.first->previous_ = focus;
                //insert the connection into the min heap as a possible next focus.
                Connection tempConnection(itr.first, itr.second);
                nextFocus.insert(tempConnection);
                cout << "we found a lower distance, vertex " << itr.first->name_ << " now has distance " <<itr.first->distance_ << endl;
            }
        }

        if (!nextFocus.isEmpty())
            focus = nextFocus.findMin().vert;
    }while(!nextFocus.isEmpty());
    //continue until no costs other than 9999


}



void Graph::print(unsigned int startname){
    vertex* start = Find(startname);
    if (start == nullptr)
        throw std::runtime_error("Argument node not in graph");

//    for(auto i : graph_){
//        cout << i.name_ << "\t" << i.checked_ << "\t" << i.distance_ << endl;
//    }
//    cout << "--------------------------" << endl;

//    for(auto i : graph_){
//        if (i.checked_ == false)
//            shortestpath(start, i.name_);
//    }
    GetAllDistances(*start);
    for (auto i : graph_){
        cout << i.name_ << ": ";
        for(auto j : i.adjacent_){
            cout << '\t' << j.first->name_ << endl;
        }
    }


    for (auto i : graph_){
        cout << i.name_ << ": ";
        vertex* v = &i;
        if(v->distance_ == 9999){
            cout <<"No path." << endl;
            continue;//return;
        }
        stack<int> storage;
        while(v != nullptr){
            storage.push(v->name_);
            v = v->previous_;
        }
        while(storage.size() != 0){
            cout << storage.top() << ", ";
            storage.pop();
        }
        int x = i.distance_;
        cout << "Cost: " << x << endl;//i.distance_ << endl;
    }
}

void Graph::InsertConnection(int A, int B){
    vertex *v1, *v2;
    v1 = Find(A);
    v2 = Find(B);
    v1->adjacent_.insert(pair<vertex*, double>(v2, 1));
    ++totalConnections_;
}

void Graph::GetOutDeg(unsigned int &min, unsigned int &max, double &avg){
    min = 9999999; max = 0; avg = 0;
    for (auto i : graph_){
        if (i.adjacent_.size() < min)
            min = i.adjacent_.size();
	if (i.adjacent_.size() > max)
            max = i.adjacent_.size();
    }
    avg = (totalConnections_ / (double)graph_.size()) /2;
    return;
}


#endif // Graph_H_INCLUDED
