#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

class Graph {

public:
    Graph(int V);
    void Edge(int v, int w);
    Graph Transpose();
    void Kosaraju(vector<int> &SCC);
    void DAG(vector<int> &SCC);

private:
    int V;
    list<int> *adj;
    void StackDFS(int v, bool visited[], stack<int> &Stack);
    void DFS(int v, bool visited[],vector<int> &SCC);
    int getGroup(int v, vector<int> &SCC);
    void getMaxDegree0(int V);
};
#endif

