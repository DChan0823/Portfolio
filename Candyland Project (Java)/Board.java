/**
 * Board.java
 * @author Derek Chan
 * A part of the Candyland program that handles operations associated with the
 * board. Contains an array that represents the board. Methods: findFace returns
 * the position number of the particular face card, move method calculates
 * the position
 */
package hw2;

class Board {
    
    final int PLUMPY_POS = 8;
    final int MR_MINT_POS = 17;
    final int JOLLY_POS = 42;
    
    // A partial board for Candyland
    // based on the picture at: http://www.lscheffer.com/CandyLand-big.jpg
    Face board[] = {Face.RED, Face.PURPLE, Face.YELLOW, Face.BLUE, Face.ORANGE, 
                  Face.GREEN, Face.RED, Face.PURPLE, Face.PLUMPY, Face.YELLOW,
                  Face.BLUE, Face.ORANGE, Face.GREEN, Face.RED, Face.PURPLE, 
                  Face.YELLOW, Face.BLUE, Face.MR_MINT, Face.ORANGE, Face.GREEN,
                  Face.RED, Face.PURPLE, Face.YELLOW, Face.BLUE, Face.ORANGE, 
                  Face.GREEN, Face.RED, Face.PURPLE, Face.YELLOW, Face.BLUE,
                  Face.ORANGE, Face.GREEN, Face.RED, Face.PURPLE, Face.YELLOW,
                  Face.BLUE, Face.ORANGE, Face.GREEN, Face.RED, Face.PURPLE,
                  Face.YELLOW, Face.BLUE, Face.JOLLY, Face.ORANGE, Face.GREEN,
                  Face.RED, Face.PURPLE, Face.YELLOW, Face.BLUE, Face.ORANGE 
               };

    private final int FINAL_POSITION = board.length;
    
    // Description: Starting after indicated position search forward on board to find the color
    // Parameters: startPos -- index of current space of player -- start looking *after* this space
    //             face -- find the next space with this face card
    // Returns: index of next space of chosen face card
    public int findFace(int startPos, Face face) {
        if (face == Face.PLUMPY) return PLUMPY_POS;
        if (face == Face.MR_MINT) return MR_MINT_POS;
        if (face == Face.JOLLY) return JOLLY_POS;
        
        for (int pos = startPos+1; pos < FINAL_POSITION; pos++)
            if (board[pos].equals(face))
                return pos;
        return FINAL_POSITION;
    }
       
    // Description: Move a player
    // Parameters: player -- index of player to move
    //             card -- particular drawn face card
    //Returns: index for the next position of this current player
    public int move(int player, Card card) 
    {
        int nextPos = player;
        
        nextPos = findFace(nextPos, card.getFace());
        if (card.isDoubled())
            nextPos = findFace(nextPos, card.getFace());
        return nextPos;
    }
    
    //Returns the index of the winning position
    public int winningPosition()
    {
        return FINAL_POSITION;
    }
}
