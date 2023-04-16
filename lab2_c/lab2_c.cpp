//копии и сравнения посчитать
//графики нарисовать
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
    size_t comparison_count = 0, copy_count = 0, time = 0;    
    void operator+=(const stats& rhs)
    {
        comparison_count += rhs.comparison_count;
        copy_count += rhs.copy_count;
        time += rhs.time;
    }
};
void print_mass(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2)
{
	std::vector<int>::iterator t = iter1;
	while (t <= iter2)
	{
		cout << *t << "; ";
		++t;
	}
    cout << endl;
}
stats heapify(std::vector<int>::iterator it1, std::vector<int>::iterator it2, int i, stats flag) 
{
	int n = it2 - it1;
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
    flag.comparison_count++;
	if (l < n && *(it1 + l) > *(it1 + largest)) 
		largest = l;
    flag.comparison_count++;
	if (r < n && *(it1 + r) > *(it1 + largest)) 
		largest = r;
    flag.comparison_count++;
	if (largest != i) 
	{
        flag.copy_count++;
		std::swap(*(it1 + i), *(it1 + largest));
		flag = heapify(it1, it2, largest, flag);
	}
    return flag;
}
stats heap_sort(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2) 
{
	stats flag;
	int n = iter2 - iter1;
	for (int i = n / 2; i >= 0; i--) 
	{
        flag.comparison_count++;
		flag = heapify(iter1, iter2, i, flag);
	}
    flag.comparison_count++;
	for (int i = n; i >= 0; i--) 
	{
        flag.comparison_count++;
        flag.copy_count++;
		std::swap(*(iter1), *(iter1 + i));
		flag = heapify(iter1, iter1 + i, 0, flag);
	}
    flag.comparison_count++;
	return flag;
}

stats shell_sort(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2)
{
	stats flag;
	int n = iter2 - iter1 + 1;
	for (int step = n / 2; step > 0; step /= 2) 
	{
        flag.comparison_count++;
        flag.copy_count += 3; //?
		std::vector<int>::iterator temp1 = iter1, temp2 = iter1, temp3 = iter1;
		for (temp1 += step; temp1 <= iter2; temp1++)
		{
            flag.comparison_count++;
			int temp = *(temp1);
			flag.copy_count++;
			for (temp2 = temp1; temp2 >= temp3 + step && *(temp2 - step) > temp; temp2 -= step) 
			{
                flag.comparison_count++;
				*(temp2) = *(temp2 - step);
			}
            flag.comparison_count++;
			*(temp2) = temp;
		}
        flag.comparison_count++;
	}
    flag.comparison_count++;
	return flag;
}

stats selection_sort(std::vector<int>:: iterator iter1, std::vector<int>::iterator iter2)
{
	stats flag;
    flag.copy_count++;
	std::vector<int>::iterator tmp = iter1;
	while(tmp <= iter2)
	{
        flag.comparison_count += 2;
        flag.copy_count++;
		std::vector<int>::iterator small_ = tmp;
		if (tmp != iter2)
		{
            flag.copy_count++;
			std::vector<int>::iterator iter_ = tmp + 1;
			while (iter_ <= iter2)
			{
                flag.comparison_count += 2;
				if (*iter_ < *small_)
				{
                    flag.copy_count++;
					small_ = iter_;
				}
				iter_++;
			}
            flag.comparison_count++;
		}
		iter_swap(tmp, small_);
		flag.copy_count++;
		tmp++;
	}
    flag.comparison_count++;
	return flag;
}
size_t lcg() 
{
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}
stats selection_random(int n)
{
    stats result;
    for (int j = 0; j < 100; j++)
    {
        std::vector<int> mass;
        for (int i = 0; i < n; i++)
            mass.push_back(lcg());
        auto iter1{ mass.begin() };
        auto iter2{ mass.end() - 1 };
        auto start = std::chrono::high_resolution_clock::now();
        result += selection_sort(iter1, iter2);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        result.time += duration.count();
    }
    cout << "\t\tSELECTION SORT : ";
    cout << "length of random array - " << n << endl ;
    cout << "time: " << (double)result.time / 100 << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count / 100 << endl;
    cout << "copy count : " << result.copy_count / 100 << endl<< endl;
    return result;
}
stats selection_sorted(int n)
{
    stats result;
    std::vector<int> mass;
    for (int i = 0; i < n; i++)
    {
        mass.push_back(i);
    }
    auto iter1{ mass.begin() };
    auto iter2{ mass.end() - 1 };
    auto start = std::chrono::high_resolution_clock::now();
    result += selection_sort(iter1, iter2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    result.time += duration.count();
    cout << "\t\tSELECTION SORT : ";
    cout << "length of sorted array - " << n << endl;
    cout << "time: " << (double)result.time << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count << endl;
    cout << "copy count : " << result.copy_count << endl << endl;
    return result;
}
stats selection_reverse(int n)
{
    stats result;
    std::vector<int> mass;
    for (int i = n; i > 0; i--)
    {
        mass.push_back(i);
    }
    auto iter1{ mass.begin() };
    auto iter2{ mass.end() - 1 };
    auto start = std::chrono::high_resolution_clock::now();
    result += selection_sort(iter1, iter2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    result.time += duration.count();
    cout << "\t\tSELECTION SORT : ";
    cout << "length of reverse sorted array - " << n << endl;
    cout << "time: " << (double)result.time << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count << endl;
    cout << "copy count : " << result.copy_count << endl << endl;
    return result;
}


stats shella_random(int n)
{
    stats result;
    for (int j = 0; j < 100; j++)
    {
        std::vector<int> mass;
        for (int i = 0; i < n; i++)
            mass.push_back(lcg());
        auto iter1{ mass.begin() };
        auto iter2{ mass.end() - 1 };
        auto start = std::chrono::high_resolution_clock::now();
        result += shell_sort(iter1, iter2);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        result.time += duration.count();
    }
    cout << "\t\tSHELLA SORT : ";
    cout << "length of random array - " << n << endl;
    cout << "time: " << (double)result.time / 100 << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count / 100 << endl;
    cout << "copy count : " << result.copy_count / 100 << endl << endl;
    return result;
}
stats shella_sorted(int n)
{
    stats result;
    std::vector<int> mass;
    for (int i = 0; i < n; i++)
    {
        mass.push_back(i);
    }
    auto iter1{ mass.begin() };
    auto iter2{ mass.end() - 1 };
    auto start = std::chrono::high_resolution_clock::now();
    result += shell_sort(iter1, iter2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    result.time += duration.count();
    cout << "\t\tSHELLA SORT : ";
    cout << "length of sorted array - " << n << endl;
    cout << "time: " << (double)result.time << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count << endl;
    cout << "copy count : " << result.copy_count << endl << endl;
    return result;

}stats shella_reverse(int n)
{
    stats result;
    std::vector<int> mass;
    for (int i = n; i > 0; i--)
    {
        mass.push_back(i);
    }
    auto iter1{ mass.begin() };
    auto iter2{ mass.end() - 1 };
    auto start = std::chrono::high_resolution_clock::now();
    result += shell_sort(iter1, iter2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    result.time += duration.count();
    cout << "\t\tSHELLA SORT : ";
    cout << "length of reverse sorted array - " << n << endl;
    cout << "time: " << (double)result.time << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count << endl;
    cout << "copy count : " << result.copy_count << endl << endl;
    return result;
}




stats heap_sort_random(int n)
{
    stats result;
    for (int j = 0; j < 100; j++)
    {
        std::vector<int> mass;
        for (int i = 0; i < n; i++)
            mass.push_back(lcg());
        auto iter1{ mass.begin() };
        auto iter2{ mass.end() - 1 };
        auto start = std::chrono::high_resolution_clock::now();
        result += heap_sort(iter1, iter2);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        result.time += duration.count();
    }
    cout << "\t\tHEAP SORT : ";
    cout << "length of random array - " << n << endl;
    cout << "time: " << (double)result.time / 100 << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count / 100 << endl;
    cout << "copy count : " << result.copy_count / 100 << endl << endl;
    return result;
}
stats heap_sort_sorted(int n)
{
    stats result;
    std::vector<int> mass;
    for (int i = 0; i < n; i++)
    {
        mass.push_back(i);
    }
    auto iter1{ mass.begin() };
    auto iter2{ mass.end() - 1 };
    auto start = std::chrono::high_resolution_clock::now();
    result += heap_sort(iter1, iter2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    result.time += duration.count();
    cout << "\t\tHEAP SORT : ";
    cout << "length of sorted array - " << n << endl;
    cout << "time: " << (double)result.time << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count << endl;
    cout << "copy count : " << result.copy_count << endl << endl;
    return result;

}stats heap_sort_reverse(int n)
{
    stats result;
    std::vector<int> mass;
    for (int i = n; i > 0; i--)
    {
        mass.push_back(i);
    }
    auto iter1{ mass.begin() };
    auto iter2{ mass.end() - 1 };
    auto start = std::chrono::high_resolution_clock::now();
    result += heap_sort(iter1, iter2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    result.time += duration.count();
    cout << "\t\tHEAP SORT : ";
    cout << "length of reverse sorted array - " << n << endl;
    cout << "time: " << (double)result.time << " microseconds" << endl;
    cout << "comparison count : " << result.comparison_count << endl;
    cout << "copy count : " << result.copy_count << endl;
    return result;
}
void menu()
{
    system("cls");
    cout << "1. Selection sort" << endl;
    cout << "2. Shella sort" << endl;
    cout << "3. Heap sort" << endl;
    cout << "4. Tests" << endl;
    cout << "5. Finish the program" << endl;
    cout << "choice: ";
}
int main() 
{
    int choice = 0, ch = 0, choi = 0, val = 0;
    bool flag1 = true;
    std::vector<int> array = { 1, 2, 55, 32, -69, 0, 42, 1010, -515, 10, 11, 38, -8 };
    while (flag1)
    {
        menu();
        cin >> choice;
        std::vector<int> tmp = array;
        auto iter1{ tmp.begin() };
        auto iter2{ tmp.end() - 1};
        if (choice == 1 || choice == 2 || choice == 3)
        {
            cout << endl << "Old array: ";
            print_mass(iter1, iter2);
            if (choice == 1) selection_sort(iter1, iter2);
            if (choice == 2) shell_sort(iter1, iter2);
            if (choice == 3) heap_sort(iter1, iter2);
            cout << endl << "New array: ";
            print_mass(iter1, iter2);
            cout << endl << endl;
            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
        }
        else if (choice == 4)
        {
            selection_random(1000);
            selection_sorted(1000);
            selection_reverse(1000);
            cout << endl << endl;

            shella_random(1000);
            shella_sorted(1000);
            shella_reverse(1000);
            cout << endl << endl;

            heap_sort_random(1000);
            heap_sort_sorted(1000);
            heap_sort_reverse(1000);
            cout << endl << endl;

            selection_random(2000);
            selection_sorted(2000);
            selection_reverse(2000);
            cout << endl << endl;

            shella_random(2000);
            shella_sorted(2000);
            shella_reverse(2000);
            cout << endl << endl;

            heap_sort_random(2000);
            heap_sort_sorted(2000);
            heap_sort_reverse(2000);
            cout << endl << endl;

            selection_random(3000);
            selection_sorted(3000);
            selection_reverse(3000);
            cout << endl << endl;

            shella_random(3000);
            shella_sorted(3000);
            shella_reverse(3000);
            cout << endl << endl;

            heap_sort_random(3000);
            heap_sort_sorted(3000);
            heap_sort_reverse(3000);
            cout << endl << endl;

            selection_random(4000);
            selection_sorted(4000);
            selection_reverse(4000);
            cout << endl << endl;

            shella_random(4000);
            shella_sorted(4000);
            shella_reverse(4000);
            cout << endl << endl;

            heap_sort_random(4000);
            heap_sort_sorted(4000);
            heap_sort_reverse(4000);
            cout << endl << endl;

            selection_random(5000);
            selection_sorted(5000);
            selection_reverse(5000);
            cout << endl << endl;

            shella_random(5000);
            shella_sorted(5000);
            shella_reverse(5000);
            cout << endl << endl;

            heap_sort_random(5000);
            heap_sort_sorted(5000);
            heap_sort_reverse(5000);
            cout << endl << endl;

            selection_random(6000);
            selection_sorted(6000);
            selection_reverse(6000);
            cout << endl << endl;

            shella_random(6000);
            shella_sorted(6000);
            shella_reverse(6000);
            cout << endl << endl;

            heap_sort_random(6000);
            heap_sort_sorted(6000);
            heap_sort_reverse(6000);
            cout << endl << endl;

            selection_random(7000);
            selection_sorted(7000);
            selection_reverse(7000);
            cout << endl << endl;

            shella_random(7000);
            shella_sorted(7000);
            shella_reverse(7000);
            cout << endl << endl;

            heap_sort_random(7000);
            heap_sort_sorted(7000);
            heap_sort_reverse(7000);
            cout << endl << endl;

            selection_random(8000);
            selection_sorted(8000);
            selection_reverse(8000);
            cout << endl << endl;

            shella_random(8000);
            shella_sorted(8000);
            shella_reverse(8000);
            cout << endl << endl;

            heap_sort_random(8000);
            heap_sort_sorted(8000);
            heap_sort_reverse(8000);
            cout << endl << endl;

            selection_random(9000);
            selection_sorted(9000);
            selection_reverse(9000);
            cout << endl << endl;

            shella_random(9000);
            shella_sorted(9000);
            shella_reverse(9000);
            cout << endl << endl;

            heap_sort_random(9000);
            heap_sort_sorted(9000);
            heap_sort_reverse(9000);
            cout << endl << endl;

            selection_random(10000);
            selection_sorted(10000);
            selection_reverse(10000);
            cout << endl << endl;

            shella_random(10000);
            shella_sorted(10000);
            shella_reverse(10000);
            cout << endl << endl;

            heap_sort_random(10000);
            heap_sort_sorted(10000);
            heap_sort_reverse(10000);
            cout << endl << endl;

            selection_random(25000);
            selection_sorted(25000);
            selection_reverse(25000);
            cout << endl << endl;

            shella_random(25000);
            shella_sorted(25000);
            shella_reverse(25000);
            cout << endl << endl;

            heap_sort_random(25000);
            heap_sort_sorted(25000);
            heap_sort_reverse(25000);
            cout << endl << endl;

            selection_random(50000);
            selection_sorted(50000);
            selection_reverse(50000);
            cout << endl << endl;

            shella_random(50000);
            shella_sorted(50000);
            shella_reverse(50000);
            cout << endl << endl;

            heap_sort_random(50000);
            heap_sort_sorted(50000);
            heap_sort_reverse(50000);
            cout << endl << endl;

            selection_random(100000);
            selection_sorted(100000);
            selection_reverse(100000);
            cout << endl << endl;

            shella_random(100000);
            shella_sorted(100000);
            shella_reverse(100000);
            cout << endl << endl;

            heap_sort_random(100000);
            heap_sort_sorted(100000);
            heap_sort_reverse(100000);
            cout << endl << endl;

            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
        }
        else if (choice == 5)
            return 0;
        else
        {
            cout << "invalid character entered!!!!!!!    try again" << endl;
            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;
        }
    }
}
