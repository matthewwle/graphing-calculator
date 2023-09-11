#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include "token.h"
#include <cstring>
#include <assert.h>
using namespace std;

const int INTEGER = 1;
const int OPERATOR = 2;
const int FUNCTION = 3;
const int LEFTPAREN = 0;
const int RIGHTPAREN = 5;

class Token
{
public: 
    Token(): token("A"){};//default ctor
    Token(const string& s): token(s){}//ctor that takes string
    friend ostream& operator <<(ostream& outs, const Token& t) {//funcitons to print the Tokens
            outs << t.getToken() << " ";
            return outs;
        }
    friend ostream& operator <<(ostream& outs, const Token* t) {
            outs << t->getToken() << " ";
            return outs;
        }
    void Print(ostream& outs) const{//another way to print token
        outs << token;
    }
    virtual int typeOf(){//virutal function never used for Token types
        assert(false);
    }
    string getToken() const{//returns token
        return token;
    }

private:
    string token;
};

#endif