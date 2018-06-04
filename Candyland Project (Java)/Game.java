/**
 * Game.java
 * @author Derek Chan
 * A part of the Candyland program that handles operations associated with the
 * game itself. Functions: draws the cards, adding players, prints introduction,
 * checks for winner, prints winner, and plays the game.
 */
package hw2;

import java.util.*;

class Game {
    
    final int MIN_NUM_PLAYERS = 2;
    final int MAX_NUM_PLAYERS = 6;
    int nextDraw = 0;
    
    Board board;
    
    List<Player> listOfPlayers = new ArrayList<>();
    
    public Game() 
    {
        board = new Board();
    }
    
    // Description: Display welcome string
    public void printIntro() {
        
        System.out.println("This is a crude version of Candyland\n");
    }
   
    // Generate the next value "drawn"
    // Returns: the value of the next card drawn. Returning the null indicates
    //          there are no more values
    public Card draw() {
        Face testRollsFaceOrder[] = {Face.PLUMPY, Face.YELLOW, Face.RED, 
            Face.YELLOW, Face.GREEN, Face.MR_MINT, Face.JOLLY, Face.RED, 
            Face.GREEN, Face.ORANGE, Face.GREEN, Face.YELLOW, Face.RED};
        
        boolean testRollsRepeat[] = {false, true, false, true, false, false, 
            false, false, false, true, false, false, false};
        
        final int NUM_CARDS = testRollsFaceOrder.length;
        
        Card testRolls[] = new Card[NUM_CARDS];
        
        for(int i = 0; i < NUM_CARDS; i++)
        {
            testRolls[i] = new Card(testRollsFaceOrder[i], testRollsRepeat[i]);
        }
    
        if (nextDraw >= NUM_CARDS) return null;
        return testRolls[nextDraw++];
    }
    
    //Adds name of players to the List of player
    public void addPlayers()
    {
        System.out.println("Enter the names of the players (2 to 6), ending with 'done':");
        
        Scanner in = new Scanner(System.in);
        
        Player newPlayer;
        
        do
        {
            String line = in.nextLine();
            
            if(line.equals("done"))
            {
                break;
            }
            
            newPlayer = new Player(line);
            
            listOfPlayers.add(newPlayer);
            
        }while(listOfPlayers.size() < MAX_NUM_PLAYERS);
        
        if (listOfPlayers.size() < MIN_NUM_PLAYERS)
        {
            throw new Error("Not Enough Players. Ending Game."); 
        }
    }

    // Description: Check for a winner
    // Parameters: none
    // Returns: true if there are no winners yet
    //          false if anyone has won
    public boolean nowinner() {
        for (int player = 0; player < listOfPlayers.size(); player++) {
            if (listOfPlayers.get(player).getPosition() == board.winningPosition()) // reached the end
               return false;
            }
        return true;
    }
    
    // Print the identity of the winner, if any.
    // If there are no winners, do nothing.
    // Parameters: none
    void printWinner() {
        for (int player = 0; player < listOfPlayers.size(); player++) {
            // Would be clearer to use a different constant to
            // explicitly define the winning position
            if (listOfPlayers.get(player).getPosition() == board.winningPosition())
                //cout << "Player " << player << " wins!" << endl;
                System.out.print("Player " + listOfPlayers.get(player).getName() + " wins!\n");
        }
    }
    
    // Description: Play the game
    public void playGame() {
        // Use nextPlayer to switch among the players
        int nextPlayer = 0;
        boolean done = false;
        
        printIntro();

        addPlayers();
        
        //while no winner is found and still have cards in testRolls
        //draw cards and assign position to player in List.
        //displays card drawn and ending position of players turn
        //displays winner or no winner
        while (nowinner() && !done) {
            Card nextCard = draw();

            if (nextCard != null) {
                
                System.out.print(listOfPlayers.get(nextPlayer).getName() + " draws a ");
            
                if(nextCard.isDoubled())
                {
                    System.out.println("double " + nextCard.getFace().getName());
                }
                else
                {
                    System.out.println(nextCard.getFace().getName());
                }
                
                listOfPlayers.get(nextPlayer).setPosition(board.move(listOfPlayers.get(nextPlayer).getPosition(), nextCard));
            
                System.out.println("Player " + listOfPlayers.get(nextPlayer).getName() + 
                        " is at position " + listOfPlayers.get(nextPlayer).getPosition());
                nextPlayer = (nextPlayer + 1) % listOfPlayers.size();
            } else done = true;
        }
        if (nowinner())
           
            System.out.println("No winner");
        else printWinner();
    }
}
