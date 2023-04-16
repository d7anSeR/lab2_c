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
void print_mass(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2)
{
	std::vector<int>::iterator t = iter1;
	while (t <= iter2)
	{
		cout << *t << endl;
		++t;
	}
}
void heapify(std::vector<int>::iterator it1, std::vector<int>::iterator it2, int i) 
{
	int n = it2 - it1;
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && *(it1 + l) > *(it1 + largest)) 
		largest = l;
	if (r < n && *(it1 + r) > *(it1 + largest)) 
		largest = r;
	if (largest != i) 
	{
		std::swap(*(it1 + i), *(it1 + largest));
		heapify(it1, it2, largest);
	}
}
stats heap_sort(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2) 
{
	stats flag;
	int n = iter2 - iter1;
	std::vector<int>::iterator it = iter1;
	for (int i = n / 2 - 1; i >= 0; i--) 
	{
		heapify(it, iter2, i);
	}
	for (int i = n - 1; i >= 0; i--) 
	{
		std::swap(*(it), *(it + i));
		heapify(it, it + i, 0);
	}
	print_mass(iter1, iter2);
}

stats shell_sort(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2)
{
	stats flag;
	int n = iter2 - iter1 + 1;
	for (int step = n / 2; step > 0; step /= 2) 
	{
		std::vector<int>::iterator temp1 = iter1, temp2 = iter1, temp3 = iter1;
		for (temp1 += step; temp1 <= iter2; temp1++)
		{
			int temp = *(temp1);
			flag.copy_count++;
			for (temp2 = temp1; temp2 >= temp3 + step && *(temp2 - step) > temp; temp2 -= step) 
			{
				*(temp2) = *(temp2 - step);
			}
			*(temp2) = temp;
		}
	}
	print_mass(iter1, iter2);
	return flag;
}

stats selection_sort(std::vector<int>:: iterator iter1, std::vector<int>::iterator iter2)
{
	stats flag;
	std::vector<int>::iterator tmp = iter1;
	while(tmp <= iter2)
	{
		std::vector<int>::iterator small_ = tmp;
		if (tmp != iter2)
		{
			std::vector<int>::iterator iter_ = tmp + 1;
			while (iter_ <= iter2)
			{
				if (*iter_ < *small_)
				{
					small_ = iter_;
				}
				iter_++;
			}
		}
		iter_swap(tmp, small_);
		flag.copy_count++;
		tmp++;
	}
	print_mass(iter1, iter2);
	return flag;
}
int main() 
{
	std::vector<int> numbers = { 15, 0, 1, 18, 94, 22, 43, 1010, 32, 17, 16, 19, 2, 1019};
	auto iter1{ numbers.begin() };
	auto iter2{ numbers.end() - 1};
	selection_sort(iter1, iter2);
	cout << endl;
	shell_sort(iter1, iter2);
	cout << endl;
	heap_sort(iter1, iter2);
	cout << endl;
}
