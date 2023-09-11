#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include <iostream>
#include "token.h"
#include "operator.h"
using namespace std;

class RightParen : public Operator
{
public: 
    RightParen(): Operator(")"){};//makes right parenthesis operator

int typeOf(){//returns an identifiable number
    return 5;
}

private:
};


#endif