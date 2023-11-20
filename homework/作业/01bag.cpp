#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

int k(int W, vector<int>& wt, vector<int>& val, vector<int>& dp) {
	int n = wt.size();
	
	for (int i = 1; i <= n; ++i) {
		for (int w = W; w >= wt[i - 1]; --w) {
			dp[w] = max(dp[w], val[i - 1] + dp[w - wt[i - 1]]);
		}
	}
	
	return dp[W];
}

void testAlgorithm(int dataSize, ofstream& outputFile) {
	vector<int> wt(dataSize, 1); // weights are all 1 for simplicity
	vector<int> val(dataSize, 1); // values are all 1 for simplicity
	int W = dataSize;
	
	vector<int> dp(W + 1, 0);
	
	auto start_time = high_resolution_clock::now();
	int result = k(W, wt, val, dp);
	auto end_time = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end_time - start_time);
	
	cout << "数据规模: " << dataSize << endl;
	cout << "最大价值: " << result << endl;
	cout << "所需时间: " << duration.count() << " 毫秒" << endl;
	cout << "空间复杂度: " << (W + 1) * sizeof(int) << " 字节" << endl;
	
	// 输出到CSV文件
	outputFile << dataSize << "," << duration.count() << "," << (W + 1) * sizeof(int) << "\n";
}

int main() {
	ofstream outputFile("results.csv");
	outputFile << "数据规模,时间(ms),空间(bytes)\n";
	
	
	testAlgorithm(500000, outputFile);
	testAlgorithm(1000000, outputFile);
	testAlgorithm(5000000, outputFile);
	
	outputFile.close();
	
	return 0;
}
