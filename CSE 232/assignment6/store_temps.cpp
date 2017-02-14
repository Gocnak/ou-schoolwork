#include <iostream>
#include <random>
#include <fstream>

using namespace std;

struct Reading { // a temperature reading
    int hour; // hour after midnight [0:23]
    double temperature; // in Fahrenheit
};

// Macro'd here for ease of change. We're doing this over a 24 hour period.
#define MAX_HOURS 24

int main()
{
    // Setup our random number generation.
    default_random_engine generator;
    normal_distribution<double> distribution(55.0, 15.0);
    
    // Open our output file for saving.
    ofstream outfile("raw_temps.txt");
    if (!outfile)
    {
        cerr << "Could not write to file raw_temps.txt!" << endl;
        return -1;
    }
    
    for (int i = 0; i < MAX_HOURS; i++)
    {
        // Generate the temperature for this hour.
        Reading temp {i, distribution(generator)};
        // Output the temperature to the file.
        outfile << temp.hour << ' ' << temp.temperature << endl;
    }
    
    // Close our file.
    outfile.close();
    
    // All done!
    return 0;
}