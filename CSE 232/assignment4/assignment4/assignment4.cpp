/*
 * Assignment 4: Nick K. 
 * This was completed by following the book very closely, as well as using
 * the online resource found on http://stroustrup.com/Programming/.
 * I added functionality by following chapter 7, section 7.8.2 in particular.
 * Since I didn't start from scratch: Partial author credit: Bjarne Stroustrup

Simple calculator

This program implements a basic expression calculator.
Input from cin; output to cout.

The grammar for input is:

Calculation:
    Statement
    Print
    Quit
    Calculation Statement

Statement:
    Declaration
    Expression

Declaration:
    "let" Name "=" Expression
Name:
    letter
    letter Sequence
Sequence:
    letter
    digit
    "_"
    letter Sequence
    digit Sequence
    "_" Sequence

Print:
    ";"

Quit:
    "quit"

Expression:
    Term
    Expression "+" Term
    Expression "-" Term
Term:
    Primary
    Term "*" Primary
    Term "/" Primary
    Term "%" Primary
Primary:
    Number
    "(" Expression ")"
    "-" Primary
    "+" Primary
Name
    Name "=" Expression
Number:
    floating-point-literal

Input comes from cin through the Token_stream called ts.
*/

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------

// a very simple user-defined type
class Token
{
  public:
    char kind;                                                // what kind of token
    double value;                                             // for numbers: a value
    string name;                                              // for variables and functions: a name
    Token(char ch) : kind(ch), value(0) {}                    // make a Token from a char
    Token(char ch, double val) : kind(ch), value(val) {}      // make a Token from a char and a double
    Token(char ch, string n) : kind(ch), value(0), name(n) {} // make a Token from a char and a string
};

// stream of tokens
class Token_stream
{
  public:
    Token_stream();        // make a Token_stream that reads from cin
    Token get();           // get a Token
    void putback(Token t); // put a Token back
    void ignore(char c);   // discard characters up to and including a c
  private:
    bool full;    // is there a Token in the buffer?
    Token buffer; // here is where we keep a Token put back using putback()
};

// constructor
Token_stream::Token_stream() : full(false), buffer(0) {} // no Token in buffer

const char let = 'L';          // declaration token
const char quit = 'q';         // t.kind==quit means that t is q quit Token
const char help = 'h';         // help token
const char print = ';';        // t.kind==print means that t is a print Token
const char number = '8';       // t.kind==number means that t is a number Token
const char name = 'a';         // name token
const string declkey = "let";  // declaration keyword
const string quitkey = "quit"; // keyword to quit

// read characters from cin and compose a Token
Token Token_stream::get()
{
    if (full)
    { // check if we already have a Token ready
        full = false;
        return buffer;
    }

    char ch;
    cin.get(ch); // note that cin.get() does NOT skip whitespace
    while (isspace(ch))
    {
        if (ch == '\n')
            return Token(print); // if newline detected, return print Token
        cin.get(ch);
    }

    switch (ch)
    {
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
    case ',':
        return Token(ch); // let each character represent itself
    case '.':             // a floating-point-literal can start with a dot
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': // numeric literal
    {
        cin.putback(ch); // put digit back into the input stream
        double val;
        cin >> val; // read a floating-point number
        return Token(number, val);
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
                s += ch;
            cin.putback(ch);
            if (s == declkey)
                return Token(let); // declaration keyword
            if (s == quitkey)
                return Token(quit); // quit keyword
            return Token(name, s);
        }
        error("Bad token");
    }
}

// put Token back into Token stream
void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into full buffer");
    buffer = t;  // copy t to buffer
    full = true; // buffer is now full
}

// ignore Tokens up to specific kind
void Token_stream::ignore(char c)
// c represents the kind of Token
{
    // first look in buffer:
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while (cin >> ch)
        if (ch == c)
            return;
}

// -----------------------------------------------------------------------

// type for (name,value) pairs
class Variable
{
  public:
    string name;
    double value;
    Variable(string n, double v) : name(n), value(v) {}
};

// type for var_table and associated functions
class Variable_table
{
  public:
    double get(string s);                           // return the value of the Variable named s
    void set(string s, double d);                   // set the Variable named s to d
    bool is_declared(string var);                   // is var already in var_table?
    double declare(string var, double val); // add (var,val) to var_table
  private:
    vector<Variable> var_table; // vector of Variables
};

// return the value of the Variable named s
double Variable_table::get(string s)
{
    for (auto i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == s)
            return var_table[i].value;
    }
        
    error("get: undefined variable ", s);
}

// set the Variable named s to d
void Variable_table::set(string s, double d)
{
    for (auto i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == s)
        {
            var_table[i].value = d;
            return;
        }
    }
        
    error("set: undefined variable ", s);
}

// is var already in var_table?
bool Variable_table::is_declared(string var)
{
    for (auto i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == var)
            return true;
    }
        
    return false;
}

// add (var,val) to var_table
double Variable_table::declare(string var, double val)
{
    if (is_declared(var))
        error(var, " is declared twice!");
    var_table.push_back(Variable(var, val));
    return val;
}

// -----------------------------------------------------------------------

Token_stream ts;     // provides get() and putback()
Variable_table vt;   // provides get(), set(), is_declared() and declare()
double expression(); // declaration so that primary() can call expression()

// -----------------------------------------------------------------------

// deal with numbers, unary +/-, parentheses, sqrt, pow, names and assignments
// calls expression()
double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(': // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case '-':
        return -primary();
    case '+':
        return primary();
    case number:
        return t.value;
    case name:
    {
        Token t2 = ts.get(); // check next token
        if (t2.kind == '=')
        { // handle name '=' expression
            double d = expression();
            vt.set(t.name, d);
            return d;
        }
        // not an assignment
        ts.putback(t2);
        return vt.get(t.name);
    }
    default:
        error("Expected a primary value.");
    }
}

// -----------------------------------------------------------------------

// deal with *, / and %
// calls primary()
double term()
{
    double left = primary();
    Token t = ts.get(); // get the next token from Token_stream

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
                error("Cannot divide by zero!");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            int i1 = int(left);
            if (i1 != left)
                error("left-hand operand of % not int");
            int i2 = int(d);
            if (i2 != d)
                error("right-hand operand of % not int");
            if (i2 == 0)
                error("%: divide by zero");
            left = i1 % i2;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t); // put t back into the Token_stream
            return left;
        }
    }
}

// -----------------------------------------------------------------------

// deal with + and -
// calls term()
double expression()
{
    double left = term(); // read and evaluate a Term
    Token t = ts.get();   // get the next Token from the Token stream

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term(); // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term(); // evaluate Term and subtract
            t = ts.get();
            break;
        case '=':
            error("Use of '=' outside of a declaration!");
        default:
            ts.putback(t); // put t back into the token stream
            return left;   // finally: no more + or -; return the answer
        }
    }
}

// -----------------------------------------------------------------------

// assume we have seen "let" or "const"
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
double declaration()
{
    Token t = ts.get();
    if (t.kind != name)
        error("Name expected in declaration!");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("'=' missing in declaration of ", var_name);

    double d = expression();
    vt.declare(var_name, d);
    return d;
}

// -----------------------------------------------------------------------

// handles declarations and expressions
double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

// -----------------------------------------------------------------------

// clean input after error
void clean_up_mess() { ts.ignore(print); }

// -----------------------------------------------------------------------

const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

// expression evaluation loop
void calculate()
{
    while (cin)
    {
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get(); // first discard all "prints"
            if (t.kind == quit)
                return; // Quit out

            ts.putback(t);
            cout << result << statement() << endl;
        }
        catch (exception &e)
        {
            cerr << e.what() << endl; // write error message
            clean_up_mess();
        }
    }  
}

// -----------------------------------------------------------------------

int main() try
{
    // predefine names:
    vt.declare("pi", 3.1415926535);
    vt.declare("e", 2.7182818284);

    calculate();

    keep_window_open(); // cope with Windows console mode
    return 0;
}
catch (exception &e)
{
    cerr << "exception: " << e.what() << endl;
    keep_window_open("~~");
    return 1;
}
catch (...)
{
    cerr << "exception\n";
    keep_window_open("~~");
    return 2;
}