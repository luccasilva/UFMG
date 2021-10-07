#include "Graph.h"

Graph::Graph(int V, int E){
    this->V = V;
	this->E = E;
    adj = new list<int>[V];
}

void Graph::AddEdge(int v, int w){
	// cria a aresta em ambas as direções
    adj[v].push_back(w);
	adj[w].push_back(v);

	Edge Edge;
	Edge.x = v;
	Edge.y = w;
	Edge.visited = false;

	// lista a aresta para solução da tarefa 2
	edgesList.push_back(Edge);
}

// função para verificar o funcionamento da lista
void Graph::PrintEdge(){
	for (int x = 0; x<E; x++){
        std::cout << edgesList[x].x-1 << " * " << edgesList[x].y-1 << std::endl;
    }
}

void Graph::dfs(vector<int> decisionVector[], int src,int par){
	for (auto vAdj : adj[src]) {
		if (vAdj != par)
			dfs(decisionVector, vAdj, src);
	}
	// para cada vértice do grafo seguindo a ordem da dfs
	// decide se inclúi ou não o vértice no conjunto solução
	for (auto vAdj : adj[src]) {
		if (vAdj != par) {
			decisionVector[src][0] += decisionVector[vAdj][1];
			decisionVector[src][1] += min(decisionVector[vAdj][1], decisionVector[vAdj][0]);
		}
	}
}

//função que desempenha a tarefa 1
void Graph::minimalVertexCover(){
	vector<int> decisionVector[V];

	for (int i = 1; i < V; i++) {
		// decisão de não incluir no conjunto solução
		decisionVector[i].push_back(0);

		// decisão de incluir no conjunto solução
		decisionVector[i].push_back(1);
	}

	dfs(decisionVector, 1, -1);
	cout << min(decisionVector[1][0], decisionVector[1][1]) << endl;
}

//função que desempenha a tarefa 2
void Graph::aproxMinimalVertexCover(){

	vector<Edge> SolutionList;
	int x,y,Sx,Sy;

	//para toda aresta do grafo, coloca uma aresta no conjunto solução
	for (auto & element : edgesList){
		if (element.visited == false){
			element.visited = true;
			SolutionList.push_back(element);
			x = element.x;
			y = element.y;
		}
		//retira as arestas adjacentes do conjunto para continuar o algoritimo
		for (auto & edge : edgesList){
  			Sx = edge.x;
			Sy = edge.y;

			if (edge.visited == false && (x == Sx || y == Sy || x == Sy || y == Sx)){
					edge.visited = true;
			}
		}
	}

	int vertices = SolutionList.size()*2;

	vector<int> solution;

	//lista todos os vértices que fazem parte do conjunto solução
	for (auto & element : SolutionList){
		solution.push_back(element.x-1);
		solution.push_back(element.y-1);
	}

	//trata os vértices que não possuem nenhuma ligação
	for (int v = 1; v < V; v++){
        if(adj[v].size()==0){
			vertices = vertices + 1;
			solution.push_back(v-1);
		}
    }

	cout << vertices << endl;

	for (auto & element : solution){
		cout << element << endl;
	}
}