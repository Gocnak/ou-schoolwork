#include <iostream>
#include <memory>
#include <cstring>
#include <stdarg.h>
#include <vector>

// Taken from stack overflow
inline void log(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], (size_t) n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    std::cout << formatted.get() << std::endl;
}

class RAII
{
public:
    RAII() : m_pPayload(nullptr)
    {
        m_iInstance = instanceIDs;
        instanceIDs++;
        log("Created a blank RAII with ID: %i", m_iInstance);
    }
    RAII(size_t size) : m_pPayload(nullptr)
    {
        m_iInstance = instanceIDs;
        instanceIDs++;
        r_allocate(size);
        log("Created an allocated RAII with size %i and address %p", size, m_pPayload);
    }

    RAII(const RAII &other) : m_pPayload(nullptr)
    {
        m_iInstance = instanceIDs;
        instanceIDs++;
        r_copy(other);
        log("Created a copy-constructed RAII with ID %i and address %p (original address at %p)",
        m_iInstance, m_pPayload, other.m_pPayload);
    }

    ~RAII()
    {
        log("Deallocating the RAII instance %p ...", m_pPayload);
        r_free();
        log("Deallocated the RAII instance with ID %i", m_iInstance);
    }

    RAII &operator=(const RAII &other)
    {
        r_copy(other);
        log("Copied from the RAII with ID %i, into the pointer %p", other.m_iInstance, m_pPayload);
        return *this;
    }

    static int instanceIDs;

    void r_log()
    {
        log("ID: %i, Address: %p", m_iInstance, m_pPayload);
    }

private:
    void r_allocate(size_t size)
    {
        if (m_pPayload)
        {
            log("We're trying to allocate when we're not null, for address %p", m_pPayload);
            return;
        }
        log("Allocating RAII for ID %i", m_iInstance);
        m_pPayload = (char*)malloc(size);
        log("Allocated RAII (ID, address): (%i, %p)", m_iInstance, m_pPayload);
    }

    void r_copy(const RAII &other)
    {
        // Get rid of the current payload, if it exists
        r_free();
        // Allocate the new buffer with this size
        size_t size = sizeof(other.m_pPayload);
        r_allocate(size);
        // And now copy the payload to this
        memcpy(m_pPayload, other.m_pPayload, size);
    }

    void r_free()
    {
        free(m_pPayload);
        m_pPayload = nullptr;
    }

    int m_iInstance;
    char *m_pPayload;

};

// Initialize our instance IDs
int RAII::instanceIDs = 0;

// During "regular" instantiation within a function
void test1()
{
    log("TEST ONE! (Regular instantiation)");
    RAII *test1_1 = new RAII();
    RAII *test1_2 = new RAII(10);
    RAII *test1_3 = new RAII(*test1_2);
    delete test1_1;
    delete test1_2;
    delete test1_3;
}

void test2_and_3()
{
    log("TEST TWO! (Put in a vector)");
    RAII *test2_1 = new RAII(20);
    RAII *test2_2 = new RAII(20);
    RAII *test2_3 = new RAII(30);
    std::vector<RAII*> instances;
    instances.push_back(test2_1);
    instances.push_back(test2_2);
    instances.push_back(test2_3);

    for (RAII *e : instances)
    {
        e->r_log();
    }

    log("TEST THREE! (Vector of instances copied)");
    // Note: I don't think this is what was intended, since I store pointers in both.
    std::vector<RAII*> copy_into;
    copy_into = instances;

    for (RAII *e : copy_into)
    {
        e->r_log();
    }

    delete test2_1;
    delete test2_2;
    delete test2_3;
}


// Case 1: Move constructor
RAII *test_func1(size_t size = 10)
{
    return new RAII(size);
}

// Case 2: Move assignment
RAII *test_func2(RAII *toAssignTo, size_t size = 10)
{
    toAssignTo = new RAII(size);
    return toAssignTo;
}

void test4()
{
    log("TEST FOUR! (Returned from function)");
    log("Case 1: (move constructor");
    RAII *test4_1 = test_func1(20);
    log("Case 2: (copy assignment)");
    RAII *test4_2 = nullptr;
    test4_2 = test_func2(test4_2, 20);

    delete(test4_1);
    delete(test4_2);
}


int main()
{
    test1();
    test2_and_3();
    test4();
    return 0;
}