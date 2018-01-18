//
//  pa3.cpp
//  pa3
//
//  Created by Mark Lawrence on 11/9/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//


#include <iostream>
#include <string>
#include <fstream>
#include "pa3.hpp"
#include "StackLinkedList.hpp"
using namespace std;




int main(int argc, const char * argv[]) {
   
    
    cout<<"Please enter the name of the input file: ";
    cin>>inputFile;
    cout<<"\n";
    ifstream textFile(inputFile);
   
    //If the file name can not be found, quit the program
    if (!textFile) {
        cout << "error: Cannot find input file named "<<inputFile<<"\n";
        return 1;
    }
    
    //Loop through each line in the text file
    while (getline(textFile, line)){
        for (int i =0; i<line.length(); i++) {
            c=line[i];
            
            //Check for keywords (a keyword is in all capslock)
            if (isupper(c)==1){
                keyword += c;
                //Keep adding characters to the keyword until the next character is not uppercased
                if (isupper(line[i+1])!= 1){
                    nestedLoops->push(keyword);
                    //Check to make sure the new keyword will be the first time it is used
                    if (keywordsStack->isUniqueEntryToStack(keyword)){
                        //If it is the first time the keyword has been used and is one of the three legal keywords, add it to the stack
                        if (keyword=="FOR" || keyword=="BEGIN" || keyword=="END"){
                            keywordsStack->push(keyword);
                        }
                    }
                    keyword="";
                }
            }
            
            //Check for identifiers (identifiers are lowercase)
            if (islower(c)==1){
                identifiers += c;
                //Keep adding characters to the identifier until the next character is not lowercase anymore
                if (islower(line[i+1])!= 1){
                    if (identifiersStack->isUniqueEntryToStack(identifiers)){
                        identifiersStack->push(identifiers);
                    }
                    identifiers="";
                }
            }
            
            //Check for constants (digits)
            if (isdigit(c)){
                constants += c;
                if (isdigit(line[i+1])!= 1){
                    if (constantsStack->isUniqueEntryToStack(constants)){
                        constantsStack->push(constants);
                    }
                    constants="";
                }
            }
            
            //Chekcs for all the operands excpet for + and ++
            if (c =='-' || c =='*' || c =='/' || c =='='){
                operators += c;
                if (operatorsStack->isUniqueEntryToStack(operators)){
                    operatorsStack->push(operators);
                }
                 operators="";
            }
            //Checks for the + and ++ operands
            if (c=='+'){
                //If the next charcter is also a +, add ++ to the stack
                if (line[i+1]=='+'){
                    if (operatorsStack->isUniqueEntryToStack("++")){
                        operatorsStack->push("++");
                        //Since you know that the character is a ++, iterate a second time to the next character
                        i++;
                    }
                }
                else{
                    if (operatorsStack->isUniqueEntryToStack("+"))
                    operatorsStack->push("+");
                }
            }
            
            //Check for the two delimiters
            if (c==',' || c==';'){
                delimiters = c;
                if (delimitersStack->isUniqueEntryToStack(delimiters)){
                    delimitersStack->push(delimiters);
                }
                delimiters="";
            }
        }
        forLoopErrors += findForLoopErrors(line);
    }
    
    printAnalysis(nestedLoops, keywordsStack, identifiersStack, constantsStack, operatorsStack, delimitersStack,forLoopErrors);
    return 0;
}

void printAnalysis (StackLinkedList *nestedLoops, StackLinkedList *keywordStack, StackLinkedList *identifiersStack, StackLinkedList *constantsStack, StackLinkedList *operatorsStack, StackLinkedList *delimitersStack, string forLoopErros){
    
    cout<<"The depth of the nested loop(s) is "<<nestedLoops->countNestedLoop()<<"\nKeywords: ";
    keywordStack->print();
    cout<<"\nIdentifier: ";
    identifiersStack->print();
    cout<<"\nConstant: ";
    constantsStack->print();
    cout<<"\nOperators: ";
    operatorsStack->print();
    cout<<"\nDelimiter: ";
    delimitersStack->print();
    cout<<"\n\nSyntax Error(s): "<<findSyntaxErrors(nestedLoops, forLoopErros);
    cout<<"\n";
    
}

string findSyntaxErrors(StackLinkedList *nestedLoops, string forLoopErrors){
    string syntaxErrors="";
    //Call the various syntax error methods, add their results to syntaxErrors
    syntaxErrors += nestedLoops->checkForInvalidKeyword();
    syntaxErrors += nestedLoops->checkForMissingKeywords();
    syntaxErrors += forLoopErrors;
    if (syntaxErrors==""){
        syntaxErrors="NA";
    }
    return syntaxErrors;
}

string findForLoopErrors(string line){
    string loopDeclaration;
    string forLoopError;
    char c;
    bool startOfLoopDeclaration = false;
    int numberOfOpenParenthesis = 0;
    int numberOfCloseParenthesis = 0;
    
    //Find illeagal declaration in the for loop
    for (int i =0; i<line.length(); i++) {
        c=line[i];
        
        if (c=='F' || startOfLoopDeclaration){
            startOfLoopDeclaration = true;
            //If a user uses a ';' in a for loop declaration instead of a ',', create an error message
            if (c==';'){
                forLoopError += "; ";
            }
            loopDeclaration += c;
        }
    }
    
    //Check for an equal number of open and close parenthesis in a for loop declaration
    for (int i =0; i<loopDeclaration.length(); i++) {
        if (loopDeclaration[i]=='('){
            numberOfOpenParenthesis++;
        }
        if (loopDeclaration[i]==')'){
            numberOfCloseParenthesis++;
        }
    }
    
    if (numberOfOpenParenthesis != numberOfCloseParenthesis){
        if (numberOfCloseParenthesis > numberOfOpenParenthesis){
            forLoopError+=") ";
        }
        if (numberOfOpenParenthesis > numberOfCloseParenthesis){
            forLoopError+="( ";
        }
    }
    
    
    
    return forLoopError;
}

void StackLinkedList::push(string nestedStak){
    //Add a new element to the stack
    Stack *current=new Stack;
    current->setStackName(nestedStak);
    
    current->next=NULL;
    if(head==NULL)
    {
        head=current;
        tail=current;
        current=NULL;
    }
    else
    {
        tail->next=current;
        tail=current;
    }
}

void StackLinkedList::pop(){
    //Remove an element from the stack
    Stack *current=new Stack;
    Stack *preivious = new Stack;
    current=head;
    
    while (current && current->next != NULL){
        preivious = current;
        current= current->next;
    }
    
    preivious->next = current->next;
    current = NULL;
    tail = preivious;
}

void StackLinkedList::print(){
    Stack *current=new Stack;
    current=head;
    //Print until reach the end of the linked list
    while(current!=NULL){
        cout<<current->getStackName()<<"\t";
        current=current->next;
    }
}

bool StackLinkedList::isUniqueEntryToStack(string newEntry){
    bool isUnique = true;
    Stack *current=new Stack;
    current=head;
    
    //Iterates through the linked list, sees if the new entry has been already entered
    while(current!=NULL){
        if (current->getStackName()==newEntry){
            //If it is not a new entry, return false
            isUnique=false;
        }
        current=current->next;
    }
    return isUnique;
}

int StackLinkedList::countNestedLoop(){
    int numberOfNestedLoops=0;
    int couldBeBiggestLoop =0;
    Stack *current=new Stack;
    current=head;
    
    //If a single for loop is never properly declared, return 0
    if (current==NULL || current->next==NULL || current->next->next==NULL){
        return 0;
    }
    
    while(current!=NULL){
        
        //If the current element in the stack is a FOR and the next one is BEGIN and the one after that is not END, increment the counter since there is another layer to the nested loop
        if (current->getStackName()=="FOR" && current->next->getStackName()=="BEGIN"&&current->next->next->getStackName()!="END"){
            numberOfNestedLoops++;
        }
        //Once you current->next->next is a END, the nested loop has ended, so check to see if it is the longest nested loop so far
        if (current!=NULL && current->next!=NULL && current->next->next!=NULL && current->next->next->getStackName()=="END"){
            if (couldBeBiggestLoop<numberOfNestedLoops){
                couldBeBiggestLoop = numberOfNestedLoops;
            }
            numberOfNestedLoops=numberOfNestedLoops-1;
        }
        
        current=current->next;
    }
    if (couldBeBiggestLoop == 0){
        return 0;
    }
    current=head;
    //Go through the KEYWORDS, and if one has been misspelt, that does not count as a nested loop anymore, so subtract one form couldBeBiggestLoop
    while (current!=NULL) {
        if (current->getStackName()!="FOR" && current->getStackName()!="BEGIN" && current->getStackName()!="END"){
            couldBeBiggestLoop= couldBeBiggestLoop-1;
        }
        current = current->next;
    }
    if (couldBeBiggestLoop<0){
        return 0;
    }
    return couldBeBiggestLoop;
}

string StackLinkedList::checkForInvalidKeyword(){
    string invalidKeywords;
    Stack *current=new Stack;
    current=head;
    
    while(current!=NULL){
        //If a keyword (a string of characters in caps) is not one of the three legal keywords, add it to invalidKeywords
        if (current->getStackName()!="FOR" && current->getStackName()!="END" && current->getStackName()!="BEGIN"){
            invalidKeywords += current->getStackName();
            invalidKeywords += " ";
        }
        current=current->next;
    }
    return invalidKeywords;
}

string StackLinkedList::checkForMissingKeywords(){
    string missingKeywords;
    int numberOfFor=0;
    int numberOfBegin=0;
    int numberOfEnd=0;
    Stack *current=new Stack;
    current=head;
    
    //Calculate how many times each keyword is used
    while(current!=NULL){
        if (current->getStackName()=="FOR"){
            numberOfFor++;
        }
        if (current->getStackName()=="BEGIN"){
            numberOfBegin++;
        }
        if (current->getStackName()=="END"){
            numberOfEnd++;
        }
        current=current->next;
    }
    
    //Add a missing error message is the number of ENDs is not the same as the number of FORs
    if (numberOfEnd!=numberOfFor){
        for (int i = numberOfEnd; i<numberOfFor; i++) {
            missingKeywords += "END";
        }
    }
    //Add error message is the the number of BEGINs is equal to the number of ENDs and not equal to the number of FORs
    if (numberOfBegin!=numberOfFor && numberOfBegin == numberOfEnd){
        for (int i = numberOfBegin; i<numberOfFor; i++) {
            missingKeywords += "BEGIN";
        }
    }
    return missingKeywords;
}


Stack::Stack(string stack){
    this->stack = stack;
}

string Stack::getStackName(){
    return stack;
}

void Stack::setStackName(string stack){
    this->stack = stack;
}


