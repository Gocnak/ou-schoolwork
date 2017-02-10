//
// Created by nick on 2/9/17.
//
#include "Chrono.h"

namespace Chrono {
// member function definitions:
    Date::Date(int yy, Month mm, int dd)
            : y{yy}, m{mm}, d{dd}
    {
        if (!is_date(yy, mm, dd)) throw Invalid{};
    }

    const Date &default_date()
    {
        static Date dd{2001, Month::jan, 1}; // start of 21st century
        return dd;
    }

    Date::Date()
            : y{default_date().year()},
              m{default_date().month()},
              d{default_date().day()}
    {
    }

    void Date::add_year(int n)
    {
        if (m == Month::feb && d == 29 && !leapyear(y + n)) {
// beware of leap years!
            m = Month::mar;
// use March 1 instead of February 29
            d = 1;
        }
        y += n;
    }

// helper functions:
    bool is_date(int y, Month m, int d)
    {
// assume that y is valid
        if (d <= 0) return false;
// d must be positive
        if (m < Month::jan || Month::dec < m) return false;
        int days_in_month = 31;
// most months have 31 days
        switch (m) {
            case Month::feb:
// the length of February varies
                days_in_month = (leapyear(y)) ? 29 : 28;
                break;
            case Month::apr:
            case Month::jun:
            case Month::sep:
            case Month::nov:
            default:
                days_in_month = 30;
// the rest have 30 days
                break;
        }
        return days_in_month >= d;
    }

    bool leapyear(int y)
    {// see exercise 10
    }

    bool operator==(const Date &a, const Date &b)
    {
        return a.year() == b.year()
               && a.month() == b.month()
               && a.day() == b.day();
    }

    bool operator!=(const Date &a, const Date &b)
    {
        return !(a == b);
    }
}
// Chrono
