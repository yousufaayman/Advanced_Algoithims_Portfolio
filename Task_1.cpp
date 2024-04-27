#include <iostream>
#include <algorithm>

using namespace std;

void rmDuplicates(char arrayOfChar[], int &lenArrChar)
{
    if (lenArrChar <= 1)
        return;

    sort(arrayOfChar, arrayOfChar + lenArrChar);

    int uniqueCount = 0;
    for (int i = 0; i < lenArrChar - 1; i++)
    {
        if (arrayOfChar[i] != arrayOfChar[i + 1])
        {
            arrayOfChar[uniqueCount++] = arrayOfChar[i];
        }
    }
    arrayOfChar[uniqueCount++] = arrayOfChar[lenArrChar - 1];
    lenArrChar = uniqueCount;
}

int main()
{
    char arrayOfChar[] = {'a', 'b', 'a', 'c', 'd', 'b', 'c'};
    int lenArrChar = sizeof(arrayOfChar) / sizeof(arrayOfChar[0]);

    rmDuplicates(arrayOfChar, lenArrChar);

    cout << endl
         << "Array After Removing Duplicates: ";
    for (int i = 0; i < lenArrChar; i++)
    {
        cout << arrayOfChar[i] << " ";
    }

    return 0;
}
