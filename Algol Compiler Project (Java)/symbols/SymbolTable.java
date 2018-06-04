/**
 * SymbolTable.java
 * @author Derek Chan
 * Description: SymbolTable class implements chained symbol tables. Constructor,
 * insert, and findAll method are similar to Aho's Class Env on pg. 89 of 2nd Ed
 */
package symbols;

import java.util.*;

public class SymbolTable {
    private Hashtable table;            //hashtable of symbols
    protected SymbolTable prev;         //pointer to prev scope
    protected int scopeNum;             //scope number for tracking
    
    /*
    * SymbolTable constructor
    * Pre-conditon: Takes a SymbolTable parameter
    * Post-condition: new hashtable of symbols for current scope is init
    */
    public SymbolTable(SymbolTable p) {
        table = new Hashtable(); prev = p;
    }
    
    /*
    * insert method
    * Description: insert symbol into hashtable
    * Pre-conditon: Takes a string key(symbol name) parameter, takes a Symbol
    * object parameter
    * Post-condition: Hashtable has new symbol inserted
    */
    public void insert(String s, Symbol sym){
        table.put(s, sym);
    }
    
    /*
    * findAll method
    * Description: search for symbol name in all open scopes
    * Pre-conditon: Takes a symbol name string parameter
    * Post-condition: returns Symbol object if found in hashtable of all
    * open scopes, else returns null.
    */
    public Symbol findAll(String s){
        for(SymbolTable e = this; e != null; e = e.prev) {
            Symbol found = (Symbol)(e.table.get(s));
            
            if(found != null) return found;
        }
        return null;
    }
    
    /*
    * findLocal method
    * Description: search for symbol name in current scope
    * Pre-conditon: Takes a symbol name string parameter
    * Post-condition: returns Symbol object if found in hashtable of current
    * open scopes, else returns null.
    */
    public Symbol findLocal(String s){
        Symbol found = (Symbol)(table.get(s));
        
        if(found != null)
            return found;
        else
            return null;
    }
    
    /*
    * display method
    * Description: outputs all symbols in scope
    * Pre-conditon: Hashtable table should not be empty.
    * Post-condition: outputs all symbols in scope
    */
    public void display(){
        Enumeration e = table.keys();
        while (e.hasMoreElements())
        {
            System.out.print(e.nextElement());
            System.out.print(" ");
        }
        System.out.print("\n");
    }
}
