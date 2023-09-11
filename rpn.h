#ifndef RPN_H
#define RPN_H
#include <iostream>
using namespace std;
#include "../queue/MyQueue.h"
#include <cmath>
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/function.h"
#include "../token/operator.h"

class RPN
{
public: 
    RPN(Queue<Token*> _tokens): tokenList(_tokens){}//get tokenlist to evaluate

    Token* postfix(double xval = 0){//value of x default to 0
        Stack<Token*> resultStack;//declare variables needed
        typename Queue<Token*> :: Iterator start(tokenList.begin());
        typename Queue<Token*> :: Iterator end(tokenList.end());
        Token* hold;
        Integer x(xval);
        Token* xPoint = &x;
        int num;
        Token* left;
        Token* right;
        Token* res;
        Function* FuncVal;
        Operator* OpVal;
        double resultNum;
        int numOfArgs;
        for (; start!= end; start++){//iterate from beginning to end of queue
            hold = *start;
            num = hold->typeOf();//get type of token
            switch (num){
                case INTEGER: {resultStack.push(hold);}//if int just push to resultStack
                    break;
                case OPERATOR: {OpVal = static_cast<Operator*> (hold);//if operator then pop 2 and evaluate using the operator
                        right = resultStack.pop();
                        left = resultStack.pop();
                        resultNum = OpVal->eval(left, right);
                        resultStack.push(new Integer(resultNum));}//push result back into stack
                    break;
                case FUNCTION: {FuncVal = static_cast<Function*> (hold);//cast to function
                    numOfArgs = FuncVal->getArgs();
                    if (FuncVal->getFunc() == "X")//if X then push the value of x into the stack
                        resultStack.push(xPoint);
                    else{
                        resultNum = FuncVal->eval(resultStack.pop());//if not pop and evauate then push result into stack
                        resultStack.push(new Integer(resultNum));
                    }
            }
            }

        }
        res = resultStack.pop();//at the end there's only one number so pop stack
        return res;
    }
    double operator ()(double xval = 0)//allows users to call with () operator
    {
        Token* res = postfix(xval);
        string a = res->getToken();
        return stod(a);
    }
    void set_input(Queue<Token*> _tokens){
        tokenList = _tokens;
    }


private:

Queue<Token*> tokenList;

}
;

#endif