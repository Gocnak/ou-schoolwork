#include <iostream>
#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"
#include "FL/Fl_Button.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Float_Input.H"

Fl_Button *pClearButton;
Fl_Float_Input *pInputFarenheit, *pInputCelsius, *pInputKelvin;

typedef enum
{
    TEMP_F = 0,
    TEMP_C,
    TEMP_K
} TemperatureType;

inline float toFarenheit(float val, TemperatureType t)
{
    if (t == TEMP_F)
        return val;
    else if (t == TEMP_K)
        return toFarenheit(val + 273.15f, TEMP_C);
    else
        return val * (9.0f/5.0f) + 32.0f;
}

inline float toCelsius(float val, TemperatureType t)
{
    if (t == TEMP_C)
        return val;
    else if (t == TEMP_K)
        return val - 273.15f;
    else
        return (val - 32.0f) * 5.0f/9.0f;
}

inline float toKelvin(float val, TemperatureType t)
{
    if (t == TEMP_K)
        return val;
    else if (t == TEMP_C)
        return val + 273.15f;
    else
        return toKelvin(toCelsius(val, t), TEMP_C);
}

void TextCallback(Fl_Widget *pW)
{
    // TODO: For each input, see if it's a valid number, then convert
    // to all other fields
    if (pW == pInputKelvin)
    {
        float val = (float)atof(pInputKelvin->value());
        // Below absolute value is not possible
        if (val < 0.0)
        {
            pInputKelvin->value("");
        }

        if (pInputFarenheit)
            pInputFarenheit->value(to_string(toFarenheit(val, TEMP_K)).c_str());
    }
    else if (pW == pInputCelsius)
    {
        double val = atof(pInputCelsius->value());
    }
    else if (pW == pInputFarenheit)
    {
        double val = atof(pInputFarenheit->value());

    }
}

void ButtonCallback(Fl_Widget *widget)
{
    //TODO: clear all inputs
}

int main()
{
    // Create widgets
    Simple_window sw(Point(50, 50), 500, 500, "Temperature Converter");
    pInputFarenheit = new Fl_Float_Input(200, 2, 200, 50, "Fahrenheit");
    pInputCelsius = new Fl_Float_Input(200, 52, 200, 50, "Celsius");
    pInputKelvin = new Fl_Float_Input(200, 102, 200, 50, "Kelvin");
    pClearButton = new Fl_Button(200, 152, 100, 100, "Clear");

    // Set callbacks
    pInputFarenheit->callback(&TextCallback);
    pInputCelsius->callback(&TextCallback);
    pInputKelvin->callback(&TextCallback);
    pClearButton->callback(&ButtonCallback);

    // Add the widgets and show them
    sw.add(pInputFarenheit);
    sw.add(pInputCelsius);
    sw.add(pInputKelvin);
    sw.add(pClearButton);
    sw.show();
    return gui_main();
}