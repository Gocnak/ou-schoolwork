#include <iostream>

#include "Book.h"
#include "Library.h"

using namespace std;

int main()
{
    try
    {
        // Make our library
        Library lib = Library();
    
        // Make our books
        Book book1 = Book("The Cat in the Hat", "Dr. Seuss", "12-45-845-YES");
        Book book2 = Book("The Hunger Games", "Carolyn McCormick", "145-958-554-14521");
        
        // Note: Uncomment to test ISBN checking
        // book1.SetISBN("F4KE-ISBN-SH0ULD-F[]L");
    
        // Some testing
        cout << "Book1: " << &book1;
        cout << "Book2: " << &book2;
        cout << "Book1 == Book2: " << (book1 == book2) << endl;
        cout << "Book1 != Book2: " << (book1 != book2) << endl;
    
        lib.AddBook(book1);
        lib.AddBook(book2);
    
        // Make our patrons
        Patron john = Patron("John", 1245884);
        Patron patrice = Patron("Patrice", 129584);
    
        // Some testing
        cout << "Patron1: " << john.GetName() << endl;
        cout << "Patron2: " << patrice.GetName() << endl;
        cout << "Patron1 == Patron2: " << (john == patrice) << endl;
        
        // Note: Uncomment the following to test fees functionality
        // john.SetFees(50.0);
        // patrice.SetFees(25.0);
        
        lib.AddPatron(john);
        lib.AddPatron(patrice);
        
        // Checking out books
        // John wants some Dr. Seuss
        lib.CheckoutBook(john, book1);
    
        // Note: Uncomment the following to test checkout functionality
        // lib.CheckoutBook(patrice, book1);
    
        // Patrice will be basic
        lib.CheckoutBook(patrice, book2);
        
        // Check our fee patrons
        std::vector<Patron> feePatrons = lib.GetFeePatrons();
        if (!feePatrons.empty())
        {
            for (auto i = 0; i < feePatrons.size(); i++)
            {
                Patron p = feePatrons[i];
                cout << p.GetName() << " owes $" << p.GetFees() << " in fees!" << endl;
            }
        }
        else
        {
           cout << "Nobody owes any fees!" << endl;
        }
        
        return 0;
    }
    catch (const char *pMsg)
    {
        cout << pMsg << endl;
        return -1;
    }
    catch (...)
    {
        return -1;
    }
}