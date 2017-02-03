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

    void SetTitle(const char *pTitle) { this->pTitle = pTitle;}
    void SetAuthor(const char *pAuth) { pAuthor = pAuth;}
    void SetISBN(const char *pISBN);
    void SetCopyrightDate(const char *pDate) { pCopyrightDate = pDate;}
    void SetGenre(Genre g) { kBookGenre = g;}

    bool IsCheckedOut() { return bCheckedOut; }
    const char *GetTitle() { return pTitle;}
    const char *GetAuthor() { return pAuthor;}
    const char *GetISBN() { return pISBN;}
    const char *GetCopyrightDate() { return pCopyrightDate;}
    Genre GetGenre() { return kBookGenre;}

    const bool operator==(const Book &other);
    const bool operator!=(const Book &other);
    friend std::ostream &operator<<(std::ostream &cout, Book *pBook);

private:
    bool bCheckedOut;
    const char *pTitle, *pAuthor, *pISBN, *pCopyrightDate;
    Genre kBookGenre;
};