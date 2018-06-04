/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTable.h
 * Author: B
 *
 * Created on February 6, 2018, 11:03 PM
 */
#include <iostream>
#include "Event.h"
using namespace std;

const int SIZE = 100;

#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable{
    
private:
    Event container[SIZE][SIZE];
    
public:
    HashTable();
    ~HashTable();
    int EventKeyFunc(string title); //reinitializes key for the limited size of the list
    void input(string title, int day, MONTH month, int year, int hour, int minutes, string descrip);
    void removeEvent(string title);
    Event searchEvent(string title);
};

#endif /* HASHTABLE_H */

