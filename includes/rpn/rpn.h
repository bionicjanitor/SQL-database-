#ifndef RPN_H
#define RPN_H
#include <iostream>
#include "../token/token_children.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

class RPN{
public:
RPN();
RPN(Queue<Token*> &postfix);


void set_input(Queue<Token *> &postfix);

//Map<string, mmap_sl> eval();
vectorlong eval(const vector<mmap_sl*>& double_dl, const map_sl& fieldmaps);

private:
Queue<Token*> _postfix;
vectorlong _answer;

};




#endif 