#include "shunting_yard.h"

ShuntingYard::ShuntingYard(){
_infix = Queue<Token*>();
_postfix =  Queue<Token*>();
_traversal = false;
}

ShuntingYard::ShuntingYard(Queue<Token*> infix){
    _infix = infix;
}


Queue<Token*> ShuntingYard::postfix(){
        _postfix = Queue<Token*>();
        Stack<Token*> stk;
        while(!(_infix.empty())){
            Token* tok = _infix.pop();
            // if(tok->get_type() == 0){
            //     cout << "pushing number" << endl;
            // _postfix.push(tok);
            // }
            if(tok->get_type() == 0 || tok->get_type() == 1){
                //cout << "pushing tokstr: " << tok->token_str() << endl;
                _postfix.push(tok);
            }
            if(tok->get_type() >= 3 && tok->get_type() <= 5){
            
                while(!stk.empty() && stk.top()->get_type() >= tok->get_type() && stk.top()->get_type() != 6){
                    _postfix.push(stk.pop());
                }
                //cout << "pushing in logical or relational: " <<  tok->token_str() << endl; 
                stk.push(tok);
            }
            if(tok->get_type() == 6){
                //cout << "pushing left paren" << endl;
                stk.push(tok); 
            }
            if(tok->get_type() == 7){
                //cout << "in right paren" << endl;
                while(stk.top()->get_type() != 6){
                    //cout << "pushing not left paren into postfix: " << stk.top()->token_str() << endl;
                    _postfix.push(stk.pop());
                }             
                if(stk.top()->get_type() == 6){
                    //cout << "popping left paren: " << tok->token_str() << endl;
                    stk.pop();
                }
            }
        }
        while(!(stk.empty())){
            _postfix.push(stk.pop());          
        }   
    
    return _postfix;
}


Queue<Token*> ShuntingYard::postfix(Queue<Token*> infix){
    _infix = infix;
    return postfix();
}

void ShuntingYard::infix(Queue<Token*> infix){
    _infix = infix;
}