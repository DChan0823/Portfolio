/**
 * Word.java
 * @author Derek Chan
 * Description: This class is an extension of the Token class. It is
 * responsible for holding the reserved words, identifiers, operators, and
 * composite tokens like !=.
 * Part of design is from Aho.
 */
package lexer;

public class Word extends Token {
    
    public String lexeme = "";
    
    //constructor for Word
    //stores tokenNumber into Token class field
    //stores lexeme into Word class field
    public Word(String s, int num) 
    { 
        super(num); lexeme = s;
    }
    
    @Override
    public String toString() { return lexeme; }
    
    //initialized operators and composite operators
    //used for later easy creation of objects
    //used for easy comparison
    public static final Word
            addition = new Word("+", TokenNumber.ADDOP), 
            subtraction = new Word("-", TokenNumber.ADDOP),
            multiplication = new Word("*", TokenNumber.MULTOP),
            division = new Word("/", TokenNumber.MULTOP),
            eq = new Word("=", TokenNumber.RELOP),
            ne = new Word("!=", TokenNumber.RELOP),
            lt = new Word("<", TokenNumber.RELOP),
            gt = new Word(">", TokenNumber.RELOP),
            leftParen = new Word("(", TokenNumber.LP),
            rightParen = new Word(")", TokenNumber.RP),
            semi = new Word(";", TokenNumber.SEMICOLON),
            boolNot = new Word("!", TokenNumber.NOT),
            dot = new Word(".", TokenNumber.DOT),
            colonEqual = new Word (":=", TokenNumber.COLONEQUAL);
}
