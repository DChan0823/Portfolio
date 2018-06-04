/**
 * Card.java
 * @author Derek Chan
 * A part of the Candyland program that handles operations associated with the
 * Cards drawn in the Candyland game. Holds the face value as an object, holds 
 * boolean value for if its a double card. Methods: getters for variables and
 * an overwritten toString method
 */
package hw2;

public class Card {
    
    private Face face;
    private boolean isDouble;
    
    public Card(Face f, boolean d)
    {
        face = f;
        isDouble = d;
    }
    
    //getter
    public Face getFace()
    {
        return face;
    }
    
    //getter
    public boolean isDoubled()
    {
        return isDouble;
    }
    
    //Overwritten toString method
    @Override
    public String toString()
    {
        if(isDouble)
        {
            return "double " + face.toString();
        }
        else
        {
            return face.toString();
        }
    }
    
}
