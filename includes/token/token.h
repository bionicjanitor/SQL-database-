#ifndef TOKEN_H
#define TOKEN_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../queue/MyQueue.h"
#include "../table/typedefs.h"

using namespace std;

enum Precedence { Unknown =-1,TokStr, Set,  Operator, LogicalOr, LogicalAnd, Relation, LParenth, RParenth};

class Token
{
public:
    Token();
    Token(string s);
    Token(string str, int type);

    virtual vector<long> get_recno(){

    }

    virtual Precedence get_type() const{

    }

   
    virtual vectorlong eval(const vector< mmap_sl*>& indices, const map_sl& fieldmaps, Token* left, Token* right){

    }

    virtual vectorlong eval(vectorlong left, vectorlong right){

    }

    friend ostream& operator <<(ostream& outs, const Token& t){
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