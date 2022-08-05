#include "state_machine_functions.h"

void init_table(int _table[][MAX_COLUMNS]){
    for(int i = 0; i < MAX_ROWS; i ++){
        for(int j = 0; j < MAX_COLUMNS; j++){
            _table[i][j] = -1;
        }
    }
}

void mark_success(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 1;
}

void mark_fail(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 0;
}

bool is_success(int _table[][MAX_COLUMNS], int state){
    if(_table[state][0] == 1){
        return true;
    }
    return false;
}

void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state){
    for(int i = from; i <= to; i++){
        _table[row][i] = state; 
    }
    
}

void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state){
    const bool debug = true;
    if(debug){
        //cout << "marking cells" << endl;
        for(int i = 0; i < strlen(columns); i++){
            _table[row][columns[i]] = state; 
       }
    }
}

void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state){
    table[row][column] = state;
}

void print_table(int _table[][MAX_COLUMNS]){
    for(int i = 0; i < MAX_ROWS; i++){
        for(int j = 0; i < MAX_COLUMNS; j++){
            cout<< "["<< _table[i][j] << "]"; 
        }
        cout << endl;
    }
}

void show_string(char s[], int _pos){
    for(int i = 0; i < strlen(s); i++){
        cout << s[i]; 
    }
    cout << endl;
    for(int i = 0; i < _pos; i++){
        cout << " ";
    }
    cout << "^" << endl;
}
