//
// Created by nick on 2/3/17.
//
#include "Book.h"

#include <cstring>
#include <vector>
#include <string>
#include <sstream>


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

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void Book::SetISBN(std::string pISBN)
{
    std::vector<std::string> parts = split(pISBN, '-');
    // First three must be int
    for (int i = 0; i < 3; i++)
    {
        int test = atoi(parts[i]);
        if (test < 1)
            throw std::exception();
    }
    // The last guy should be a digit or a letter
    const char *last = parts[3].c_str();
    for (int i = 0; i < strlen(last); i++)
    {
        if (!isalnum(last[i]))
            throw std::exception();
    }

    // Passed all checks
    m_pISBN = pISBN;
}

std::ostream &operator<<(std::ostream &cout, Book *pBook)
{
    cout << pBook->m_pTitle << std::endl;
    cout << pBook->m_pAuthor << std::endl;
    cout << pBook->m_pISBN << std::endl;
    return cout;
}
