//
//  pa3.hpp
//  pa3
//
//  Created by Mark Lawrence on 11/9/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#ifndef pa3_hpp
#define pa3_hpp

#include <stdio.h>
#include <string>
#include "StackLinkedList.hpp"
using namespace std;


class Stack{
private:
    string stack;
public:
    Stack *next;
    Stack(){}
    Stack(string stack);
    void setStackName(string stack);
    string getStackName();
};


class StackLinkedList{
private:
    Stack *head;
    Stack *tail;
public:
    StackLinkedList(){
        head=NULL;
        tail=NULL;
    }
    void pop();
    void push(string stack);
    void print();
    bool isUniqueEntryToStack(string newEntry);
    int countNestedLoop();
    string checkForInvalidKeyword();
    string checkForMissingKeywords();
};

string line;
string inputFile;
string keyword;
string identifiers;
string constants;
string operators;
string delimiters;


StackLinkedList *keywordsStack = new StackLinkedList();
StackLinkedList *nestedLoops = new StackLinkedList();
StackLinkedList *identifiersStack = new StackLinkedList();
StackLinkedList *constantsStack = new StackLinkedList();
StackLinkedList *operatorsStack = new StackLinkedList();
StackLinkedList *delimitersStack = new StackLinkedList();

string forLoopErrors="";

char c;

string checkForKeywords(string line);
void printAnalysis (StackLinkedList *nestedLoops, StackLinkedList *keywordStack, StackLinkedList *identifiersStack, StackLinkedList *constantsStack, StackLinkedList *operatorsStack, StackLinkedList *delimitersStack, string forLoopErros);
string findSyntaxErrors(StackLinkedList *nestedLoops, string forLoopErrors);
string findForLoopErrors(string line);





#endif /* pa3_hpp */
