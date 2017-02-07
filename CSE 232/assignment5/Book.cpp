//
// Created by nick on 2/3/17.
//
#include "Book.h"

#include <cstring>


Book::Book()
{
    m_bCheckedOut = false;
    m_pAuthor = "";
    m_pCopyrightDate = "";
    m_pISBN = "";
    m_pTitle = "";
}

Book::Book(const char *title, const char *author, const char *ISBN)
{
    m_pTitle = title;
    m_pAuthor = author;
    m_pISBN = ISBN;
}

void Book::CheckOut()
{
    m_bCheckedOut = true;
}

void Book::CheckIn()
{
    m_bCheckedOut = false;
}

const bool Book::operator!=(const Book &other)
{
    return strcmp(m_pISBN, other.m_pISBN) != 0;
}

const bool Book::operator==(const Book &other)
{
    return strcmp(m_pISBN, other.m_pISBN) == 0;
}

void Book::SetISBN(const char *pISBN)
{
    //strtok(m_pISBN, "-");
    // TODO
}

std::ostream &operator<<(std::ostream &cout, Book *pBook)
{
    cout << pBook->m_pTitle << std::endl;
    cout << pBook->m_pAuthor << std::endl;
    cout << pBook->m_pISBN << std::endl;
    return cout;
}
