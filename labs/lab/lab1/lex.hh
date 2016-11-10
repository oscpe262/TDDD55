#ifndef KOMP_LEX_H
#define KOMP_LEX_H

#include <iostream>

using namespace std;

//
// In a real-life scanner, tokens should be able to have arbitrary
// lenth. In this scanner, tokens are limited to 1023 characters for
// simplicity.
//

const int kMaxTokenLength = 1024;

//
// Objects of the class ScannerError are thrown by the scanner if it
// encounters an error. The instance variable errorCharacter contains
// the character that caused the error. If it is zero, it is possible
// that the error was not caused by bad input. The instance variable
// message contains an error message or is NULL. The instance variable
// state contains the state the scanner was in when it encountered the
// error. This is really only useful for debugging the scanner itself.
//
// The << operator is defined for ScannerError, so it is easy to print
// it.
//

class ScannerError
{
public:
    char errorCharacter;
    char *message;
    int  state;

    ScannerError(char c, int s) : errorCharacter(c), state(s) {};
    ScannerError(char *s) : message(s) {};
    ScannerError()       : errorCharacter(0) {};
};



//
// The class Token represents a single token. It has a field named
// type which is used to discriminate between different types of
// tokens. The valid token types are listed in the TokenType enum.
//
// The field numberValue is valid only if the token is a number, in
// which case it is the value of the number. The field symbolValue is
// only valid if the token is a symbol, in which case it is a string
// containing the symbol.
//
// The << operator is defined for Token, so it is easy to print it.
//
// If you want a textual representation of a token type, call the
// Lookup method in Token. With no arguments it returns a string
// representation of the token's own type. With a TokenType argument
// it returns the textual representation of that token type.
//
// If you change the set of possible tokens, don't forget to change
// the list in lex.cc which contains a textual representation of the
// token types.
//

typedef enum
{
    kUninitialized = 0,
    kNumber = 1,
    kIdentifier = 2,
    kPlus = 3,
    kMinus = 4,
    kTimes = 5,
    kDivide = 6,
    kLeftParen = 7,
    kRightParen = 8,
    kAssign = 9,
    kEndMark = 10,
    kEndOfLine = 11,
    kPower
} TokenType;

class Token
{
public:
    TokenType       type;
    double          numberValue;
    char           *symbolValue;

    char *Lookup(TokenType);
    char *Lookup(void);
    Token() : type(kUninitialized) {};
    Token(TokenType t) : type(t) {};
    Token(TokenType t, double x) : type(t), numberValue(x) {};
    Token(TokenType t, char *s) : type(t), symbolValue(s) {};
};

//
// The Scanner class is a scanner. Too use it, simply create an
// instance of Scanner and call the Scan method, which is the only
// public method in the class. The Scan method will return an instance
// of Token containing the next token in the input stream. Note that
// Scan will block until a token is available.
//

class Scanner
{
    int                 state;
    int                 haveBuffered;
    unsigned char       bufferedChar;
    char                valueBuffer[kMaxTokenLength + 1];
    long                position;

    void Reset(void);
    void Accumulate(char);
    void PutbackChar(unsigned char);
    char *SymbolValue(void);
    double NumberValue(void);
    char GetChar(void);

public:
    Token Scan(void);
    Scanner() { haveBuffered = 0; Reset(); };
};

ostream& operator<<(ostream&, Token &);
ostream& operator<<(ostream&, ScannerError &);

#endif
