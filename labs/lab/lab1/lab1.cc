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

    val = 0;

    /* --- Your code here ---
     *
     * Parse the input using recursive descent parsing. You'll need
     * an object of type Scanner to get tokens from the input. Call
     * the Scan method of this object to get the next token in the
     * input stream. 
     */

    /* --- End your code --- */

    return val;
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

