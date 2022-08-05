#ifndef PTOKEN_H
#define PTOKEN_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "constants.h"

using namespace std;



class PToken
{
public:
    PToken();
    PToken(string str, int type);
    friend ostream& operator <<(ostream& outs, const PToken& t){
        outs << "|" << t._token << "|";
        return outs;
    }
    int type() const;
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type;
};

#endif