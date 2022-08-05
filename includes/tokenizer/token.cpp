#include "token.h"

PToken::PToken(){
    _token = "";
    _type = 0; 
}

PToken::PToken(string str, int type){
    _token = str;
    _type = type;
}


int PToken::type() const{
    return _type;
}

string PToken::type_string() const{
    string empty = "";
    switch(_type){
        case TOKEN_NUMBER:
        empty = "NUMBER";
        break;
        case TOKEN_ALPHA:
        empty = "ALPHA";
        break;
        case TOKEN_SPACE:
        empty = "SPACE";
        break;
        case TOKEN_OPERATOR:
        empty = "OPERATOR";
        break;
        case TOKEN_PUNC:
        empty = "PUNC";
        break;
        case TOKEN_QUOT:
        empty = "QUOT";
        break;
        default:
        empty = "UNKNOWN";
    }
    return empty;

}

string PToken::token_str() const{
    return _token;
}