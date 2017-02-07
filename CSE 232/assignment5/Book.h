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

    void SetTitle(const char *pTitle) { m_pTitle = pTitle;}
    void SetAuthor(const char *pAuth) { m_pAuthor = pAuth;}
    void SetISBN(const char *pISBN);
    void SetCopyrightDate(const char *pDate) { m_pCopyrightDate = pDate;}
    void SetGenre(Genre g) { m_kBookGenre = g;}

    bool IsCheckedOut() { return m_bCheckedOut; }
    const char *GetTitle() { return m_pTitle;}
    const char *GetAuthor() { return m_pAuthor;}
    const char *GetISBN() { return m_pISBN;}
    const char *GetCopyrightDate() { return m_pCopyrightDate;}
    Genre GetGenre() { return m_kBookGenre;}

    const bool operator==(const Book &other);
    const bool operator!=(const Book &other);
    friend std::ostream &operator<<(std::ostream &cout, Book *pBook);

private:
    bool m_bCheckedOut;
    const char *m_pTitle, *m_pAuthor, *m_pISBN, *m_pCopyrightDate;
    Genre m_kBookGenre;
};