#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    init_table(_table); // creating the tabel in general
    //creating our rules here
       //doubles:
    mark_fail(_table, 0);            //Mark states 0 and 2 as fail states
    mark_success(_table, 1);         //Mark states 1 and 3 as success states
    mark_fail(_table, 2);
    mark_success(_table, 3);

   // mark_cell(0, _table, 97, 10);

    mark_cells(0, _table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
    mark_cells(0, _table, '.', '.', 2);  //state [0] --- '.' ------> [2] 
    mark_cells(1, _table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]
    mark_cells(1, _table, '.', '.', 2);  //state [1] --- '.' ------> [2] 
    mark_cells(2, _table, DIGITS, 3);    //state [2] --- DIGITS ---> [3]
    mark_cells(3, _table, DIGITS, 3);    //state [3] --- DIGITS ---> [3]

    //alfa
    mark_fail(_table, 6);            //Mark states 0 and 2 as fail states
    mark_success(_table, 7);         //Mark states 1 and 3 as success states

    mark_cells(6, _table, ALFA, 7);    //state [0] --- DIGITS ---> [1]
    mark_cells(7, _table, ALFA, 7);    //state [1] --- DIGITS ---> [1]
    
    //spaces
    mark_fail(_table, 4);            
    mark_success(_table, 5);         

    mark_cells(4, _table, SPACES, 5);    
    mark_cells(5, _table, SPACES, 5);   

    //puncs
    mark_fail(_table, 10);            
    mark_success(_table, 11);         

    mark_cells(10, _table, PUNC, 11);    
    mark_cells(11, _table, PUNC, 11);   
    
    //operator
    mark_fail(_table, 20);            
    mark_success(_table, 21);         

    mark_cells(20, _table, OPERATORS, 21);    
    mark_cells(21, _table, OPERATORS, 21);   

    // quotation
    mark_success(_table, 27);

    mark_fail(_table, 26); 
    // mark_fail(_table, 27);

    mark_cell(25, _table, '\"', 26);

    mark_cells(26, _table, DIGITS, 26);
    mark_cells(26, _table, ALFA, 26);
    mark_cells(26, _table, SPACES, 26);
    mark_cells(26, _table, PUNC, 26);
    mark_cells(26, _table, OPERATORS, 26);
    mark_cells(26, _table, QUOT, 27);


    // mark_cells(27, _table, DIGITS, 27);
    // mark_cells(27, _table, ALFA, 27);
    // mark_cells(27, _table, SPACES, 27);
    // mark_cells(27, _table, PUNC, 27);
    // mark_cells(27, _table, OPERATORS, 27);

    
}

bool STokenizer::get_token(int start_state, string& token){
    const bool debug = true;
    token = "";
    int new_state = start_state;
    int success_state = _pos;
   
    for(int i = _pos; i < strlen(_buffer); i++){ //if pos =1 
        if(_buffer[i] < 0){
            new_state = _table[new_state][MAX_COLUMNS + _buffer[i]];
        }else{

        new_state = _table[new_state][_buffer[i]]; // make the new state 
        }
        //check to see if its a success state
        if(new_state == -1){
            // cout << "fail" << endl;
            break;
        }       
        if(is_success(_table, new_state)){
            //cout << new_state << endl;
            success_state = i;
        }
        //success state
         // add to the token from the buffer
        
        //cout << _pos << endl;
    }
    for(int i = _pos; i <= success_state; i++){
        if(_buffer[i] != '\"'){
            token+= _buffer[i];
        }
    }
    _pos = success_state + 1;
    //cout << _pos << endl;
    //rules: 1 a followed by a B, then followed by 2 a's
    //string: ab
    

    return false;
}
              

STokenizer::STokenizer(){
    _pos = 0;
    for(int i = 0; i < MAX_BUFFER; i++){
        _buffer[i] = 0;
    }
    make_table(_table);
}

STokenizer::STokenizer(char str[]){
     for(int i = 0; i < MAX_BUFFER; i++){
        _buffer[i] = '\0';
    }
    for(int i = 0; i< strlen(str); i++){
        _buffer[i] = str[i];
    }

    _pos = 0;
    make_table(_table);
}   

bool STokenizer::done(){
    if(_pos == strlen(_buffer)){
        return true;
    }
    return false;
}

bool STokenizer::more(){
    if(_pos <= strlen(_buffer)){
        return true;
    }
    return false;
}

void STokenizer::set_string(char str[]){
    for(int i = 0; i < MAX_BUFFER; i++){
        _buffer[i] = 0;
    }
    for(int i = 0; i < strlen(str); i++){
        _buffer[i] = str[i];
    }
    _pos = 0;
}

STokenizer& operator >> (STokenizer& s, PToken& t){
    char a = s._buffer[s._pos];

    string container = "";
    int type = TOKEN_UNKNOWN;
    int start = 0;
    for(int i = 0; i < strlen(ALFA); i++){
        if(a == ALFA[i]){
            type = TOKEN_ALPHA;
            start = START_ALPHA;
        }
    }
    if(a == '\"'){
        //cout << "a is equal to quotation" << endl;
        type = TOKEN_QUOT;
        start = START_QUOT;
    }
    for(int i = 0; i < strlen(DIGITS); i++){
        if(a == DIGITS[i]){
            type = TOKEN_NUMBER;
            start = START_DOUBLE;
        }
    }
     for(int i = 0; i < strlen(OPERATORS); i++){
        if(a == OPERATORS[i]){
            type = TOKEN_OPERATOR;
            start = START_OPERATOR;
        }
    }
     for(int i = 0; i < strlen(SPACES); i++){
        if(a == SPACES[i]){
            //cout << "a is a space" << endl;
            type = TOKEN_SPACE;
            start = START_SPACES;
        }
    }
     for(int i = 0; i < strlen(PUNC); i++){
        if(a == PUNC[i]){
            type = TOKEN_PUNC; 
            start = START_PUNC;
        }
    }

   // for(int i = 0; i < strlen(QUOT); i++){
       
    //}

    // for(int i = 0; i < strlen(QUOT); i++){
    //     if(a == QUOT[i]){
    //         type = TOKEN_QUOT;
    //         start = START_QUOT;
    //     }
    // }


    s.get_token(start ,container);
    t = PToken(container, type);
    return s;
}