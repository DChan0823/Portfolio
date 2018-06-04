/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HashTable.h"

HashTable::HashTable(){
    Event event;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
        container[i][j] = event;
        }
    }
}

HashTable::~HashTable(){
}

int HashTable::EventKeyFunc(string title){
    
    return 1;
}

void HashTable::input(string title, int day, MONTH month, int year, int hour, int minutes, string descript){
    int key = EventKeyFunc(title);
    Event e;
    Event eve(title, day, month, year, hour, minutes, descript);
    int count = 0;
    if(container[key][0].notSimilar(e) == false)
        container[key][0].insert(eve);
    else{
        do{
            count++;
        }while(container[key][count].notSimilar(e) == true);
        container[key][count].insert(eve);
    }
}

void HashTable::removeEvent(string title){
    int key = EventKeyFunc(title);
    int count = 0;
    Event e;
    //if event doesn't exist, return
    if(searchEvent(title).notSimilar(e) == false)
        return;
    
    //if in first element of array, shift all elements forward
    if(container[key][0].getTitle() == title){
        while(container[key][count].notSimilar(e) == true){
            container[key][count] = container[key][count+1];
            count++;
        }
    }
    else{
        //finds the desired event, searching by title
        while(container[key][count].getTitle() != title){
            count++;
        }
        if(container[key][count].getTitle() == title){
            //if last element in array, make last element NULL
            if(container[key][count+1].notSimilar(e) == false)
                container[key][count].insert(e);
            else{
                //if in the middle, 
                while(container[key][count].notSimilar(e) == true){
                    container[key][count].insert(container[key][count+1]);
                    count++;
                }
            }
        }
    } 
}

Event HashTable::searchEvent(string title){
    int key = EventKeyFunc(title);
    int count = 1;
    Event e;
    int found = 1;
    
    if(container[key][0].getTitle() == title)
        return container[key][0];
    else{
        do{
            if(container[key][count].getTitle() == title)
                found = 0;
            else
                count++;
        }while(container[key][count].notSimilar(e) == true && found == 1);
    }
    if(found == 0)
        return container[key][count];
    else
        return e;
}