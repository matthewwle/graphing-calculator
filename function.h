#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <cstring>
#include <string>
#include "operator.h"
#include <cmath>
using namespace std;

class Function : public Operator
{
public: 

Function(string a = " ", int num = 1): Operator(a), func(a), numArgs(num){};//ctor for function with default vars

int getArgs(){
    return numArgs;
}
int typeOf(){//virtual function to get type
    return 3;
}

double eval(Token* num){
    Integer* numval = static_cast<Integer*> (num);//evaluates the token depending on what trig function it is
    double valnum = numval->getValue();
    int val = typeTrig();
    double result;
    switch(val){
        case 1: result = sin(valnum);
            break;
        case 2: result = cos(valnum);
            break;
        case 3: result = tan(valnum);
            break;
        default:
            break;
    }
    return result;
}

int typeTrig(){//gets the 3 letters and returns 1 2 or 3 depending on if sin cos or tan
    char first = func[0];
    char second =  func[1];
    char third = func[2];
    if(first == 'S' && second == 'I' && third == 'N'){
        return 1;
    }
    else if(first == 'C' && second == 'O' && third == 'S'){
        return 2;
    }
    else
    return 3;
}

string getFunc(){//returns the string func
    return func;
}



private: 
string func;
int numArgs;
}
;

#endif