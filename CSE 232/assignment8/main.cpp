#include <iostream>
#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"

class Bezier : public Shape
{
public:
    Bezier(Point p1, Point p2, Point p3, int t)
    {
        double rate = 1.0 / (double)t;
        for (double locT = 0.0; locT <= 1.0; locT += rate)
        {
            double inv = 1 - locT;
            // (1-t)^2 * P1 + 2(1-t)*t*P2 + t^2*P3
            double x = inv*inv * (double)p1.x + 2.0 * inv * locT * (double)p2.x + locT * locT * (double)p3.x;
            double y = inv*inv * (double)p1.y + 2.0 * inv * locT * (double)p2.y + locT * locT * (double)p3.y;
            add(Point((int) x, (int) y));
        }
    }
};

int main()
{
    Simple_window window(Point(20, 20), 500, 500, "Bezier");
    Bezier b(Point(10, 10), Point(20, 400), Point(50, 300), 100);
    b.set_color(Color::blue);
    Bezier b1(Point(10, 300), Point(200, 0), Point(500, 300), 100);
    b1.set_color(Color::green);
    Bezier b2(Point(300, 10), Point(0, 200), Point(300, 500), 100);
    b2.set_color(Color::magenta);
    window.attach(b);
    window.attach(b1);
    window.attach(b2);
    window.show();
    return gui_main();
}