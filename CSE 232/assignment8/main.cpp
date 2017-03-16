#include <iostream>
#include "GUI/Graph.h"
#include "GUI/Simple_window.h"

class Bezier : Function
{
public:
    Bezier(Point p1, Point p2, Point p3, int t);

    void draw_lines() const override;

};

int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}