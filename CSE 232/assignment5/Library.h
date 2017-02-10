//
// Created by nick on 2/3/17.
//
#pragma once

#include <vector>
#include "Book.h"
#include "Patron.h"
#include "Chrono.h"

struct Transaction
{
    Book m_Book;
    Patron m_Patron;
    Chrono::Date m_Date;
};


class Library
{
public:

    Library();

    void AddBook(Book &b) { m_vecBooks.push_back(b);}
    void AddPatron(Patron &p) { m_vecPatrons.push_back(p);}
    void CheckoutBook(Patron &p, Book &b);
    std::vector<Patron> GetFeePatrons();

    bool HasPatron(Patron *p);
    bool HasBook(Book *b);

private:

    std::vector<Book> m_vecBooks;
    std::vector<Patron> m_vecPatrons;
    std::vector<Transaction> m_vecTransaction;

};
