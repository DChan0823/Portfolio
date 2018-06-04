/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package parser;

import lexer.*;
/**
 *
 * @author Derek
 */
public class Parser {
    private Lexer lex;
    private Token look;
    int used = 0;
    
    public Parser(Lexer one)
    {
        lex = one;
        
        move();
    }
    
    void move() { look = lex.getToken(); }
    
    void error(String s) { throw new Error("near line " + lex.lineNum + ": " + s); }
    
    void match(int t) 
    {
        if(look.tokenNum == t)
            move();
        else
            error("syntax error");
    }
    
    public void startParse()
    {
        program();
    }
    
    public void program()
    {
        
    }
}
