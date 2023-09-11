#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/function.h"
#include "../token/operator.h"
#include <cmath>
using namespace std;


class ShuntingYard
{
public: 
    ShuntingYard(){}//blank default ctor
    ShuntingYard(Queue<Token*> tokens): infixTokens(tokens){//sets tokens to the tokenptr infixTokens
        
    }
    void infix(Queue<Token*> _infix){//allows users to set new tokens
        infixTokens = _infix;
    }

    Queue<Token*> postfix(Queue<Token*> origList){//actual shuntingyard algorithm
    Stack<Token*> resultStack;//declaring all variables needed
    Queue<Token*> resultQueue;
        typename Queue<Token*> :: Iterator start(origList.begin());
        typename Queue<Token*> :: Iterator end(origList.end());
        int num;
        Token* hold;
        Token* left;
        Token* right;
        Token* res;
        Token* resultStackHold;
        double resultNum;
        int numOfArgs;
        Operator* OpVal; 
        Operator* HoldOpVal;
        Function* FuncVal;
        
        for (; start!= end; start++){//iterates from start to end 
            hold = *start;//hold gets the acutal token
            num = hold->typeOf();//gets the type of token
            switch (num){
                case INTEGER: resultQueue.push(hold);//if its an integer just push to result queue
                    break;
                case OPERATOR:
                        if (resultStack.empty()){//if operator and stack is empty just push to result stack
                            resultStack.push(hold);
                        }
                        else {//if not empty check for precedence and push to stack if precedence is higher than the top, otherwise
                            resultStackHold = resultStack.top();//pop until the stack is empty or precedence is higher than top
                            HoldOpVal = static_cast<Operator*> (resultStackHold);
                            OpVal = static_cast<Operator*> (hold);
                            num = OpVal->getPre();
                        if (HoldOpVal->getPre() < num || resultStack.empty()){
                            resultStack.push(hold);
                        }
                        else{
                            while(HoldOpVal->getPre() >= num){
                                resultQueue.push(resultStack.pop());
                                if(resultStack.empty())
                                    break;
                                resultStackHold = resultStack.top();
                                HoldOpVal = static_cast<Operator*> (resultStackHold);
                            }
                            resultStack.push(hold);
                        }
                        }
                            
                    break;
                case LEFTPAREN: resultStack.push(hold);//push left parenthesis into stack 
                    break;
                case RIGHTPAREN:
                                resultStackHold = resultStack.top();//keep on popping stack until you see left parenthesis on top then pop that
                                while(resultStackHold->typeOf() != LEFTPAREN){//and throw away right parenthesis
                                    resultQueue.push(resultStack.pop());
                                    resultStackHold = resultStack.top();
                                }
                                resultStack.pop();
                                break;
                case FUNCTION: 
                    FuncVal = static_cast<Function*> (hold);
                    if (FuncVal->getFunc() == "X")//if X then push the X to queue
                        resultQueue.push(hold);
                    else{
                        resultStack.push(hold);//if not X then push to stack
                    }
                        
                    break;
            }
        }
        while (!(resultStack.empty())){//pop stack until empty
            resultQueue.push(resultStack.pop());
        }
        return resultQueue;

    }
    Queue<Token*> postfix(){
        return postfix(infixTokens);
    }

private: 
Queue<Token*> infixTokens;
}
;

#endif