// assignment1.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "Windows.h"

int main()
{
    std::cout << "Press Enter to continue";
    char c;
    std::cin.get(c);
    OutputDebugString(L"This goes in Visual Studio's console\n");
    return 0;
}