/**
 * Face.java
 * @author Derek Chan
 * A part of the Candyland program that holds the enumeration of the Face value
 * of the cards drawn in Candyland.
 */
package hw2;

public enum Face 
{
    BLUE("BLUE", false),
    GREEN("GREEN", false),
    ORANGE("ORANGE", false),
    PURPLE("PURPLE", false),
    RED("RED", false),
    YELLOW("YELLOW", false),
    PLUMPY("PLUMPY", true),
    MR_MINT("MR. MINT", true),
    JOLLY("JOLLY", true);
    
    private final String name;
    private final boolean isCharacter;
    
    Face(String _name, boolean _isCharacter)
    {
        name = _name;
        isCharacter = _isCharacter;
    }
    
    //getter
    public String getName()
    {
        return name;
    }
    
    //getter
    public boolean getIsCharacter()
    {
        return isCharacter;
    }
}
