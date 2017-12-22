#ifndef Graph_H_INCLUDED
#define Graph_H_INCLUDED
#include <list>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <random>
#include <time.h>
using namespace std;

size_t LineCount(ifstream &graphFile);
void EdgeDefine(const string &line, int &start, int &end, float &weight);

class vertex{
    friend class Graph;
    public:
        vertex(int name): name_{name}{};
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
        void print(int start);
        void GetOutDeg(int &min, int &max, double &avg);
        void InsertConnection(int a, int b);
        vertex* Find(int name);
        double GetWeight(int a, int b);
        vertex* Input (int name);
    private:
        void shortestpath(vertex &PointA, vertex &PointB, vertex*prev, double & current, double & best);
        list<vertex> graph_;
	int totalConnections_;
};

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
    //temp.weight_ = 1;
    for (int i = 0; i < maxNodes; i++){
        temp.name_ = i;
        graph_.push_back(temp);
    }
    //CreateConnections(maxNodes);
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

double Graph::shortestpath(int A, int B){
    vertex *v1, *v2;
    v1 = Find(A);
    v1->distance_ = 0;
    v2 = Find(B);
    double current = 0, best = 9999;
    shortestpath(*v1, *v2, v1->previous_, current, best);
    return best;
}


void Graph::shortestpath(vertex &PointA, vertex &PointB, vertex*prev, double & current, double & best){
    if (PointA.checked_ == true){
        if (current < PointA.distance_){
            PointA.distance_ = current;
            PointA.previous_ = prev;
        }
        return;
    }
    //if checked, ignore.
    if (PointA.name_ == PointB.name_){
        if (current < best)
            best = current;
        return;
    }
    //if we reach the final bit, overwrite best with current
    //going through each adjacent vertices

    PointA.checked_= true;
    double cost,  optimal = 9999;
    for( auto itr = (&PointA)->adjacent_.begin(); itr != (&PointA)->adjacent_.end(); itr++ ){
        vertex* t1 = itr->first;
        if (t1->distance_ > current + itr->second){
            t1->distance_ = current + itr->second;
            t1->previous_ = &PointA;
        }
        cost = t1->distance_;
        //now for each of these verticies, run the shortest path function.
        shortestpath(*t1,PointB,&PointA,cost,optimal);
    }
    if(optimal < best)
        best = optimal;
}

void Graph::print(int start){
    for(auto i : graph_){
        if (i.checked_ == false)
            shortestpath(start, i.name_);
    }
    for (auto i : graph_){
        cout << i.name_ << ": ";
        vertex* v = &i;
	if(v->distance_ == 9999){
            cout <<"No path." << endl;
            return;
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
        cout << "Cost: " << i.distance_ << endl;
    }
}

void Graph::InsertConnection(int A, int B){
    vertex *v1, *v2;
    v1 = Find(A);
    v2 = Find(B);
    v1->adjacent_.insert(pair<vertex*, double>(v2, 1));
    ++totalConnections_;
}

void Graph::GetOutDeg(int &min, int &max, double &avg){
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
