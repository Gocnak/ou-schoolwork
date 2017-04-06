#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

void fillTrigrams(string *pString, unordered_map<string, int> *pMap)
{
    if (!pString || !pMap)
        return;

    size_t maxlen = pString->length();
    // In steps of three...
    for (unsigned int i = 0; i + 2 < maxlen; i++)
    {
        // Make our trigram substring
        string trigram = pString->substr(i, 3);
        // Replace any spaces if they exist
        replace(trigram.begin(), trigram.end(), ' ', '_');
        // Update the count if it exists
        int count = 0;
        // Does it exist?
        unordered_map<string, int>::iterator found = pMap->find(trigram);
        if (found != pMap->end())
        {
            count = found->second; // Get the existing count if it does
        }
        count++; // Otherwise this will be 1
        (*pMap)[trigram] = count;
    }
}


int main()
{
    // Get the input
    cout << "Input your text:" << endl;
    string input;
    getline(cin, input);
    
    // Make and fill the trigram map
    unordered_map<string, int> map;
    fillTrigrams(&input, &map);
    
    // Output the trigrams and their counts
    for (const auto &n : map)
        cout << "Trigram: " << n.first << " (" << n.second << ")" << endl;
    
    return 0;
}