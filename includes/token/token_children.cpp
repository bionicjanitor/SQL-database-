#include "token_children.h"

LParen::LParen():Token("("){
    _prec = LParenth;
}

//=============================
RParen::RParen():Token(")"){
    _prec = RParenth;
}

//=============================
TokenStr::TokenStr(string str):Token(str){
    _t = str;
    _prec = TokStr;
}

string TokenStr::get_str() const{
    return _t;
}

//=============================
Logical::Logical(string str):Token(str){
    if(str == "or"){
        _prec = LogicalOr;
    }else{
        _prec = LogicalAnd;
    }
    
}

vectorlong Logical::eval(vectorlong left, vectorlong right){
    vectorlong results;
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    if(get_type() == LogicalAnd){
        set_intersection(left.begin(), left.end(), right.begin(), right.end(), back_inserter(results));
    }else if(get_type() == LogicalOr){
        set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(results));
    }
    return results;
}



Precedence Logical::get_type() const{
    return _prec;
}

//=============================

// Operator::Operator(string str):Token(""){
//     if(str == "<"){
//         _operator = str;
//     }
//     if(str == ">"){
//         _operator = str;
//     }
//     if(str == "="){ 
//         _operator = str;
//     }
//     if(str == ">="){
//         _operator = str;
//     }
//     if(str == "<="){
//         _operator = str;
//     }
// }

// string Operator::get_str(){
//     return _operator;
// }

// Precedence Operator::get_type(){
//     return _prec;
// }
//=============================
ResultSet::ResultSet(vectorlong rec): Token(""){
    _recno = rec;
    // cout << "_recno: " << _recno << endl;
    _prec = Set;
}

//=============================
Relational::Relational(string str): Token(str){
    _operator = str;
    //_perc = Relation;
}

string Relational::token_str(){
    return _operator;
}

vectorlong Relational::eval(const vector<mmap_sl*>& indices, const map_sl& fieldmaps, Token* left, Token* right){
    if(!fieldmaps.contains(left->token_str())){
        cout << "field entered does not exist on the table" << endl;
        return vectorlong();
    }
    if(token_str() == "="){
        //cout << "token children:" << __LINE__ << endl;
        vectorlong values; // storing values in here
        //cout << "token children:" << __LINE__ << endl;
        //cout << "left->tok_str(): " << left->token_str() << endl;
        //cout << "right->tok_str(): " << right->token_str() << endl;
        values =  indices.at(fieldmaps.at(left->token_str()))->at(right->token_str()); //grabbing all the indices from here and putting them into temp
        //cout << "token children:" << __LINE__ << endl;
        return values;
    }
    if(token_str() == "<"){
        //cout << "token children:" << __LINE__ << endl;
        vectorlong values; // store values in here
        vectorlong grab; //grabbing all the value_lists from each linked node
        mmap_sl::Iterator it = indices.at(fieldmaps.at(left->token_str()))->begin();// make the iterator at the beginning of the linked list
        for(; it != indices.at(fieldmaps.at(left->token_str()))->lower_bound(right->token_str()); it++){
            grab = (*it).value_list; // we are just grabbing value lists here
            for(int i = 0; i < grab.size(); i++){
                values.push_back(grab[i]);
            }
        }
        return values;
    }
    if(token_str() == ">"){
        //cout << "token children:" << __LINE__ << endl;
        vectorlong values;
        vectorlong grab;
        mmap_sl::Iterator it = indices.at(fieldmaps.at(left->token_str()))->upper_bound(right->token_str()); //making the iterator set to the beginning of the right linked list
        for(; it != indices.at(fieldmaps.at(left->token_str()))->end(); it++){ //because we start at the lowerbound of the right token, we want to go all the way to the end of the left token
            grab = (*it).value_list; // we are just grabbing value lists here
            for(int i = 0; i < grab.size(); i++){
                values.push_back(grab[i]);
            }
        }
        return values;
    }
    if(token_str() == "<="){
        //cout << "token children:" << __LINE__ << endl;
        vectorlong values;
        vectorlong grab;
        mmap_sl::Iterator it = indices.at(fieldmaps.at(left->token_str()))->begin();
        for(; it != indices.at(fieldmaps.at(left->token_str()))->upper_bound(right->token_str()); it++){ //because we start at the lowerbound of the right token, we want to go all the way to the end of the left token
            grab = ((*it).value_list); // we are just grabbing value lists here
            for(int i = 0; i < grab.size(); i++){
                values.push_back(grab[i]);
            }   
        }
        //cout << "values: " << values << endl;
        return values;
    }
    if(token_str() == ">="){
        //cout << "token children:" << __LINE__ << endl;
        vectorlong values;
        vectorlong grab;
        mmap_sl::Iterator it = indices.at(fieldmaps.at(left->token_str()))->lower_bound(right->token_str());
        for(; it != indices.at(fieldmaps.at(left->token_str()))->end(); it++){
            grab = ((*it).value_list);
            for(int i = 0; i < grab.size(); i++){
                values.push_back(grab[i]);
            }   
        }
        //cout << "values: " << values << endl;
        return values;
    }

}

