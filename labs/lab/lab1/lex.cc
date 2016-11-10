#include "lex.hh"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//
// Human-readable representations of token types
//

static char *kTokenTypeNames[] =
{
    "uninitialized",
    "number",
    "identifier",
    "plus",
    "minus",
    "times",
    "divide",
    "left paren",
    "right paren",
    "assignment",
    "end of file",
    "end of line",
    "power"
};

//
// Reset resets the scanner to a reasonably safe state
//

void Scanner::Reset(void)
{
    position = 0;
    state = 0;
    memset(valueBuffer, '\0', kMaxTokenLength);
}

//
// GetChar returns the next input character. It uses stdio because I
// failed to get blocking input when using the get method of istream.
//

char Scanner::GetChar(void)
{
    int c;

    if (haveBuffered)
    {
        haveBuffered = 0;
        return bufferedChar;
    }
    else
    {
        cin.sync_with_stdio();
        c = getc(stdin);
        if (c == EOF)
            return -1;
        else
            return c;
    }
}

//
// The scanner sometimes needs to put back a single character onto the
// input stream. This function does it.
//

void Scanner::PutbackChar(unsigned char c)
{
    haveBuffered = 1;
    bufferedChar = c;
}


//
// Scan is the only publicly callable functions. It simple resets the
// scanner and then recognizes a single token.
//

Token Scanner::Scan(void)
{
    int c;
    
    Reset();
    while (1)
    {
        c = GetChar();
        
        switch (state)
        {
        case 0:                     // Initial state
            if (isdigit(c))
            {
                Accumulate(c);
                state = 1;
            }
            else if (isalpha(c))
            {
                Accumulate(c);
                state = 6;
            }
            else switch(c)
            {
            case -1: return Token(kEndMark);
            case ' ':
            case '\t':
            case '\r': break;
            case '\n': return Token(kEndOfLine);
            case '*': return Token(kTimes);
            case '+': return Token(kPlus);
            case '-': return Token(kMinus);
            case '/': return Token(kDivide);
            case '(': return Token(kLeftParen);
            case ')': return Token(kRightParen);
            case '^': return Token(kPower);
            case '.': Accumulate(c); state = 8; break;
            case ':': state = 7; break;
            default:
                throw ScannerError(c, state);
            }
            break;

        case 1:
            if (isdigit(c))
            {
                Accumulate(c);
                state = 1;
            }
            else switch (c)
            {
            case 'E': Accumulate(c); state = 3; break;
            case 'e': Accumulate(c); state = 3; break;
            case '.': Accumulate(c); state = 2; break;
            default:
                PutbackChar(c);
                return Token(kNumber, NumberValue());
            }
            break;

        case 2:
            if (isdigit(c))
            {
                Accumulate(c);
                state = 2;
            }
            else switch (c)
            {
            case 'E': Accumulate(c); state = 3; break;
            case 'e': Accumulate(c); state = 3; break;
            default:
                PutbackChar(c);
                return Token(kNumber, NumberValue());
            }
            break;

        case 3:
            if (isdigit(c))
            {
                Accumulate(c);
                state = 5;
            }
            else switch(c)
            {
            case '+': Accumulate(c); state = 4; break;
            case '-': Accumulate(c); state = 4; break;
            default:
                throw ScannerError(c, state);
            }
            break;

        case 4:
            if (isdigit(c))
            {
                Accumulate(c);
                state = 5;
            }
            else
            {
                throw ScannerError(c, state);
            }
            break;

        case 5:
            if (isdigit(c))
            {
                Accumulate(c);
                state = 5;
            }
            else
            {
                PutbackChar(c);
                return Token(kNumber, NumberValue());
            }
            break;

        case 6:
            if (isdigit(c) || isalpha(c))
            {
                Accumulate(c);
                state = 6;
            }
            else
            {
                PutbackChar(c);
                return Token(kIdentifier, SymbolValue());
            }
            break;

        case 7:
            if (c == '=')
                return Token(kAssign);
            else
                throw ScannerError(c, state);
            break;

        case 8:
            if (isdigit(c))
            {
                Accumulate(c);
                state = 2;
            }
            else
            {
                throw ScannerError(c, state);
            }
            break;

        default:
            cerr << "Scanner bug. Entered unknown state " << state << '\n';
            throw ScannerError("Unkown state");
        }
    }
}

//
// Accumulate buffers a character for later use in a
// multiple-character token.
//

void Scanner::Accumulate(char c)
{
    if (position >= kMaxTokenLength)
    {
        valueBuffer[kMaxTokenLength - 1] = 0;
        cerr << "Token too long: " << valueBuffer << '\n';
        throw ScannerError("Token too long");
    }
    else
    {
        valueBuffer[position] = c;
        position += 1;
    }
}


//
// NumberValue converts accumulated characters to a double
//

double Scanner::NumberValue(void)
{
    return atof(valueBuffer);
}

//
// SymbolValue returns a copy of the accumulated characters as a
// NUL-terminated string
//

char *Scanner::SymbolValue(void)
{
    char *tmp;

    tmp = new char[position + 1];
    memcpy(tmp, valueBuffer, position);
    tmp[position] = 0;

    return tmp;
}


ostream& operator<<(ostream& s, Token &t)
{
    switch (t.type)
    {
    case kNumber:
        return s << "(token " << t.Lookup(t.type) << ' '
                 << t.numberValue << ')';
    case kIdentifier:
        return s << "(token " << t.Lookup(t.type) << ' '
                 << t.symbolValue << ')';
    default:
        return s << "(token " << t.Lookup(t.type) << ')';
    }
}

ostream& operator<<(ostream& s, ScannerError& e)
{
    if (e.errorCharacter)
    {
        return s << "(error char='" << e.errorCharacter <<"' state=" << e.state << ')';
    }
    else
    {
        return s << "(error \"" << e.message << "\")";
    }
}

//
// Lookup just returns the textual representation of a token type. The
// no argument version returns the type of the token.
//

char *Token::Lookup(void)
{
    return kTokenTypeNames[type];
}

char *Token::Lookup(TokenType t)
{
    return kTokenTypeNames[t];
}
