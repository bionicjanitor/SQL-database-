#include "parser.h"


Parser::Parser(){
fail_flag = false;
}

Parser::Parser(const char* s){
    set_string(s);
}


void Parser::set_string(string str){
    char buffer[300];
    
    strcpy(buffer, str.c_str());
    ptree.clear();
    STokenizer stok(buffer);
    PToken t;
    stok >> t;
    while(stok.more()){
        if(t.type() != 5 && t.type() != 3){
            // cout << "t_str(): " << t.token_str() << endl;
            input_q.push(t.token_str());
        }
           t = PToken();

        stok >> t;
    //         cout << t << " type:" << t.type() <<endl;
    }
    make_parse_table(_table);
    build_keyword_list();
    // cout << "parser: " << __LINE__ << endl;
    fail_flag = get_parse_tree();
    // cout << boolalpha << fail_flag << ": fail_flag" << endl;
    // cout << "count: " << count << endl;
}

void Parser::init_parse_table(int _table[][256]){
    init_table(_table);
}

void Parser::make_parse_table(int _table[][256]){
     // use this to never change the value when adding on to it plus to space however you want it to be
    init_parse_table(_table); // everything fail
    mark_success(_table, 5);
    mark_success(_table, 7);
    mark_cell(0, _table, SELECT, select_parse);
    mark_cell(select_parse, _table, STAR, select_parse+2);
    mark_cell(select_parse, _table, SYMBOL, select_parse+1);
    mark_cell(select_parse+1, _table, SYMBOL, select_parse+1); // reiteration
    mark_cell(select_parse+1, _table, FROM, select_parse+3); // 2 to 4
    mark_cell(select_parse+2, _table, FROM, select_parse+3); // 3 to 4
    mark_cell(select_parse+3, _table, SYMBOL, select_parse+4);
    mark_cell(select_parse+4, _table, WHERE, select_parse+5); //first success state
    mark_cell(select_parse+5, _table, SYMBOL, select_parse+6);
    mark_cell(select_parse+6, _table, SYMBOL, select_parse+6);// reiteration

    //for insert command
    
    mark_success(_table, 13);
    mark_cell(0, _table, INSERT, insert_parse);
    mark_cell(insert_parse, _table, INTO, insert_parse+1);
    mark_cell(insert_parse+1, _table, SYMBOL, insert_parse+2);
    mark_cell(insert_parse+2, _table, VALUE, insert_parse+3);
    mark_cell(insert_parse+3, _table, SYMBOL, insert_parse+4);
    mark_cell(insert_parse+4, _table, SYMBOL, insert_parse+4);
   
   //for create/make command
     // cushion space
    mark_success(_table, 19);
    mark_cell(0, _table, MAKE, cmake_parse);
    mark_cell(0, _table, CREATE, cmake_parse);
    mark_cell(cmake_parse, _table, TABLE, cmake_parse+1);
    mark_cell(cmake_parse+1, _table, SYMBOL, cmake_parse+2);
    mark_cell(cmake_parse+2, _table, FIELDS, cmake_parse+3);
    mark_cell(cmake_parse+3, _table, SYMBOL, cmake_parse+4);
    mark_cell(cmake_parse+4, _table, SYMBOL, cmake_parse+4);

    //for drop command
     // cushion space
    mark_success(_table, 23);
    mark_cell(0, _table, DROP, drop_parse);
    mark_cell(drop_parse, _table, TABLE, drop_parse+1);
    mark_cell(drop_parse+1, _table, SYMBOL, drop_parse+2);

}

void Parser::build_keyword_list(){
    keywords.insert("select", SELECT);
    keywords.insert("insert", INSERT);
    keywords.insert("make", MAKE);
    keywords.insert("create", CREATE);
    keywords.insert("drop", DROP);
    keywords.insert("values", VALUE);
    keywords.insert("fields", FIELDS);
    keywords.insert("symbol", SYMBOL);
    keywords.insert("from", FROM);
    keywords.insert("star", STAR);
    keywords.insert("where", WHERE);
    keywords.insert("table", TABLE);
    keywords.insert("into", INTO);
    // keywords.insert("condition", CONDITION);
}


bool Parser::get_parse_tree(){ 
    int state = 0;
   // cout << "parsing tree baby" << endl;
    while(!input_q.empty() && state != -1){
        string temp = input_q.pop();
        // cout << "temp: " << temp << endl; 
        if(keywords.contains(temp)){
            int next_state = _table[state][keywords[temp]];
            state = next_state;
            
        }else{
            state = _table[state][SYMBOL];
        }
        switch(state){
                case select_parse:{
                    // cout << "parser: " << __LINE__ << endl;
                    ptree.get("command").push_back(temp);//1
                    break;
                }
              
                case select_parse+1:{
                    // cout << "parser: " << __LINE__ << endl;
                    ptree.get("fields").push_back(temp);
                    break; //2
                }
                
                case select_parse+2:{
                   // cout<< "parse_tree+2" << endl;
                    ptree.get("fields").push_back(temp);
                    break; // 3
                }

                case select_parse+3:{
                    break;
                }

                case select_parse+4:{
                    ptree.get("table_name").push_back(temp);
                    break; // 4
                }

                case select_parse+5:{
                    ptree.get("where").push_back("yes");
                    break;//5
                }

                case select_parse+6:{
                    ptree.get("condition").push_back(temp);
                    break; //6
                }

                

                case insert_parse:{
                    ptree.get("command").push_back(temp);
                    break;//7
                }
               

                case insert_parse+1:{
                    break;
                }
               

                case insert_parse+2:{
                    ptree.get("table_name").push_back(temp);
                    break; //8
                }
               

                case insert_parse+3:{
                    break;
                }
                

                case insert_parse+4:{
                    ptree.get("values").push_back(temp);
                    break;//9
                }
                

                case cmake_parse:{
                    ptree.get("command").push_back(temp);
                    break;//10
                
                }

                case cmake_parse+1:{
                break;
                }

                case cmake_parse+2:{
                ptree.get("table_name").push_back(temp);
                    break; // 11
                } 

                case cmake_parse+3:{
                    break;
                }

                case cmake_parse+4:{
                    ptree.get("col").push_back(temp);
                    break; // 12
                }

                case drop_parse:{
                    ptree.get("command").push_back(temp);
                    break; // 13
                }
               

                case drop_parse+1:{
                    ptree.get("table").push_back(temp);
                    break; // 14
                }
               

                case drop_parse+2:{
                    ptree.get("condition").push_back(temp);
                    break; // 15
                }
                

                default: {

                }

                }
    }
    //cout << "end of parsing tree baby" << endl;
    if(state != -1){
        //cout << "in success state" << endl;
        return true;

    }else{
        //cout << "not in success state" << endl;
        ptree.clear();
        //cout << "cleared" << endl;
        return false;
    }
    
}

// bool is_fail(){
//     return fail_flag;
// }

const mmap_ss& Parser::parse_tree() {
   // cout << "returning a ptree" << endl;
    return ptree;
}