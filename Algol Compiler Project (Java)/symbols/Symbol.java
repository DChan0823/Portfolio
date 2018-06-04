/**
 * SymbolTable.java
 * @author Derek Chan
 * Description: Simple Symbol Object to hold attributes of symbols. Currently
 * just one attribute: name.
 */
package symbols;

public class Symbol {
    private String name;
    
    public Symbol(String n){
        name = n;
    }
    
    public String getName() {
        return name;
    }
}
