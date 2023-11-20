#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

void merge(std::vector<int>& arr, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;
	std::vector<int> L(n1);
	std::vector<int> R(n2);
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(std::vector<int>& arr, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

int main() {
	std::vector<int> arr;
	std::ofstream outputFile("merge_sort_results.csv");
	
	// Write CSV header
	outputFile << "Data Size,Time Complexity,Space Complexity" << std::endl;
	
	// Test different data sizes
	for (int dataSize : {10000, 100000, 500000, 1000000, 2000000, 10000000}) {
		arr.resize(dataSize);
		
		// Generate random data for testing
		for (int i = 0; i < dataSize; ++i) {
			arr[i] = rand();
		}
		
		// Measure time complexity
		auto start_time = std::chrono::high_resolution_clock::now();
		mergeSort(arr, 0, dataSize - 1);
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		
		// Measure space complexity
		int space_complexity = sizeof(int) * dataSize;
		
		// Write data to CSV
		outputFile << dataSize << "," << duration.count() << "," << space_complexity << std::endl;
	}
	
	outputFile.close();
	
	return 0;
}

