#ifndef OPERATOR_H
#define OPERATOR_H
#include <iostream>
#include "token.h"
#include <cstring>
#include  "integer.h"
using namespace std;

class Operator : public Token
{
public:
    Operator(const string& oper = "UNINIT OP"):Token(oper){//ctor gets precedence from oper var
        prec = get_prec(oper);
    }
    

    int get_prec(const string& op){//big switch statement to get the precedence of each operator
        char oper = op[0];
        switch(oper) {
                case '+': return 1;
                    break;
                case '-': return 1;
                    break;
                case '*': return 2;
                    break;
                case '/': return 2;
                    break;
                case '(' : return 0;
                    break;
                case ')' : return 20;
                    break;
                case '^': return 3;
                    break;
                case 'X' : return 0;
                    break;
                case 'S' : return 4;
                    break;
                case 'C' : return 4;
                    break;
                case 'T' : return 4;
                    break;
                default: cout << oper << " THIS SHOULDNT HAPPEN" << endl;//incase switch statment doesn't get activated

            }
       return 0;
    }
    double eval(Token* left, Token* right){//takes two tokens and does whatever the operator is on the two tokens then returns the result
        Integer* leftVal = static_cast<Integer*> (left);//cast tokens so can take values
        Integer* rightVal = static_cast<Integer*> (right);
        double leftNum = leftVal->getValue();//gets values for tokens
        double rightNum = rightVal->getValue();
        double result;
        string line = getToken();//gets the string
        char oper = line[0];//turns string into char
            switch(oper) {
                case '+': result = leftNum + rightNum;
                    break;
                case '-': result = leftNum - rightNum;
                    break;
                case '*': result = leftNum * rightNum;
                    break;
                case '/': result = leftNum / rightNum;
                    break;
                case '^': {
                    result = leftNum;
                    for (int i = 1; i < rightNum; i++){
                        result *= leftNum;
                    }
                    break;
                }
                default: cout << "THIS SHOULDNT HAPPEN";//incase switch doesn't work

            }
        return result;
    }
    int typeOf(){
        return 2;
    }

    int getPre(){//returns precedence
        return prec;
    }

    

private:
    int prec;
};

#endif