#include "rpn.h"

RPN::RPN(){
    _postfix = Queue<Token*>();
    _answer = vectorlong();
}

RPN::RPN(Queue<Token*> &postfix){
    _postfix = postfix;
    _answer = vectorlong();
}

void RPN::set_input(Queue<Token*> &postfix){
   _postfix = postfix; 
}

// Map<string, mmap_sl> RPN::eval(){
//     Stack<Token*> rpn;
//     Queue<Token*>::Iterator walker = _postfix.begin();
//     while(walker != _postfix.end()){
//         if((*walker)->get_type() == 8){
//             return _answer;
//         }
//          walker++;
//     }
//     Queue<Token*> copy = _postfix;
//     while(!(copy.empty())){
//         Token* tok = copy.pop();
//         if(tok->type() == 0){

//         }
//     }
//     return _answer;
// }

vectorlong RPN::eval(const vector<mmap_sl*>& double_dl, const map_sl& fieldmaps){
    Stack<Token*> rpn;
    Queue<Token*>::Iterator walker = _postfix.begin();
    Queue<Token*> copy = _postfix;
    while(!(copy.empty())){
        Token* tok = copy.pop();
        // cout << "rpn: " << __LINE__ << endl;
        rpn.push(tok);
       // cout << "rpn size: " << rpn.size() << endl;
        if(tok->get_type() == 3 || tok->get_type() == 4){
            Token* oper = rpn.pop();
            vectorlong right = rpn.pop()->get_recno();
            vectorlong left = rpn.pop()->get_recno();  
            rpn.push(new ResultSet(oper->eval(left, right)));
        }
        if(tok->get_type() == 5){
            //cout << "rpn: " << __LINE__ << endl;
            Token* oper = rpn.pop();
            Token* right = rpn.pop();
            Token* left = rpn.pop();
            vectorlong temp = oper->eval(double_dl, fieldmaps, left, right);
           // cout << "rpn: " << __LINE__ << endl;
            rpn.push(new ResultSet(temp));
            // cout << "temp: " << temp << endl;
        }
        
    }
    vectorlong rpnvector = rpn.pop()->get_recno();
    _answer = rpnvector;
    // cout << "_answer: " <<_answer << endl;
    return _answer;
}

