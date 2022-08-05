#ifndef TOKEN_CHILDREN_H
#define TOKEN_CHILDREN_H

#include "token.h"


class LParen:public Token{
    public:
    LParen();
    //void display() const;
    Precedence get_type() const{
        return LParenth;
    }
    private:
    //string _t;
    Precedence _prec;
};


class RParen:public Token{
    public:
    RParen();
    //void display() const;
    Precedence get_type() const{
        return RParenth;
    }
    private:
    //string _t;
    Precedence _prec;
};

class TokenStr:public Token
{
    public:
    TokenStr(string str);
    string get_str() const;
    Precedence get_type() const{
        return TokStr;
    }
    private:
    string _t;
    Precedence _prec;
};

class Logical: public Token {
    public:
    Logical(string str);
    
    Precedence get_type() const;
    vectorlong eval(vectorlong left, vectorlong right);

    private:
    //
    Precedence _prec;
};

class Operator: public Token{ // < = > >= <=
    Operator(string str);
    string get_str();
    Precedence get_type() const;
    private:
    string _operator;
    Precedence _prec;
};

class ResultSet: public Token{
    public:
    ResultSet(vectorlong rec);
    Precedence get_type() const{
        return Set;
    }

    vectorlong get_recno(){
        return _recno;
    }
    private:
    vectorlong _recno;
    Precedence _prec;
};

class Relational: public Token{
    public:
    Relational(string str);

    Precedence get_type() const{
        return Relation;
    }

    string token_str();
    vectorlong get_recno(){
        return _rec;
    }
    vectorlong eval(const vector<mmap_sl*>& indices, const map_sl& fieldmaps, Token* left, Token* right);
    private:
    string _operator;
    Precedence _prec;
    vectorlong _rec;

};

#endif