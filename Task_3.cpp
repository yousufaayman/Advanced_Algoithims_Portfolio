#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace std;

int heapify(int arr[], int size, int index, int &comparisons)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left] < arr[smallest])
    {
        smallest = left;
        comparisons++;
    }
    if (right < size && arr[right] < arr[smallest])
    {
        comparisons++;
        smallest = right;
    }
    if (smallest != index)
    {
        swap(arr[index], arr[smallest]);
        heapify(arr, size, smallest, comparisons);
    }
    return comparisons;
}

int heapSortCount(int arr[], int size)
{
    int comparisons = 0;
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i, comparisons);

    for (int i = size - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, comparisons);
    }
    return comparisons;
}

int bubbleSortCount(int arr[], int size)
{
    int comparisons = 0;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            comparisons++;
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return comparisons;
}

int selectionSortCount(int arr[], int size)
{
    int comparisons = 0;
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            comparisons++;
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[minIndex], arr[i]);
    }
    return comparisons;
}

int insertionSortCount(int arr[], int size)
{
    int comparisons = 0;
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparisons++;
        }
        arr[j + 1] = key;
    }
    return comparisons;
}

void testComparisons()
{
    srand(time(NULL));
    cout << "Sort Type | Heap Sort | Bubble Sort | Selection Sort | Insertion Sort" << endl;

    for (int testType = 0; testType < 3; testType++)
    {
        int arraySize = 30;
        int comparisonCounts[4] = {0};
        chrono::duration<double> totalTimes[4];

        for (int t = 0; t < arraySize; t++)
        {
            vector<int> arr(30);
            if (testType == 0)
                generate(arr.begin(), arr.end(), []()
                         { return rand() % 100; });
            else if (testType == 1)
                iota(arr.begin(), arr.end(), 0);
            else
                iota(arr.rbegin(), arr.rend(), 1);

            vector<int> temp = arr;
            auto start = chrono::high_resolution_clock::now();
            comparisonCounts[0] += heapSortCount(temp.data(), 30);
            auto end = chrono::high_resolution_clock::now();
            totalTimes[0] += end - start;

            temp = arr;
            start = chrono::high_resolution_clock::now();
            comparisonCounts[1] += bubbleSortCount(temp.data(), 30);
            end = chrono::high_resolution_clock::now();
            totalTimes[1] += end - start;

            temp = arr;
            start = chrono::high_resolution_clock::now();
            comparisonCounts[2] += selectionSortCount(temp.data(), 30);
            end = chrono::high_resolution_clock::now();
            totalTimes[2] += end - start;

            temp = arr;
            start = chrono::high_resolution_clock::now();
            comparisonCounts[3] += insertionSortCount(temp.data(), 30);
            end = chrono::high_resolution_clock::now();
            totalTimes[3] += end - start;
        }

        cout << ((testType == 0) ? "Random" : ((testType == 1) ? "Sorted" : "Inversely Sorted")) << " Arrays | ";
        for (int i = 0; i < 4; i++)
        {
            cout << comparisonCounts[i] / arraySize << " comps, " << totalTimes[i].count() / arraySize << " sec | ";
        }
        cout << endl;
    }
}

int main()
{
    testComparisons();
    return 0;
}
