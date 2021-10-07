#include "Graph.h"

Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V];
}

void Graph::Edge(int v, int w){
    adj[v].push_back(w);
}

Graph Graph::Transpose(){
    Graph transposedGraph(V);
    for (int v = 0; v < V; v++){
        for(list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i){
            transposedGraph.adj[*i].push_back(v);
        }
    }
    return transposedGraph;
}

//Primeira DFS do Kosaraju, armazenando o caminhamento em uma pilha  
void Graph::StackDFS(int v, bool visited[], stack<int> &Stack){
    visited[v] = true;
  
    for(list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i){
        if(!visited[*i]){
            StackDFS(*i, visited, Stack);
        }
    }

    Stack.push(v);
}

//Segunda DFS do Kosaraju, realizada no grafo transposto, armazenando os SCC em um vetor
void Graph::DFS(int v, bool visited[], vector<int> &SCC){
    visited[v] = true;
    SCC.push_back(v);
  
    for (list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i){
        if (!visited[*i]){
            DFS(*i, visited, SCC);
        }
    }
}

//Algoritimo de Kosaraju, responsável por encontrar todos os SCC do grafo
void Graph::Kosaraju(vector<int> &SCC){
    stack<int> Stack;
  
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++){
        visited[i] = false;
    }
  
    for(int i = 0; i < V; i++){
        if(visited[i] == false){
            StackDFS(i, visited, Stack);
        }
    }
  
    Graph transposedGraph = Transpose();
  
    for(int i = 0; i < V; i++){
        visited[i] = false;
    }
  
    while (Stack.empty() == false){
        int v = Stack.top();
        Stack.pop();
  
        if (visited[v] == false){
            transposedGraph.DFS(v, visited, SCC);
            SCC.push_back(-1);
        }
    }
}

//Cria um DAG como representação do grafo original, onde os vértices de um SCC são representados como um vértice apenas
//Adiciona no novo grafo apenas as arestas entre SCCs diferentes
void Graph::DAG(vector<int> &SCC){

    int vectorSize = SCC.size();
    int count = 0;

    for (int i = 0; i < vectorSize; i++){
        if(SCC[i]==-1){
            count = count + 1;
        }
    }

    Graph DAG(count);

    //faz as conexoes somente entre grupos diferentes
    for (int v = 0; v < V; v++){

        int groupV = getGroup(v,SCC);

        for(list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i){

            int current = *i;
            int groupC = getGroup(current,SCC);

            if (groupV != groupC){
                DAG.Edge(groupV,groupC);
            }
        }
    }

    DAG.getMaxDegree0(count);

}

//Retorna qual o grupo de SCC o vértice está presente
int Graph::getGroup(int v, vector<int> &SCC){
    
    int vectorSize = SCC.size();
    int count = 0;

    for (int i = 0; i < vectorSize; i++){

        if(SCC[i]==v){
            return count;
        }

        else if(SCC[i]==-1){
            count = count + 1;
        }

    }

    return -1;
}

//Contabiliza quantos vértices no DAG tem grau de saída e de entrada = a 0
//Retorna o maior entre eles ( número de arestas minímas para que o grafo original seja fortemente conectado )
void Graph::getMaxDegree0(int V){

    int outputZeroDegree = 0;
    int inputZeroDegree = 0;

    for (int v = 0; v < V; v++){
        if(adj[v].size()==0){
            outputZeroDegree = outputZeroDegree + 1;
        }
    }

    vector<int> destinyComponents;
    int size = 0;

    for (int v = 0; v < V; v++){
        for(list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i){
            int ff = *i;
            destinyComponents.push_back(ff);
            size = size + 1;
        }
    }

    int flag = 0;

    for (int v = 0; v < V; v++){
        for (int x = 0; x < size; x++){
            if (v == destinyComponents[x]){
                flag = 1;
            }
        }
        if (flag == 0){
            inputZeroDegree = inputZeroDegree + 1;
        }
        flag = 0;
    }

    if (inputZeroDegree > outputZeroDegree){
        cout << inputZeroDegree << endl;
    }

    else if (inputZeroDegree < outputZeroDegree){
        cout << outputZeroDegree << endl;
    }

    else{
        cout << inputZeroDegree << endl;
    }
    
}