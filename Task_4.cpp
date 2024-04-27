#include <iostream>
#include <algorithm>

using namespace std;

int split(int arr[], int low, int high, int k)
{
    int splitIndex = low;
    for (int j = low; j <= high; j++)
    {
        if (arr[j] <= k)
        {
            swap(arr[splitIndex], arr[j]);
            splitIndex++;
        }
    }
    return splitIndex - 1;
}

void rearrangeElements(int arr[], int low, int high, int k)
{
    if (low < high)
    {
        int si = split(arr, low, high, k);
    }
}

int main()
{
    int arr[] = {10, 4, 5, 8, 1, 3, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;
    rearrangeElements(arr, 0, n - 1, k);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
