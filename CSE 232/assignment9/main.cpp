#include <iostream>
#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"
#include "FL/Fl_Button.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Float_Input.H"

// Declare the global widgets so Callbacks can get at them
Fl_Button *pClearButton;
Fl_Float_Input *pInputFarenheit, *pInputCelsius, *pInputKelvin;

// I'm lazy
typedef enum
{
    TEMP_F = 0,
    TEMP_C,
    TEMP_K
} TemperatureType;

// These are sort of redundant but they work
inline float toFarenheit(float val, TemperatureType t)
{
    if (t == TEMP_F)
        return val;
    else if (t == TEMP_K)
        return toFarenheit(val - 273.15f, TEMP_C);
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

void ClearFields()
{
    if (pInputFarenheit)
        pInputFarenheit->value("");
    if (pInputCelsius)
        pInputCelsius->value("");
    if (pInputKelvin)
        pInputKelvin->value("");
}

void TextCallback(Fl_Widget *pW)
{
    if (pW == pInputKelvin)
    {
        float val = (float)atof(pInputKelvin->value());
        // Below absolute value is not possible
        if (val < 0.0)
        {
            ClearFields();
            return;
        }

        // Update the other two
        if (pInputFarenheit)
            pInputFarenheit->value(to_string(toFarenheit(val, TEMP_K)).c_str());
        if (pInputCelsius)
            pInputCelsius->value(to_string(toCelsius(val, TEMP_K)).c_str());
    }
    else if (pW == pInputCelsius)
    {
        float val = (float)atof(pInputCelsius->value());
        if (val < -273.15f)
        {
            ClearFields();
            return;
        }

        if (pInputFarenheit)
            pInputFarenheit->value(to_string(toFarenheit(val, TEMP_C)).c_str());
        if (pInputKelvin)
            pInputKelvin->value(to_string(toKelvin(val, TEMP_C)).c_str());
    }
    else if (pW == pInputFarenheit)
    {
        float val = (float)atof(pInputFarenheit->value());
        if (val < -459.67f)
        {
            ClearFields();
            return;
        }

        if (pInputCelsius)
            pInputCelsius->value(to_string(toCelsius(val, TEMP_F)).c_str());
        if (pInputKelvin)
            pInputKelvin->value(to_string(toKelvin(val, TEMP_F)).c_str());
    }
}

void ButtonCallback(Fl_Widget *widget)
{
    ClearFields();
}

// Under the spirit of the 'L' in FLTK, this is a very tiny and lightweight program.
// Pressing enter causes the conversion, pressing clear clears the fields.
// And pressing "next" closes the window. *shrug*
int main()
{
    // Create widgets
    Simple_window sw(Point(500, 250), 350, 100, "Temperature Converter");
    pInputFarenheit = new Fl_Float_Input(75, 2, 200, 30, "Fahrenheit");
    pInputCelsius = new Fl_Float_Input(75, 32, 200, 30, "Celsius");
    pInputKelvin = new Fl_Float_Input(75, 62, 200, 30, "Kelvin");
    pClearButton = new Fl_Button(280, 62, 40, 30, "Clear");

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