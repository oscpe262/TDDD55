#include "lab1.hh"


//
// The trace class needs a class variable. This is it
//

int Trace::indent = 0;


//
// Parse should be the entry point to your parser class. It will be
// called by the main program, which you also have to write.
//

double Parser::Parse(void)
{
    Trace       x("Parse");     // Trace execution of Parse
    double      val;            // Value of a statement

    currentToken = scanner.Scan();

    switch (currentToken.type) {
      case 1:
      case 2:
        val = E();
        break;
      default: Recover();
    }

    return val;

    /* --- Your code here ---
     *
     * Parse the input using recursive descent parsing. You'll need
     * an object of type Scanner to get tokens from the input. Call
     * the Scan method of this object to get the next token in the
     * input stream.
     */

    /* --- End your code --- */

}

void Parser::Recover(void)
{

    cerr << "Error recovery.\n" << flush;

    /* --- Your code here ---
     *
     * Error recovery routine
     *
     * Unless you come up with something better, this function should
     * scan tokens until it sees the end of line or end of file.
     * Parsing may be resumed at that point. This means that if an end
     * of line token caused the error, this routine doesn't need to do
     * anything.
     *
     * Be sure not to scan more tokens than necessary, or it won't be
     * possible to resume parsing.
     */

    /* --- End your code --- */
}

// E -> T (+T | -T)* £
double Parser::E(void) {
  Trace etrace("E");
  double val;
  while(1) {
    switch (currentToken.type) {
      case 1:
        val = T();
        break;
      case 3:
        currentToken = scanner.Scan();
        val = val + E_();
        break;
      case 4:
        currentToken = scanner.Scan();
        val = val - E_();
        break;
      default:
        return val;
    }
  }
}

/* E' ->  +E
      |   -E
      |   €       */
double Parser::E_(void) {
  Trace e_trace("E_");
  double val;
  while(1) {
    switch (currentToken.type) {
      case 1:
        val = T();
        break;
      case 3:
        currentToken = scanner.Scan();
        return val;
        break;
      case 4:
        currentToken = scanner.Scan();
        return val;
        break;
      case 5:
        currentToken = scanner.Scan();
        val = val * T();
      default:
        return val;
    }
  }
}

double Parser::T(void) {
  Trace ttrace("T");
  double val;
  switch (currentToken.type) {
    case 1:
      val = currentToken.numberValue;
      currentToken = scanner.Scan();
      break;
    default:
    ;
  }

  return val;
}
