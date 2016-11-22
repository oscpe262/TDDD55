//
// parser.hh
//
// Skeleton header file for your parser class. You will probably need more
// methods and instance variables in the parser class.
//


#ifndef KOMP_LABONE_H
#define KOMP_LABONE_H

#include <iostream>
#include "lex.hh"

using namespace std;

class Parser
{
    Scanner scanner;
    Token   currentToken;

    double E(void);
    double E_(void);
    double T(void);
public:
    void Recover(void);         // Error recovery routine
    double Parse(void);         // Main entry point
};

class Trace
{
    static int indent;
    char *name;

public:
    Trace(char *s)
    {
        name = s;
        cerr.width(indent);
        cerr << " ";
        cerr << "--> " << name << '\n' << flush;
        indent += 4;
    };

    ~Trace()
    {
        indent -= 4;
        cerr.width(indent);
        cerr << "";
        cerr << "<-- " << name << '\n' << flush;
    };
};

//
// Two error classes that you may find useful. You can thrown
// ParserError to signal an error in parsing and ParserEndOfFile to
// signal an end of file. There are other alternatives to error
// reporting that may be more convenient.
//

class ParserError {};
class ParserEndOfFile {};

#endif
