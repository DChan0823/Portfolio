/**
 * Lexer.java
 * @author Derek Chan
 * Description: This class holds the majority of the processing methods for the
 * program. The main method in Lexer, function getToken, recognizes numbers,
 * identifiers, and reserved words. 
 * The getToken method begins by skipping white spaces. It will then recognize
 * integers, identifiers, keywords, or operators. Once a token is found, it is
 * returned.
 * The readch method is used to read the next character of the buffer. 
 * The overloaded boolean readch method is used to "peek" at the next 
 * character in the buffer for composite operator matching like !=.
 * Part of design is from Aho.
 */
package lexer;

import java.io.*;
import java.util.*;

public class Lexer {
    
    StringBuffer b;
    
    Scanner inFile;
    
    public static int lineNum = 0;
    
    //peek holds the next char "peeked" from the buffer
    char peek = ' ';
    
    //reserved words hashtable for fast access
    //used for identifier or keyword comparison
    Hashtable words = new Hashtable();
    
    //reserve function to reserve keywords
    void reserve(Word w) { words.put(w.lexeme, w); }
    
    //constructor
    //automatically initialized reserved keywords
    //COMMENT is NOT reserved, though it is reserved in lang defn
    //COMMENT and anything til end of line or next ';' is ignored and does
    //not return a token
    public Lexer() throws IOException
    {   
        reserve( new Word("BEGIN", TokenNumber.BEGIN));
        reserve( new Word("END", TokenNumber.END));
        reserve( new Word("IF", TokenNumber.IF));
        reserve( new Word("THEN", TokenNumber.THEN));
        reserve( new Word("WHILE", TokenNumber.WHILE));
        reserve( new Word("DO", TokenNumber.DO));
        reserve( new Word("INTEGER", TokenNumber.TYPE));
        reserve( new Word("STRING", TokenNumber.TYPE));
        reserve( new Word("LOGICAL", TokenNumber.TYPE));
        reserve( new Word("TRUE", TokenNumber.TRUE));
        reserve( new Word("FALSE", TokenNumber.FALSE));
        reserve( new Word("DIV", TokenNumber.DIV));
        reserve( new Word("REM", TokenNumber.REM));
        reserve( new Word("OR", TokenNumber.OR));
        reserve( new Word("AND", TokenNumber.AND));
        reserve( new Word("READ", TokenNumber.READ));
        reserve( new Word("WRITE", TokenNumber.WRITE));
        reserve( new Word("WRITELN", TokenNumber.WRITELN));
        
        getInputFile();
    }
    
    void getInputFile() throws IOException
    {
        inFile = new Scanner( new File("input.txt"));
    }
    
    //readch method
    //read next char of the buffer
    void readch(StringBuffer b)
    { 
        peek = b.charAt(0); 
    }
    
    //boolean readch
    //"peek" method that checks to see if the next char is part of the composite
    //operator. returns true if it is, false if it isnt.
    boolean readch(char c, StringBuffer b)
    {
        readch(b);
        if(peek != c) return false;
        peek = ' ';
        return true;
    }
    
    void getBuffer()
    {
            //read in a line from program file
            b.append(inFile.nextLine());
            lineNum++;
    }
    
    /*public Token findToken()
    {
        Token newTok;
        
        newTok = getToken();
        
        return newTok;
    }*/
    
    //main method of the class
    //handles the tokenizing of the buffer
    public Token getToken()
    {
        if(b.length() == 0)
        {
            getBuffer();
        }
        
        //while loop skips all white spaces
        //else break and continue tokenizing process
        while(b.length() != 0)
        {
            readch(b);
            if(peek == ' ' || peek == '\t')
            {
                b.deleteCharAt(0);
            }
            else
            {
                break;
            }
        }
        
        //switch statement checks for operators and composite operators
        //if matches, initialize corresponding token and return token. 
        //
        //delete the matching operator or composition operator from buffer because
        //we are finished with them.
        //
        //for composite operators such as != and :=, use boolean readch
        //to check if next char is part of composite operator. If true
        //initialize and return a composite operator token, else return 
        //fail token for ':' or boolNot token for '!'
        //
        //the case for string literal: if peek is a '"', anything after this 
        //opening quotation to the next quotation is a string literal.
        switch(peek)
        {
            case '0':
                if( readch('0', b) || readch(' ', b) )
                {
                    b.deleteCharAt(0);
                    return new Num(0);
                } 
                else
                {
                    b.deleteCharAt(0);
                    break;
                }
            case '+':
                b.deleteCharAt(0);
                return Word.addition;
            case '-':
                b.deleteCharAt(0);
                return Word.subtraction;
            case '*':
                b.deleteCharAt(0);
                return Word.multiplication;
            case '/':
                b.deleteCharAt(0);
                return Word.division;
            case '=':
                b.deleteCharAt(0);
                return Word.eq;
            case '!':
                b.deleteCharAt(0);
                if( readch('=', b) )
                {
                    b.deleteCharAt(0);
                    return Word.ne;
                } 
                else
                {
                    b.deleteCharAt(0);
                    return Word.boolNot;
                }
            case '<':
                b.deleteCharAt(0);
                return Word.lt;
            case '>':
                b.deleteCharAt(0);
                return Word.gt;
            case '(':
                b.deleteCharAt(0);
                return Word.leftParen;
            case ')':
                b.deleteCharAt(0);
                return Word.rightParen;
            case ';':
                b.deleteCharAt(0);
                return Word.semi;
            case '.':
                b.deleteCharAt(0);
                return Word.dot;
            case ':':
                b.deleteCharAt(0);
                if( readch('=', b) )
                {
                    b.deleteCharAt(0);
                    return Word.colonEqual;
                } 
                else
                {
                    return new Word(":", TokenNumber.FAIL);
                }
            case '"':
                //used to hold the string literal
                StringBuffer buff = new StringBuffer();
                
                //append the current peek, which should be "
                buff.append(peek);
                
                //delete " from buffer, we are done with it
                b.deleteCharAt(0);
                
                //if buffer length is 0, means endofline before encountering
                //another closing quotation. this means " is an illegal token
                //because it has no matching closing "
                if(b.length() == 0) return new Word("\"", TokenNumber.FAIL);
                
                //read next character in buffer
                readch(b);
                
                //while loop takes all next characters as part of the string
                //literal until it encounters a closing "
                while(peek != '"')
                {
                    buff.append(peek);
                    
                    b.deleteCharAt(0);
                    
                    //for robustness of program
                    //if buffer length is 0, no reason to continue getToken
                    //buffer needs a refill
                    if(b.length() == 0) break;
                    
                    readch(b);
                }
                
                //for robustness of program
                //if buffer length is 0, no reason to continue getToken
                //buffer needs a refill. And, this also means no closing
                //quotation encountered before end of line, meaning it is an
                //illegal token
                if(b.length() == 0) return new Word(buff.toString(), TokenNumber.FAIL);
                
                b.deleteCharAt(0);
                
                //if case gets to here, it means we have a valid string literal
                //initialize and return valid string literal
                Word w = new Word(buff.toString()+"\"", TokenNumber.LITERAL);
                
                return w;
        }
        
        //if character is a digit, read all next chars until NOT digits.
        //get the value of the read number, initialize and return valid num
        //token.
        //
        //if numerical value is 007 or some such, should be 3 tokens of 0, 0, 7
        if( Character.isDigit(peek) )
        {
            StringBuffer value = new StringBuffer();
            
            while(Character.isDigit(peek))
            {
                value.append(peek);
              
                b.deleteCharAt(0);
                
                //for robustness of program
                //if buffer length is 0, no reason to continue getToken
                //buffer needs a refill
                if(b.length() == 0) break;
                
                readch(b);
            }
            
            //if numerical value begins with a 0
            //it is a illegal numerical token in Baby Algol, return illegal token
            //else it is a valid numerical token and return as such.
            if(value.charAt(0) == '0')
            {
                return new Word(value.toString(), TokenNumber.FAIL);
            }
            else
            {
                return new Num(Integer.parseInt(value.toString()));
            }
        }
        
        //this if statement checks for identifiers and keywords and COMMENTS
        if( Character.isLetter(peek) )
        {
            //holds string for later comparison as ident, keyword, or comment
            StringBuffer buff = new StringBuffer();
          
            //while next char is a letter or a digit
            while(Character.isLetterOrDigit(peek))
            {
                //append letter or digit peek into buff var
                buff.append(peek);
                
                //delete curr char, we done with it.
                b.deleteCharAt(0);
                
                //for robustness of program
                //if buffer length is 0, no reason to continue getToken
                //buffer needs a refill
                if(b.length() == 0) break;
                
                readch(b);
            }
            
            String s = buff.toString();
            
            //if ident is equal to comment
            //means it is a comment and anything afterwards til ';' or eoln
            //is ignored
            if(s.equalsIgnoreCase("COMMENT"))
            {
                while(peek != ';')
                {
                    //delete curr char, it is comment and can be ignored
                    b.deleteCharAt(0);
                    
                    //for robustness of program
                    //if buffer length is 0, no reason to continue getToken
                    //buffer needs a refill
                    if(b.length() == 0) break;
                    
                    readch(b);
                }
                
                if(b.length() == 0) return new Word(buff.toString(), TokenNumber.FAIL);
                
                b.deleteCharAt(0);
                
                return null;
            }
            
            //check to see if the ident is a reserved keyword
            Word w = (Word)words.get(s.toUpperCase());
            
            //if found, return reserve keyword
            if( w != null )
            {
                return w;
            }
            //else it is a new ident, initialize and return as such
            w = new Word(s, TokenNumber.IDENT);
            words.put(s, w);
          
            return w;
        }
        
        //anything else found is an illegal token
        //initialie and return as such
        Word tok = new Word(Character.toString(peek), TokenNumber.FAIL);
        peek = ' ';
        //delete current char on buffer, we done with it.
        b.deleteCharAt(0);
        return tok;
    }
}
