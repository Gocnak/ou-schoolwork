//
// Created by nick on 2/3/17.
//

#pragma once

#include <string>
#include <iostream>

typedef enum
{
    FICTION,
    NON_FICTION,
    PERIODICAL,
    BIOGRAPHY,
    CHILDREN
} Genre;

class Book
{
public:

    Book();
    Book(const char *title, const char *author, const char *ISBN);

    void CheckOut();
    void CheckIn();

    void SetTitle(std::string pTitle) { m_pTitle = pTitle;}
    void SetAuthor(std::string pAuth) { m_pAuthor = pAuth;}
    void SetISBN(std::string pISBN);
    void SetCopyrightDate(std::string pDate) { m_pCopyrightDate = pDate;}
    void SetGenre(Genre g) { m_kBookGenre = g;}

    bool IsCheckedOut() { return m_bCheckedOut; }
    std::string GetTitle() { return m_pTitle;}
    std::string GetAuthor() { return m_pAuthor;}
    std::string GetISBN() { return m_pISBN;}
    std::string GetCopyrightDate() { return m_pCopyrightDate;}
    Genre GetGenre() { return m_kBookGenre;}

    const bool operator==(const Book &other);
    const bool operator!=(const Book &other);
    friend std::ostream &operator<<(std::ostream &cout, Book *pBook);

private:
    bool m_bCheckedOut;
    std::string m_pTitle, m_pAuthor, m_pISBN, m_pCopyrightDate;
    Genre m_kBookGenre;
};