//
// Created by nick on 2/3/17.
//

#include "Library.h"


Library::Library()
{

}

void Library::CheckoutBook(Patron &p, Book &b)
{
    if (!HasPatron(&p))
        ;

    if (!HasBook(&b))
        ;

    if (p.OwesFees())
        ;

    Transaction t;
    t.m_Book = b;
    t.m_Patron = p;
    //TODO t.m_Date = now?
    m_vecTransaction.push_back(t);
}

std::vector<Patron> &Library::GetFeePatrons()
{
    std::vector<Patron> feePatrons;
    for (auto i = 0; i < m_vecPatrons.size(); i++)
    {
        Patron p = m_vecPatrons[i];
        if (p.OwesFees())
            feePatrons.push_back(p);
    }
    return feePatrons;
}

bool Library::HasPatron(Patron *p)
{
    if (!p || m_vecPatrons.empty()) return false;
    for (auto i = 0; i < m_vecPatrons.size(); i++)
    {
        if (*p == m_vecPatrons[i])
            return true;
    }
    return false;
}

bool Library::HasBook(Book *b)
{
    if (!b || m_vecBooks.empty()) return false;
    for (auto i = 0; i < m_vecBooks.size(); i++)
    {
        if (*b == m_vecBooks[i])
            return true;
    }
    return false;
}
