#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
	
	using namespace std;
	using namespace chrono;
	
	// 定义边的结构体
	struct Edge {
		long long src, dest, weight;
	};
	
	// 定义并查集的数据结构
	class DisjointSet {
	public:
		DisjointSet(int n) : parent(n), rank(n, 0) {
			for (int i = 0; i < n; ++i)
				parent[i] = i;
		}
		
		int find(int u) {
			if (u != parent[u])
				parent[u] = find(parent[u]);
			return parent[u];
		}
		
		void merge(int x, int y) {
			int rootX = find(x);
			int rootY = find(y);
			
			if (rank[rootX] > rank[rootY])
				parent[rootY] = rootX;
			else if (rank[rootX] < rank[rootY])
				parent[rootX] = rootY;
			else {
				parent[rootY] = rootX;
				rank[rootX]++;
			}
		}
		
	private:
		vector<int> parent;
		vector<int> rank;
	};
	
	// Kruskal算法
	int kruskal(vector<Edge>& edges, int V, int E, ofstream& outputFile) {
		auto start_time = high_resolution_clock::now();
		
		// 按权重升序排序所有边 
		sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
			return a.weight < b.weight;
			});
		
		// 创建并查集
		DisjointSet ds(V);
		
		// 存储最小生成树的边
		vector<Edge> result;
		
		for (const Edge& edge : edges) {
			int rootSrc = ds.find(edge.src);
			int rootDest = ds.find(edge.dest);
			
			// 判断是否形成环
			if (rootSrc != rootDest) {
				result.push_back(edge);
				ds.merge(rootSrc, rootDest);
			}
		}
		
		auto end_time = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end_time - start_time);
		
		cout << "数据规模: " << V << endl;
		cout << "Kruskal算法时间: " << duration.count() << " 毫秒" << endl;
		cout << "空间复杂度: " << V * sizeof(int) << " 字节" << endl;
		
		// 输出到CSV文件
		outputFile << V << "," << duration.count() << "," << V * sizeof(int) << "\n";
		
		return 0;
	}
		int main() {
			ofstream outputFile("kruskal_results.csv");
			outputFile << "数据规模,时间(ms),空间(bytes)\n";
			
			// 定义图的规模和边
			const int sizes[] = {100,1000,5000,10000};
			 
				for (int size : sizes) {
					int V = size;  // 顶点数
					int E = V * (V - 1) / 2;  // 边数，这里假设是一个完全图
					
					// 生成边的随机权重
					vector<Edge> edges;
					for (int i = 0; i < V; ++i) {
						for (int j = i + 1; j < V; ++j) {
							Edge edge;
							edge.src = i;
							edge.dest = j;
							edge.weight = rand() % 100;  // 随机权重
							edges.push_back(edge);
						}
					}
					
					kruskal(edges, V, E, outputFile);
				}
				
			
			
			outputFile.close();
			
			return 0;
		}

