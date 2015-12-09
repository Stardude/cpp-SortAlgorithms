#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <string>
using namespace std;

void output(vector<int>);
void bucket_sort_string(string);
void bucket_sort(vector<int>);
void radix_sort(vector<int>);
void strand_sort(vector<int>);
void counting_sort(vector<int>);

int main()
{
	vector<int> mas = { 29, 25, 3, 49, 9, 37, 21, 43, 41, 1, 5, 10 };
	cout << "Original: ";	output(mas);
	cout << "\n\nChoose your sort algorithm:\n"
		<< "\t1. Bucket sorting\n"
		<< "\t2. Radix sorting\n"
		<< "\t3. Strand sorting\n"
		<< "\t4. Counting sorting\n";
	short choice;
	cout << "\n-> "; cin >> choice;
	switch (choice)
	{
	case 1:
		bucket_sort(mas);
		break;
	case 2:
		radix_sort(mas);
		break;
	case 3:
		strand_sort(mas);
		break;
	case 4:
		counting_sort(mas);
		break;
	default:
		break;
	}
	cout << "\n\n";
	system("pause");
	return 1;
}

void output(vector<int> mas)
{
	for (int i = 0; i < mas.size(); i++)
	{
		cout << "  " << mas[i];
	}
}

void bucket_sort_string(string str)
{
	vector<int> mas;
	while (str != "")
	{
		mas.push_back(stoi(str.substr(0, str.find(','))));
		str = str.substr(str.find(',') + 1);
	}
	bucket_sort(mas);
}

void bucket_sort(vector<int> mas)
{
	static vector<int> result(mas.size());
	static int I = 0;
	static clock_t start = clock();
	vector<int>::iterator i_max = max_element(mas.begin(), mas.end());
	vector<int>::iterator i_min = min_element(mas.begin(), mas.end());
	vector<string> bucket;
	bucket.resize(5);
	int countInBucket = (*i_max - *i_min) / 5 + 1;
	int index;
	for (int i = 0; i < mas.size(); i++)
	{
		index = (mas[i] - *i_min) / countInBucket;
		if (index < 0)
			bucket[0] += to_string(mas[i]) + ",";
		else
			bucket[index] += to_string(mas[i]) + ",";
	}
	for (int i = 0; i < bucket.size(); i++)
	{
		if (bucket[i] != "")
			if (count(bucket[i].begin(), bucket[i].end(), ',') == 1)
			{
				result[I] = stoi(bucket[i].substr(0, bucket[i].find(',')));
				I++;
			}
			else
				bucket_sort_string(bucket[i]);
	}
	if (result.back())
	{
		clock_t end = clock();
		cout << "\nTime: " << (double)(end - start) / (double)CLOCKS_PER_SEC;
		cout << "\nBucket sorting: "; output(result);
		result.push_back(0);
	}
}

void radix_sort(vector<int> mas)
{
	vector<int>::iterator i_max = max_element(mas.begin(), mas.end());
	int max = *i_max;
	vector<int> result;
	result.resize(mas.size());
	vector<short> count;
	count.resize(10);
	clock_t start = clock();
	for (int exp = 1; max / exp > 0; exp = exp * 10)
	{
		result.clear();
		result.resize(mas.size());
		count.clear();
		count.resize(10);
		for (int i = 0; i < mas.size(); i++)
			count[(mas[i] / exp) % 10]++;
		for (int i = 1; i < 10; i++)
			count[i] += count[i - 1];
		for (int i = mas.size() - 1; i >= 0; i--)
		{
			result[count[(mas[i] / exp) % 10] - 1] = mas[i];
			count[(mas[i] / exp) % 10]--;
		}
		for (int i = 0; i < mas.size(); i++)
			mas[i] = result[i];
	}
	clock_t end = clock();
	cout << "\nTime: " << (double)(end - start) / (double)CLOCKS_PER_SEC;
	cout << "\nRadix sorting: "; output(mas);
}

void strand_sort(vector<int> mas)
{
	list<int> current(mas.begin(),mas.end());
	list<int> result;
	list<int> sublist;
	clock_t start = clock();
	while (!current.empty())
	{
		sublist.push_back(current.front());
		current.pop_front();
		for (list<int>::iterator it = current.begin(); it != current.end();)
		{
			if (sublist.back() <= *it)
			{
				sublist.push_back(*it);
				it = current.erase(it);
			}
			else
				it++;
		}
		result.merge(sublist);
	}
	clock_t end = clock();
	mas.clear();
	mas.insert(mas.begin(), result.begin(), result.end());
	cout << "\nTime: " << (double)(end - start) / (double)CLOCKS_PER_SEC;
	cout << "\nStrand sorting: "; output(mas);
}

void counting_sort(vector<int> mas)
{
	vector<int>::iterator i_max = max_element(mas.begin(), mas.end());
	vector<int>::iterator i_min = min_element(mas.begin(), mas.end());
	vector<int> counts;
	vector<int> result;
	result.resize(mas.size());
	counts.resize(*i_max - *i_min + 1);
	clock_t start = clock();
	for (int i = 0; i < mas.size(); i++)
	{
		counts[mas[i] - *i_min]++;
	}
	for (int i = 1; i < counts.size(); i++)
	{
		counts[i] = counts[i] + counts[i - 1];
	}
	for (int i = mas.size() - 1; i >= 0; i--)
	{
		result[counts[mas[i] - *i_min] - 1] = mas[i];
		counts[mas[i] - *i_min]--;
	}
	clock_t end = clock();
	cout << "\nTime: " << (double)(end - start) / (double)CLOCKS_PER_SEC;
	cout << "\nCounting sorting: "; output(result);
}

