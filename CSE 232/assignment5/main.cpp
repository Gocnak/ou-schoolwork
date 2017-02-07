#include <iostream>

#include "Book.h"

using namespace std;

int main()
{
    Book *b = new Book("Test", "Test", "Testy");
    cout << b;
    return 0;
}