/*
Copyright (c) 2015 C. D. Tharindu Mathew
http://mackiemathew.wordpress.com

This project is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see <http://www.gnu.org/licenses/agpl-3.0.html>.
*/

// colorcmb.cpp : Defines the entry point for the console application.
//

#include <cmath>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>

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
	const int numsLen = 1;
	unsigned long max = std::pow(2, thr);
	std::set<std::set<long>> combs;
	std::ofstream file;
	std::string fileName("output_" + std::to_string(thr) + ".txt");
	file.open(fileName, std::ios::app);
	std::cout << pow(2, thr) << std::endl;
	file << pow(2, thr) << std::endl;
	
	for (unsigned long i = 35; i < max; ++i) {
		std::set<long> nums;
		nums.insert(i);
		int lastNumInserted = 0;
		for (unsigned long j = i; (j < max && j < i + 60); ++j) {
			int total = 0;
			//std::cout << "n and k" << j << " " << nums.size() << " " << std::ceil(((nums.size() + 1) / 2));
			for (int k = nums.size(); k >= 1; k--) { 
			// int l = nums.size();
			//for (int k = nums.size(); k >= (l + 1)/2; k--) { // can't do this, even though the number is the same, the addition is different
				std::cout << k << " ";
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
					lastNumInserted = j;
					nums.insert(j);
				}
			}
			else {
				if ((lastNumInserted != 0) && (lastNumInserted + 1 <= j)) {
					break;
				}
			}
		}
		if (nums.size() > numsLen) {
			combs.insert(nums);
			for (auto &x : nums) {
				std::cout << x << ",";
				//file << x << ",";
			}
		}
			//file << "at iteration: " << i << std::endl;
			std::cout << "at iteration: " << i << std::endl;
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
	if (combs.size() > 0) {
		auto maxNums = std::max_element(combs.begin(), combs.end(), cmp);
		std::cout << "max vec: " << (*maxNums).size() << std::endl;
		file << "max vec: " << (*maxNums).size() << std::endl;
		for (auto &x : (*maxNums)) {
			std::cout << x << ",";
			file << x << ",";
		}
	}

	std::cout << std::endl;
	file << std::endl;
	file.close();
   
}
