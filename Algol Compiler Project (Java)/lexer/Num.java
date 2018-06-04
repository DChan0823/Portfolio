/**
 * Num.java
 * @author Derek Chan
 * Description: This class is an extension of the Token class. It incorporates
 * another field to hold the value of the Numerical token. Has an overrided
 * toString functino for easy printing.
 * Part of design is from Aho.
 */
package lexer;

public class Num extends Token {
    
    public final int value;
    
    //constructor
    //stores the Token Number for an integer (literal) into Token field
    //stores value of integer into Num field
    public Num(int v) 
    { 
        super(TokenNumber.LITERAL); value = v; 
    }
    
    @Override
    public String toString() {return "" + value;}
}
