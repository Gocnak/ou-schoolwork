#include <iostream>
#include "FL/Fl.H"
#include "FL/Fl_Shared_Image.H"
#include "GUI/Simple_window.h"
#include "FL/Fl_PNG_Image.H"
#include "FL/Fl_Box.H"

int main()
{
    fl_register_images();
    Fl_Window *pWin = new Fl_Window(300, 220, "HI!");
    pWin->begin();
    Fl_Box *box = new Fl_Box(20, 20, 100, 100);
    Fl_PNG_Image *png = new Fl_PNG_Image("/home/nick/Pictures/Selection_001.png");
    box->image(png);
    //box->redraw();
    pWin->end();
    pWin->show();
    return Fl::run();
}