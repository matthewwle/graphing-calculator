#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include <iostream>
#include "token.h"
#include "operator.h"
using namespace std;


class LeftParen : public Operator
{
public: 
    LeftParen(): Operator("("){};//creates left paren operator with low prescedence


    int typeOf(){
        //cout << "LEFT PAREN FIRE" << endl;
        return 0;
    }

private:

}
;


#endif