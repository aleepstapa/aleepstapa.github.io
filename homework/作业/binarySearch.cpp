#include <iostream>  
#include <fstream>  
#include <vector>  
#include <algorithm>  
#include <chrono>  

std::vector<int> read(const std::string &fileName, std::size_t limit) {  
	std::vector<int> numbers;  
	std::ifstream file(fileName);  
	
	if (file.is_open()) {  
		int number;  
		for (std::size_t i = 0; i < limit; ++i) {  
			if (!(file >> number)) {  
				break;  // End of file reached before limit  
			}  
			numbers.push_back(number);  
		}  
		file.close();  
	} else {  
		std::cout << "Unable to open the file." << std::endl;  
	}  
	return numbers;  
}
int binarySearch(std::vector<int>& nums, int target) {  
	int l = 0;  
	int r = nums.size() - 1;  
	while (l <= r) {  
		int mid = l + (r - l) / 2;  
		if (nums[mid] == target) {  
			return mid;  
		} else if (nums[mid] < target) {  
			l = mid + 1;  
		} else {  
			r = mid - 1;  
		}  
	}  
	return -1;  
}  
int spacel(int n) {  
	return static_cast<int>(n);  
}  
int main() {  
	auto start = std::chrono::high_resolution_clock::now();
	int a[7]={10000,100000,500000,1000000,2000000,5000000,10000000};
	int j=0;
	for(int i=a[j];i<=a[j],j<=6;i++,j++){
			std::vector<int> numbers = read("random_numbers.txt",i);
			std::sort(numbers.begin(), numbers.end());  
			int target = numbers[10];  
			binarySearch(numbers, target);  
			
			auto stop = std::chrono::high_resolution_clock::now();  
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);  
			int spac= spacel(a[j]) * sizeof(int); // 计算空间复杂度，单位：字节（byte）  

			
			std::cout <<a[j]<< "Time " << duration.count() << " ms" <<"Space"<<spac<<"byte"<< std::endl;  

	}
  
	return 0;  
}
