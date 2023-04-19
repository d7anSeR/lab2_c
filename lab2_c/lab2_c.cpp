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
#include<fstream>

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
        flag.copy_count +=3;
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
        flag.copy_count += 3;
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
                flag.copy_count++;
			}
            flag.comparison_count++;
			*(temp2) = temp;
            flag.copy_count++;
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
		swap(*(tmp), *(small_));
		flag.copy_count += 3;
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
            std::vector<int> mass = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000};
            std::ofstream out1, out2;
            out1.open("selection_random_comparison.txt");   
            out2.open("selection_random_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = selection_random(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }
                
            }
            out1.close();
            out2.close();


            std::ofstream out1, out2;
            out1.open("selection_sorted_comparison.txt");
            out2.open("selection_sorted_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = selection_sorted(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();

            std::ofstream out1, out2;
            out1.open("selection_reverse_comparison.txt");
            out2.open("selection_reverse_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = selection_reverse(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();
           

            std::ofstream out1, out2;
            out1.open("shella_random_comparison.txt");
            out2.open("shella_random_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = shella_random(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();


            std::ofstream out1, out2;
            out1.open("shella_sorted_comparison.txt");
            out2.open("shella_sorted_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = shella_sorted(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();


            std::ofstream out1, out2;
            out1.open("shella_reverse_comparison.txt");
            out2.open("shella_reverse_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = shella_reverse(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();



            std::ofstream out1, out2;
            out1.open("heap_random_comparison.txt");
            out2.open("heap_random_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = heap_sort_random(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();


            std::ofstream out1, out2;
            out1.open("heap_sorted_comparison.txt");
            out2.open("heap_sorted_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = heap_sort_sorted(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();


            std::ofstream out1, out2;
            out1.open("heap_reverse_comparison.txt");
            out2.open("heap_reverse_copy.txt");
            if (out1.is_open() && out2.is_open())
            {
                for (int i = 0; i < 13; i++)
                {
                    stats st = heap_sort_reverse(mass[i]);
                    out1 << st.comparison_count << '\t' << mass[i] << std::endl;
                    out2 << st.copy_count << '\t' << mass[i] << std::endl;
                }

            }
            out1.close();
            out2.close();
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
