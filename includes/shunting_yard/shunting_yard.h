#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <assert.h>
#include <iostream>

#include "../token/token_children.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"


using namespace std;

class ShuntingYard{
public:
ShuntingYard();
ShuntingYard(Queue<Token*> infix);

Queue<Token*> postfix();
Queue<Token*> postfix(Queue<Token*> infix);
void infix(Queue<Token*> infix);

private:
Queue<Token*> _infix;
Queue<Token*> _postfix;
bool _traversal;
};

#endif
    