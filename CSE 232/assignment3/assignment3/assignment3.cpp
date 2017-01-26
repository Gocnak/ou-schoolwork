// assignment2.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <map>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace chrono;

#define VECTOR_SIZE 1000  // The size of the numbers of vectors
#define RANDOM_RANGE 300  // 1 to this number is the range of numbers that can be generated

void sortMethod(vector<int> *v, int &_min, int &_max, int &_mode)
{
    // Sort the array using at most [O(n lg n)] time complexity
    sort(v->begin(), v->end());

    // Ay, if it's sorted, these values should be fairly simple to find [O(1)]
    int min = v->front();
    int max = v->back();

    // Now we do some simple scanning for our mode [O(VECTOR_SIZE)] ~= [O(n)]
    int mode = min, highest_mode = min;
    int count = 1, highest_count = 0;

    // Since our list is in order, we can scan along the numbers and count how often the number appears
    // Upon changing numbers, we refresh the count, comparing against the highest stored count to see if there is
    // an element that appears more in the list than the previous mode.
    for (auto i : *v)
    {
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

    // Return our values
    _min = min;
    _max = max;
    _mode = highest_mode;
}

void hashMapMethod(vector<int> *v, int &_min, int &_max, int &_mode)
{
    // The idea for the (hash)map method is to store counts of each number as the value.
    // Each time the same number is found (collision), we update the count of that number, while
    // simulataneously keeping track of the highest number/count keyvalue pair, minimum number, and maximum number.

    // It should be noted that if implemented correctly, a runtime of O(N) + C should be achieved, where C is some arbitrary
    // constant value (due to allocation, comparisons, etc; this is a very small number in relation to N).
    
    unordered_map<int, int> hashmap = unordered_map<int, int>();

    int min_num = INT_MAX, max_num = INT_MIN;

    int max_count = 0, mode = min_num;

    for (auto i : *v)
    {
        // Is this number the smallest?
        min_num = min<int>(min_num, i);

        // Is this number the largest?
        max_num = max<int>(max_num, i);

        // How many times does this number exist in the map?
        int count; 

        // Does this number even exist in the hashmap?
        auto it = hashmap.find(i);
        if (it != hashmap.end()) // Exists in the hashmap
        {
            count = hashmap[i]; // Set our count to the current in the map
            count++; // Increase our count (this number adds one)
        }
        else // doesn't exist
        {
            count = 1; // This is our first instance of this number
        }

        hashmap[i] = count; // Update our count
        
        // But wait a minute, is this higher than our max count?
        if (count > max_count)
        {
            // So it seems. Let's update the mode to this number, along with the max_count.
            mode = i;
            max_count = count;
        }
    }

    // At this point we really don't care for the hashmap. So I suppose we could clear it to cleanup resources.
    hashmap.clear();

    // Return our values
    _min = min_num;
    _max = max_num;
    _mode = mode;
}

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

    // Initialize our min, max, and mode variables.
    int min, max, mode;
    
    // Begin timing our sorting method
    auto start_sort = high_resolution_clock::now();
    // Run our sorting method
    sortMethod(&v, min, max, mode);
    // Calculate the time elapsed (in seconds)
    duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - start_sort);

    cout << "(Min, Max, Mode): (" << min << ", " << max << ", " << mode << ")" << endl;
    cout << "Found in: " << time_span.count() << " seconds." << endl;

    // Begin timing our hashmap method
    auto start_hash = high_resolution_clock::now();
    // Run our hashmap method
    hashMapMethod(&v, min, max, mode);
    // Calculate the time elapsed (in seconds)
    time_span = duration_cast<duration<double>>(high_resolution_clock::now() - start_hash);

    cout << "(Min, Max, Mode): (" << min << ", " << max << ", " << mode << ")" << endl;
    cout << "Found in: " << time_span.count() << " seconds." << endl;

    return 0;
}