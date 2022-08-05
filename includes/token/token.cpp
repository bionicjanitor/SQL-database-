#include "token.h"

Token::Token(){
    _token = "";
    _type = 0; 
}

Token::Token(string s){
    _token = s;
    _type = 0;
}

Token::Token(string str, int type){
    _token = str;
    _type = type;
}




int Token::type() const{
    return _type;
}

string Token::type_string() const{
    string empty = "";
    switch(_type){
        case 0:
        empty = "TOKSTR";
        break;
        case 1:
        empty = "SET";
        break;
        case 2:
        empty = "OPERATOR";
        break;
        case 3:
        empty = "LOGICALOR";
        break;
        case 4:
        empty = "LOGICALAND";
        break;
        case 5:
        empty = "RELATION";
        break;
        case 6:
        empty = "LPAREN";
        case 7:
        empty = "RPAREN";
        default:
        empty = "UNKNOWN";
    }
    return empty;

}

string Token::token_str() const{
    return _token;
}