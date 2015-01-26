// colorcmb.cpp : Defines the entry point for the console application.
//

#include <cmath>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>

bool cmp(std::set<long> a, std::set<long> b) {
	return (a.size() < b.size());
}

int recAdd(std::set<long>& nums, int n, int r, int num, long* arr, int sz) {
	int cmbTot = 0;
	for (int i = n; i >= r; --i) {
		arr[r - 1] = *std::next(nums.begin(), i-1);
		if (r > 1) {
			cmbTot += recAdd(nums, i - 1, r - 1, num, arr, sz);
		}
		else {
			long total = 0;
			for (int i = 0; i < sz; ++i) {
				//std::cout << "array " << arr[i] << std::endl;
				total += arr[i];
			}
			if (total == num) {
				cmbTot += 1;
				//return 1;
			}
			else {
				//return 0;
			}
		}
	}
	//std::cout << cmbTot << std::endl;
	return cmbTot;
}

void test() {
	std::set<long> nums;
	nums.insert(1);
	nums.insert(2);
	nums.insert(3);
	long* arr = new long[2];
	std::cout << recAdd(nums, nums.size(), 2, 5, arr, 2);
	delete[] arr;
}

int main(int argc, char** argv) {
	const int thr = 12;
	const int numsLen = 7;
	unsigned long max = std::pow(2, thr);
	std::set<std::set<long>> combs;
	std::ofstream file;
	file.open("output.txt");
	std::cout << pow(2, thr) << std::endl;
	file << pow(2, thr) << std::endl;
	
	for (unsigned long i = 1; i < max; ++i) {
		std::set<long> nums;
		nums.insert(i);
		for (unsigned long j = i; j < max; ++j) {
			int total = 0;
			for (int k = nums.size(); k >= 1; --k) {
				long* arr = new long[k];
				total += recAdd(nums, nums.size(), k, j, arr, k);
				delete[] arr;
				//std::cout << k << std::endl;
			}
			if (total == 0) {
				int numTot = j;
				for (auto &x : nums) {
					numTot += x;
				}
				if (numTot <= max) {
					nums.insert(j);
				}
			}
		}
		if (nums.size() > numsLen) {
			combs.insert(nums);
			for (auto &x : nums) {
				std::cout << x << ",";
				file << x << ",";
			}
		}
		//if (i % 100 == 0) {
			std::cout << "at iteration: " << i << std::endl;
		//}
	}
    

	//for (unsigned long i = 0; i < max; ++i) {
	//	std::set<long> nums;
	//	nums.insert(i);
	//	for (unsigned long j = i; j < max; ++j) {
	//		if (i != j) {
	//			//if ((i + j != i) &&
	//			//(i + j != j) &&
	//			//(std::find(nums.begin(), nums.end(), (i+j)) == nums.end())){
	//			bool found = false;
	//			for (auto &x : nums) {
	//				for (auto &y : nums) {
	//					if (x != y) {
	//						if (x + y == j) {
	//							found = true;
	//							break;
	//						}
	//					}
	//				}
	//				if (found) break;
	//			}
	//			long total = 0;
	//			for (auto &x : nums) {
	//				total += x;
	//			}
	//			if (total + j > max) {
 //                   // no point in continuing, subsequent numbers are greater
	//				break;
	//			}
	//			if (!found) {
	//				nums.insert(j);
	//			}
	//			//}
	//		}
	//	}
	//	if (nums.size() > numsLen) {
	//		combs.insert(nums);
	//	}
	//}
	
	std::cout << combs.size() << std::endl;
	file << combs.size() << std::endl;
	for (auto &comb : combs) {
		for (auto &x : comb) {
			std::cout << x << ",";
			file << x << ",";
		}
		std::cout << std::endl;
		file << std::endl;
	}
	auto maxNums = std::max_element(combs.begin(), combs.end(), cmp);
	std::cout << "max vec: " << (*maxNums).size() << std::endl;
	file << "max vec: " << (*maxNums).size() << std::endl;
	for (auto &x : (*maxNums)) {
		std::cout << x << ",";
		file << x << ",";
	}

	std::cout << std::endl;
	file << std::endl;
	file.close();
   
}
