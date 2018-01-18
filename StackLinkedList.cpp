//
//  StackLinkedList.cpp
//  Project_3
//
//  Created by Mark Lawrence on 11/11/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#include "StackLinkedList.hpp"
#include <iostream>
#include <string>
#include <iostream>
using namespace std;

//void StackLinkedList::push(string nestedStak){
//    //Add a new element to the stack
//    Stack *current=new Stack;
//    current->setStackName(nestedStak);
//    
//    current->next=NULL;
//    if(head==NULL)
//    {
//        head=current;
//        tail=current;
//        current=NULL;
//    }
//    else
//    {
//        tail->next=current;
//        tail=current;
//    }
//}
//
//void StackLinkedList::pop(){
//    //Remove an element from the stack
//    Stack *current=new Stack;
//    Stack *preivious = new Stack;
//    current=head;
//    
//    while (current && current->next != NULL){
//        preivious = current;
//        current= current->next;
//    }
//    
//    preivious->next = current->next;
//    current = NULL;
//    tail = preivious;
//}
//
//void StackLinkedList::print(){
//    Stack *current=new Stack;
//    current=head;
//    //Print until reach the end of the linked list
//    while(current!=NULL){
//        cout<<current->getStackName()<<"\t";
//        current=current->next;
//    }
//}
//
//bool StackLinkedList::isUniqueEntryToStack(string newEntry){
//    bool isUnique = true;
//    Stack *current=new Stack;
//    current=head;
//    
//    //Iterates through the linked list, sees if the new entry has been already entered
//    while(current!=NULL){
//        if (current->getStackName()==newEntry){
//            //If it is not a new entry, return false
//            isUnique=false;
//        }
//        current=current->next;
//    }
//    return isUnique;
//}
//
//int StackLinkedList::countNestedLoop(){
//    int numberOfNestedLoops=0;
//    int couldBeBiggestLoop =0;
//    Stack *current=new Stack;
//    current=head;
//    
//    //If a single for loop is never properly declared, return 0
//    if (current==NULL || current->next==NULL || current->next->next==NULL){
//        return 0;
//    }
//    
//    while(current!=NULL){
//        
//        //If the current element in the stack is a FOR and the next one is BEGIN and the one after that is not END, increment the counter since there is another layer to the nested loop
//        if (current->getStackName()=="FOR" && current->next->getStackName()=="BEGIN"&&current->next->next->getStackName()!="END"){
//            numberOfNestedLoops++;
//        }
//        //Once you current->next->next is a END, the nested loop has ended, so check to see if it is the longest nested loop so far
//        if (current!=NULL && current->next!=NULL && current->next->next!=NULL && current->next->next->getStackName()=="END"){
//            if (couldBeBiggestLoop<numberOfNestedLoops){
//                couldBeBiggestLoop = numberOfNestedLoops;
//            }
//            numberOfNestedLoops=numberOfNestedLoops-1;
//        }
//        
//        current=current->next;
//    }
//    if (couldBeBiggestLoop == 0){
//        return 0;
//    }
//    current=head;
//    //Go through the KEYWORDS, and if one has been misspelt, that does not count as a nested loop anymore, so subtract one form couldBeBiggestLoop
//    while (current!=NULL) {
//        if (current->getStackName()!="FOR" && current->getStackName()!="BEGIN" && current->getStackName()!="END"){
//            couldBeBiggestLoop= couldBeBiggestLoop-1;
//        }
//        current = current->next;
//    }
//    if (couldBeBiggestLoop<0){
//        return 0;
//    }
//    return couldBeBiggestLoop;
//}
//
//string StackLinkedList::checkForInvalidKeyword(){
//    string invalidKeywords;
//    Stack *current=new Stack;
//    current=head;
//    
//    while(current!=NULL){
//        //If a keyword (a string of characters in caps) is not one of the three legal keywords, add it to invalidKeywords
//        if (current->getStackName()!="FOR" && current->getStackName()!="END" && current->getStackName()!="BEGIN"){
//            invalidKeywords += current->getStackName();
//            invalidKeywords += " ";
//        }
//        current=current->next;
//    }
//    return invalidKeywords;
//}
//
//string StackLinkedList::checkForMissingKeywords(){
//    string missingKeywords;
//    int numberOfFor=0;
//    int numberOfBegin=0;
//    int numberOfEnd=0;
//    Stack *current=new Stack;
//    current=head;
//    
//    //Calculate how many times each keyword is used
//    while(current!=NULL){
//        if (current->getStackName()=="FOR"){
//            numberOfFor++;
//        }
//        if (current->getStackName()=="BEGIN"){
//            numberOfBegin++;
//        }
//        if (current->getStackName()=="END"){
//            numberOfEnd++;
//        }
//        current=current->next;
//    }
//    
//    //Add a missing error message is the number of ENDs is not the same as the number of FORs
//    if (numberOfEnd!=numberOfFor){
//        for (int i = numberOfEnd; i<numberOfFor; i++) {
//            missingKeywords += "END";
//        }
//    }
//    //Add error message is the the number of BEGINs is equal to the number of ENDs and not equal to the number of FORs
//    if (numberOfBegin!=numberOfFor && numberOfBegin == numberOfEnd){
//        for (int i = numberOfBegin; i<numberOfFor; i++) {
//            missingKeywords += "BEGIN";
//        }
//    }
//    return missingKeywords;
//}
//
//
//Stack::Stack(string stack){
//    this->stack = stack;
//}
//
//string Stack::getStackName(){
//    return stack;
//}
//
//void Stack::setStackName(string stack){
//    this->stack = stack;
//}

