#include "sql.h"

SQL::SQL(){

}

Table SQL::command(const string& str){
    Parser ptree(str.c_str());
    mmap_ss pmap = ptree.parse_tree();
    // cout << pmap.at("command")[0] << endl;
    if(pmap.at("command")[0] == "make" || pmap.at("command")[0] == "create"){
        // cout << "sql: " << __LINE__ << endl;
        // cout << "pmap.fields: " << pmap.at("col") << endl;
       Table t(pmap.at("table_name")[0], pmap.at("col"));
       return t;
    }
    if(pmap.at("command")[0] == "insert"){
        // cout << "sql: " << __LINE__ << endl;
        Table t(pmap.at("table_name")[0]);
        // cout << "pmap.at(table_name)[0]" << pmap.at("table_name")[0] <<endl;
        // cout << "sql: " << __LINE__ << endl;
        t.insert_into(pmap.at("values"));
        // cout << "sql: " << __LINE__ << endl;
        return t;
    }
    if(pmap.at("command")[0] == "select"){
        Table t(pmap.at("table_name")[0]);
        if(pmap.at("fields")[0] == "*"){
            if(pmap.contains("condition")){
                t.select(t.get_fields(), pmap.at("condition"));
            }
            else{
                t.select_all();
            } 
        }else{
            if(pmap.contains("condition")){
                t.select(pmap.at("fields"), pmap.at("condition"));
            }else{
                t.set_fields(pmap.at("fields"));
                t.select_all();
            }
        }
        record_numbers = t.select_recnos();
        // cout << "sql: " << __LINE__ << endl;
        return t;
    }
}


vectorlong SQL::select_recnos(){
    return record_numbers;
}