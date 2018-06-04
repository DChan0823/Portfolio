/**
 * Player.java
 * @author Derek Chan
 * A part of the Candyland program that handles operations associated with the
 * player of the game. Holds the name and the current position of the player.
 * has getters method for both name and position and setter method for the position.
 */
package hw2;

public class Player 
{
    
    private String name;
    private int position;
    
    final int INITIAL_POSITION = -1;
    
    public Player (String n)
    {
        name = n;
        position = INITIAL_POSITION;
    }
    
    //getter
    public String getName()
    {
        return name;
    }
    
    //getter
    public int getPosition()
    {
        return position;
    }
    
    
    public void setPosition(int newPosition)
    {
        position = newPosition;
    }
    
}
