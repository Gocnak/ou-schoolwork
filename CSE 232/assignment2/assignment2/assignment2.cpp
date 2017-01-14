// assignment2.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

#define VECTOR_SIZE 1000  // The size of the numbers of vectors
#define RANDOM_RANGE 300  // 1 to this number is the range of numbers that can be generated

int main()
{
    // Initialize our random number generator
    srand(time(nullptr));

    // Initialize our vector
    vector<int> v;

    // Add numbers to our vector
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        // Add the random number
        v.push_back(rand() % RANDOM_RANGE + 1);
    }
    
    // Cheap workaround ;) [O(n lg n)]
    sort(v.begin(), v.end());

    // Ay, if it's sorted, these values should be fairly simple to find [O(1)]
    int min = v.front();
    int max = v.back();

    // Now we do some simple scanning for our mode [O(VECTOR_SIZE)] ~= [O(n)]
    int mode = min, highest_mode = min;
    int count = 1, highest_count = 0;

    // Since our list is in order, we can scan along the numbers and count how often the number appears
    // Upon changing numbers, we refresh the count, comparing against the highest stored count to see if there is
    // an element that appears more in the list than the previous mode.
    for (auto i : v)
    {
        cout << i << " ";
        if (i == mode)
        {
            count++;
            // Note: If this is changed to >=, we will consider the mode of highest value.
            // Ex: If a list contains 1, 1, 1, 2, 2, 2 and is executed on the following code,
            // the highest mode will be 1, unless the following code is changed to >=.
            if (count > highest_count)
            {
                highest_count = count;
                highest_mode = mode;
            }
        }
        else
        {
            count = 1;
            mode = i;
        }
    }
    cout << endl;

    cout << "Min: " << min << " | Max: " << max << endl;
    cout << "Highest mode: " << highest_mode << endl;

	return 0;
}