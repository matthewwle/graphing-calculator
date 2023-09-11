#ifndef INTEGER_H
#define INTEGER_H
#include <iostream>
#include <stdlib.h>
#include "token.h"
using namespace std;

class Integer : public Token
{
public:
//Int types are 1, these are enums
    Integer(double i=0) : Token(to_string(i)), val(i){};//integer with double ctor
    Integer(const string&n = "0.0"): Token(n), val(stoi(n)){}//integer with string ctor

    double getValue(){//returns the number
        return val;
    }

    int typeOf(){//virtual function to determine type
        return 1;
    }
private:
    double val;
}
;


#endif