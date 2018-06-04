/**
 * TokeNumber.java
 * @author Derek Chan
 * Description: This class holds the TokenNumber constants for all the types
 * of tokens in Baby Algol. These numbers will be stored corresponding to the
 * type of token for later identification.
 * The FAIL state token number is -1. I included it to help make it easier
 * display illegal tokens, even though there is tech no FAIL token in Baby Algol
 * Part of design is from Aho.
 */
package lexer;

public class TokenNumber {
    
    public final static int
            FAIL = -1,
            IDENT = 1, LITERAL = 2, TYPE = 3, ADDOP = 4, MULTOP = 5, RELOP = 6,
            BEGIN = 7, END = 8, IF = 9, THEN = 10, WHILE = 11, DO = 12, 
            INTEGER = 3, STRING = 3, LOGICAL = 3, TRUE = 2, FALSE = 2, 
            DIV = 5, REM = 5, OR = 4, AND = 5, READ = 13, WRITE = 13, 
            WRITELN = 13, LP = 14, RP = 15, SEMICOLON = 16, NOT = 17,
            DOT = 18, COLONEQUAL = 19;
    
}
