//
// Created by nick on 2/3/17.
//
#include "Book.h"

#include <cstring>


Book::Book()
{
    bCheckedOut = false;
    pAuthor = "";
    pCopyrightDate = "";
    pISBN = "";
    pTitle = "";
}

Book::Book(const char *title, const char *author, const char *ISBN)
{
    pTitle = title;
    pAuthor = author;
    pISBN = ISBN;
}

void Book::CheckOut()
{
    bCheckedOut = true;
}

void Book::CheckIn()
{
    bCheckedOut = false;
}

const bool Book::operator!=(const Book &other)
{
    return strcmp(pISBN, other.pISBN) != 0;
}

const bool Book::operator==(const Book &other)
{
    return strcmp(pISBN, other.pISBN) == 0;
}

void Book::SetISBN(const char *pISBN)
{
    //strtok(pISBN, "-");
    // TODO
}

std::ostream &operator<<(std::ostream &cout, Book *pBook)
{
    cout << pBook->pTitle << std::endl;
    cout << pBook->pAuthor << std::endl;
    cout << pBook->pISBN << std::endl;
    return cout;
}
