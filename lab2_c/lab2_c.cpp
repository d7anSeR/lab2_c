#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include<vector>
using namespace std;
struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};
//class iter
//{
//private:
//	int value;
//public:
//	iter(int value):value(value) {}
//
//};

void selection_sort(std::vector<int>:: iterator iter1, std::vector<int>::iterator iter2)
{
	while(iter1 != iter2)
	{
		auto small{ &iter };
		auto iter (iter1 + 1);
		while (iter != iter2)
		{
			if (iter < small)
				small = iter;
			++iter;
		}
		std::swap(iter1, small);
		++iter1;
	}

}
int main() 
{
	std::vector<int> numbers{ 10, 20, 30, 40 };
	auto iter1{ numbers.begin() };
	auto iter2{ numbers.end() };  
	selection_sort(iter1, iter2)
	while (iter != numbers.end())
	{
		std::cout << *iter << std::endl;
		++iter;           
	}
	for (auto start{ numbers.begin() }; start != numbers.end(); start++)
	{
		std::cout << *start << std::endl;
	}

}
