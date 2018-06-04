/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package parser;

import lexer.*;
import java.io.*;
import java.util.*;
/**
 *
 * @author Derek
 */
public class ParserDriver {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        
        Scanner inFile = new Scanner( new File("input.txt"));
        
        Lexer lex = new Lexer();
        
        Parser pars = new Parser(lex);
        
        pars.startParse();
    }
    
}
