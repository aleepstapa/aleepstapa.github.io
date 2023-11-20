#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;
using namespace chrono;

// Graph representation (using adjacency list or matrix)
struct Graph {
	int V;
	vector<vector<pair<int, int>>> adj; // Pair: (weight, vertex)
	
	Graph(int V) : V(V), adj(V) {}
	
	void addEdge(int u, int v, int w) {
		adj[u].push_back({w, v});
		adj[v].push_back({w, u}); // For undirected graph
	}
	
	// Generate a random graph
	void generateRandomGraph(int E) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, V - 1), weightDis(1, 100);
		
		for (int i = 0; i < E; ++i) {
			int u = dis(gen);
			int v = dis(gen);
			int w = weightDis(gen);
			addEdge(u, v, w);
		}
	}
};

// Prim's algorithm
int prim(Graph& g) {
	vector<bool> selected(g.V, false);
	set<pair<int, int>> minHeap; // Pair: (weight, vertex)
	minHeap.insert({0, 0});
	
	int mstCost = 0;
	while (!minHeap.empty()) {
		auto [weight, u] = *minHeap.begin();
		minHeap.erase(minHeap.begin());
		
		if (selected[u]) continue;
		selected[u] = true;
		mstCost += weight;
		
		for (auto& [w, v] : g.adj[u]) {
			if (!selected[v]) minHeap.insert({w, v});
		}
	}
	return mstCost;
}

int main() {
	ofstream outputFile("results.csv");
	outputFile << "Vertices,Edges,Time(ms),Space(bytes)\n";
	
	int scales[] = {10000, 100000, 500000, 1000000, 2000000, 10000000};
	
	for (int vertices : scales) {
		// Assuming the number of edges is proportional to the number of vertices
		int edges = vertices * 2; 
		
		Graph g(vertices);
		g.generateRandomGraph(edges);
		
		auto start = high_resolution_clock::now();
		int mstCost = prim(g);
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		
		int spaceComplexity = sizeof(g) + (sizeof(vector<pair<int, int>>) * g.adj.size()); // Approximate space
		
		outputFile << vertices << "," << edges << "," << duration.count() << "," << spaceComplexity << "\n";
	}
	
	outputFile.close();
	return 0;
}
