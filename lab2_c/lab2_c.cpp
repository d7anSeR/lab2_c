#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <conio.h>
#include <chrono>
#include <iostream>
#include<vector>
using namespace std;
struct stats 
{
	size_t comparison_count = 0;
	size_t copy_count = 0;
};
stats shell_sort(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2)
{
	stats flag;
	int n = 0;
	std::vector<int>::iterator temp = iter1;
	while (temp <= iter2)
	{
		n++;
		++temp;
	}
	int i = 0, j = 0, step = 0;
	for (step = n / 2; step > 0; step /= 2)
	{
		for (i = step; i < n; i++)
		{
			int tmp = *(iter1 + i - 1);
			for (j = i; j >= step; j -= step)
			{
				if (tmp < *(iter1 + j - step))
					iter1 + j = iter1 + j - step;
				else
					break;
			}
			*(iter1 + j) = tmp;
		}
	}
	std::vector<int>::iterator tmp3 = iter1;
	while (tmp3 <= iter2)
	{
		cout << *tmp3 << endl;
		++tmp3;
	}
	return flag;
}

stats selection_sort(std::vector<int>:: iterator iter1, std::vector<int>::iterator iter2)
{
	stats flag;
	while(iter1 <= iter2)
	{
		flag.comparison_count += 2;
		std::vector<int>::iterator small_ = iter1;
		if (iter1 != iter2)
		{
			std::vector<int>::iterator iter_ = iter1 + 1;
			while (iter_ <= iter2)
			{
				flag.comparison_count += 2;
				if (*iter_ < *small_)
				{
					small_ = iter_;
				}
				++iter_;
			}
			flag.comparison_count++;
		}
		iter_swap(iter1, small_);
		flag.copy_count++;
		cout << *iter1 << endl;
		++iter1;
	}
	flag.comparison_count++;
	return flag;
}
int main() 
{
	std::vector<int> numbers = { 15, 0, 1, 18, 94, 22, 43, 1010, 32, 14, 16, 19};
	auto iter1{ numbers.begin() };
	auto iter2{ numbers.end() - 1};  
	/*selection_sort(iter1, iter2);*/
	shell_sort(iter1, iter2);
}
