/**
 * Token.java
 * @author Derek Chan
 * Description: This objects from this class are Tokens and hold the token
 * number for the specific token. Has an overrided toString method for easy
 * printing.
 * Part of design is from Aho.
 */
package lexer;

public class Token {
    
    public final int tokenNum;
    
    public Token(int t) { tokenNum = t;}
    
    //getters
    public int getTokNum()
    {
        return tokenNum;
    }
    
    @Override
    public String toString() { return "" + (char)tokenNum; }
}
