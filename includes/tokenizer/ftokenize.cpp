#include "ftokenize.h"

bool FTokenizer::get_new_block(){  
    if(!_f.eof()){    
        char container[MAX_BUFFER] = "";
        for(int i = 0; i < MAX_BUFFER; i++){
            container[i] = 0;
        }     
        _f.read(container, MAX_BUFFER-1);
        _stk.set_string(container);
        return true;
    }
    _more = false;
    return false; 
}

FTokenizer::FTokenizer(char* fname){
    _f.open(fname);
    if(_f.fail()){
        cout << "error opening file" << endl;
        exit(1);
    }
    _pos = 0; 
    _blockPos = 0;
    _more = true;
    _stk = STokenizer();
    get_new_block();
}

PToken FTokenizer::next_token(){
   PToken next = PToken();
   if(_stk.done()){
       get_new_block();
   }
   _stk >> next;
   return next;
}

bool FTokenizer::more(){
    return _more;
}

int FTokenizer::pos(){
    return _pos;
}

int FTokenizer::block_pos(){
    return _blockPos;
}

FTokenizer& operator >> (FTokenizer& f, PToken& t){
    t = f.next_token();
    return f;
}
