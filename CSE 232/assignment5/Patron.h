//
// Created by nick on 2/3/17.
//
#pragma once

#include <cstring>

class Patron
{
public:

    Patron(const char *pName, int card)
    {
        m_pName = pName;
        m_iLibraryCard = card;
        m_fFees = 0.0f;
    }

    const char *GetName() { return m_pName;}
    int GetLibraryCardNumber() { return m_iLibraryCard;}
    double GetFees() { return m_fFees;}
    bool OwesFees() { return m_fFees > 0;}

    void SetFees(double fees) { m_fFees = fees;}

    const bool &operator==(const Patron &other)
    {
        return strcmp(m_pName, other.m_pName) == 0 &&
               m_iLibraryCard == other.m_iLibraryCard;
    }

private:
    const char *m_pName;
    int m_iLibraryCard;
    double m_fFees;
};
