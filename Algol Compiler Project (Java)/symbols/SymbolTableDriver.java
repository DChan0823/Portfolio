/**
 * SymbolTableDriver.java
 * @author Derek Chan
 * Description: Driver program to show implementation of the SymbolTable class.
 * Program reads in an input file of symbols with '{' and '}' denoting opening
 * and closing of scopes. Each scope has its own HashTable. HashTable holds
 * key-value pairs where the symbol names are keys. The symbols are
 * stored in the HashTable of its current scope as an object. Closed scopes are stored in
 * a SymbolTable array with position corresponding to their scope number (this
 * makes final Symbol Table Dump convenient and pretty). Outputs which scope 
 * symbols are inserted into. Outputs final Symbol Table Dump.
 */
package symbols;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class SymbolTableDriver {

    public static void main(String[] args) 
    {
        SymbolTable currScope = null;       //for tracking current scope
        SymbolTable closedScope = null;     //to hold closeScope pointer     
        SymbolTable tempScope;              //to temp hold a ST pointer
        String line;                        //used to hold a symbol from file
        int scopeNum = -1;                  //integer value of scope location
        
        //used to hold finished/closed scopes for later printing
        SymbolTable [] closedScopeArray = new SymbolTable[100];
        
        //Program Start
        System.out.println("Program Initialized...");
        System.out.println("Reading file...");
        
        //opening of file, try-catch for IOException
        try(Scanner in = new Scanner(new File("input.txt")))
        {
            //while file still has words to be read
            while(in.hasNext()) 
            {
                line = in.next();           //read in a symbol
                
                //if symbol is '{' initialize a new scope(SymbolTable)
                if("{".equals(line))
                {
                    SymbolTable newScope = new SymbolTable(currScope);
                    currScope = newScope;
                    scopeNum++;
                    currScope.scopeNum = scopeNum;
                }
                //else if symbol is '}' close scope and store closed scope in
                //closedScopeArray with position as its scopeNum
                else if ("}".equals(line))
                {
                    tempScope = closedScope;
                    closedScope = currScope;
                    
                    closedScopeArray[closedScope.scopeNum] = closedScope;
                    
                    currScope = currScope.prev;
                    closedScope.prev = tempScope;
                }
                //search to see if symbol is already in current Scope
                //if yes, do not insert to current scope.
                //if not, search other open scopes
                //if yes in other open scopes, insert into current scope
                //if not in other open scopes, insert into current scope.
                else
                {
                    if(currScope.findLocal(line) != null)
                    {
                        System.out.println(line + " already in current scope." +
                                " Not inserted.");
                    }
                    else if(currScope.findAll(line) != null)
                    {
                        System.out.print(line + " NOT in local, but IS in global.");
                        System.out.println("Inserted into current Scope " + currScope.scopeNum);
                        
                        Symbol newSymbol = new Symbol(line);
                        
                        currScope.insert(line, newSymbol);
                    }
                    else
                    {
                        System.out.println(line + " inserted in Scope " + currScope.scopeNum);
                        
                        Symbol newSymbol = new Symbol(line);
                        
                        currScope.insert(line, newSymbol);
                    }
                }
            }
            
            in.close();
        }
        catch (IOException e) 
        {
          System.out.println(e);
        }
        
        //FINAL SYMBOL TABLE DUMP
        System.out.println("\nSYMBOL TABLE DUMP");
        
        int i = 0;
        
        //Prints out all finished closed Scopes, in ascending scope order
        while(closedScopeArray[i] != null)
        {
            System.out.print("Scope " + i + ": ");
            closedScopeArray[i].display();
            
            i++;
        }
    }
    
}
