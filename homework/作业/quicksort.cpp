#include <iostream>  
#include <vector>  
#include <chrono>  
#include <fstream>  
#include <random>  
#include <cmath>  

using namespace std;  
// 计算划分  
int partition(vector<int>& arr, int low, int high) {  
	int pivot = arr[high];  
	int i = low - 1;  
	for (int j = low; j <= high - 1; j++) {  
		if (arr[j] <= pivot) {  
			i++;  
			swap(arr[i], arr[j]);  
		}  
	}  
	swap(arr[i + 1], arr[high]);  
	return i + 1;  
}  
// 快排函数  
void quicksort(vector<int>& arr, int low, int high) {  
	if (low < high) {  
		int pi = partition(arr, low, high);  
		quicksort(arr, low, pi - 1);  
		quicksort(arr, pi + 1, high);  
	}  
}  



// 生成随机数组  
vector<int> generateRandomArray(int size) {  
	random_device rd;  
	mt19937 gen(rd());  
	uniform_int_distribution<> distr(-1000000, 1000000);  
	vector<int> arr(size);  
	for (int i = 0; i < size; ++i) {  
		arr[i] = distr(gen);  
	}  
	return arr;  
}  

// 计算空间复杂度，对于快速排序来说，其空间复杂度为O(log n)  
int calculateSpaceComplexity(int n) {  
	return static_cast<int>(log2(n));  
}  

int main() {  
	// 设置数据量  
	vector<int> sizes = {10000, 100000, 500000, 1000000, 2000000, 5000000, 10000000};  
	// 打开文件输出数据  
	ofstream outfile("quicksort_results.csv");  
	outfile << "Size,Time(ms),Space(bytes)\n"; // 修改表头为毫秒和字节单位，更直观易懂  
	for (auto size : sizes) {  
		// 运行10次并计算平均值，注意调整数据类型避免溢出，时间单位改为毫秒，空间单位改为字节  
		double totalTime = 0.0; // 单位：毫秒  
		for (int i = 1; i <= 10; ++i) { // 从1开始方便计数  
			auto start = chrono::high_resolution_clock::now(); // 开始时间戳，单位：纳秒（ns）  
			vector<int> arr = generateRandomArray(size); // 生成随机数组，单位：字节（byte）  
			quicksort(arr, 0, size - 1); // 快速排序算法执行，传入数组和范围（下标）  
			auto end = chrono::high_resolution_clock::now(); // 结束时间戳，单位：纳秒（ns）  
			totalTime += chrono::duration_cast<chrono::milliseconds>(end - start).count(); // 计算时间差并累加，单位：毫秒（ms）  
			if (i == 1) { 
				int space = calculateSpaceComplexity(size) * sizeof(int); // 计算空间复杂度，单位：字节（byte）  
				outfile << size << "," << totalTime << "," << space << "\n"; // 写入CSV文件，以逗号分隔各个字段。时间单位为毫秒（ms），空间单位为字节（byte）。注意调整字段顺序以符合题目要求。使用"\n"换行。  
			} 
		}  
	}  
	outfile.close(); // 关闭CSV文件  
	return 0;  
}
