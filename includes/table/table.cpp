#include "table.h"

int Table::_serial = 0;


Table::Table(){
    
}

Table::Table(const string& name){
    const bool debug = true;
    //_serial++;
    last_record =-1;
    ifstream of;

    title = name + ".bin"; //becoming the file
    string fieldnames = name+ ".txt";
    //_index = Map<string, mmap_sl*>();
 
    of.open(fieldnames); // opening the existing text file
    string temp = "";
    while(getline(of, temp)){
        field_names.push_back(temp);
    }
 
    for(int i = 0; i < field_names.size(); i++){
        _fields.insert(field_names[i], i);
        _index.push_back(new mmap_sl());
    }
    //open_fileRW(f, title.c_str()); // opening binary file
    reindex();
    of.close();
}

Table::Table(const string& name, vectorstr fields){
    _serial++;
    last_record =-1;
    ofstream of;
    fstream f;
    title = name + ".bin"; //becoming the file
    string fieldnames = name+ ".txt";
    //cout << "table: " << __LINE__ << endl; 
    //_index = Map<string, mmap_sl*>();
    _fields = map_sl();
    //cout << "table: " << __LINE__ << endl; 
    //cout << "fields: " << fields << endl;
    field_names = fields;
    //cout << "field_names: " << field_names << endl;
    of.open(fieldnames); // opening the text file
    open_fileW(f, title.c_str()); // opening binary file
    for(int i = 0; i < field_names.size(); i++){
        _fields.insert(field_names[i], i);                                                                                            
        of << fields[i] << endl;
        _index.push_back(new mmap_sl());
    } 
    of.close();
    f.close();
    
}

void Table::insert_into(vectorstr row){
    //cout << "table: " << __LINE__ << endl; 
    fstream f;
    FileRecord rec(row);
    string bin = title;
    //cout << "table: " << __LINE__ << endl; 
    open_fileRW(f, bin.c_str());
    //cout << "table: " << __LINE__ << endl; 
    last_record ++; // incrementing the last record
    _results.push_back(last_record);
   // cout << "table: " << __LINE__ << endl; 
    for(int i = 0; i < row.size(); i++){
      //  cout << "table: " << __LINE__ << endl; 
        
        long index = _fields.at(field_names[i]);
        //cout << "table: " << __LINE__ << endl; 
        _index.at(i)->at(row[i]).push_back(last_record);
    }
    //cout << "table: " << __LINE__ << endl; 
    rec.write(f);
   // cout << "table: " << __LINE__ << endl; 
    f.close();
}


void Table::reindex(){
    FileRecord r2;
    fstream file; 
    long recno = 0;
    open_fileRW(file, title.c_str());
    file.seekg(0, ios::end);
    int filesize = file.tellg();
    int recordsize = sizeof(r2._record);
    long number_recs = filesize/recordsize;
    _results.clear();
    for(int i = 0; i < number_recs; i++){
        //long index = _fields.at(field_names[i]);
        _results.push_back(i); 
        r2.read(file, i);
        for(int j = 0; j < field_names.size(); j++){
            //long index = _fields.at(field_names[j]);
            _index.at(j)->at(r2._record[j]).push_back(i);
        }  
    }
    file.close(); 
    last_record = number_recs - 1;
}

Table Table::select(vectorstr fields, string left, string oper, string right){
    //_serial++;
    
    vectorlong new_records;
    if(oper == "="){
        new_records = _index.at(_fields.at(left))->at(right);
    }   
    if(oper == "<") {
         mmap_sl::Iterator it = _index.at(_fields.at(left))->begin();
          // end of the iterator where you want to reach
        for(; it != _index.at(_fields.at(left))->lower_bound(right); it++){
            for(int i = 0; i < (*it).value_list.size(); i++){
                new_records.push_back((*it).value_list.at(i)); // pushing back everything 
            }
        }
    }
    if(oper == ">"){
         mmap_sl::Iterator it = _index.at(_fields.at(left))->upper_bound(right);
          // end of the iterator where you want to reach
        for(; it != _index.at(_fields.at(left))->end(); it++){
            for(int i = 0; i < (*it).value_list.size(); i++){
                new_records.push_back((*it).value_list.at(i)); // pushing back everything 
            }
        }
    }
    if(oper == "<="){
           mmap_sl::Iterator it = _index.at(_fields.at(left))->begin();
          // end of the iterator where you want to reach
        for(; it != _index.at(_fields.at(left))->upper_bound(right); it++){// go one more ahead cuz its equal to
            for(int i = 0; i < (*it).value_list.size(); i++){
                new_records.push_back((*it).value_list.at(i)); // pushing back everything 
            }
        }
    }
    if(oper == ">="){
        mmap_sl::Iterator it = _index.at(_fields.at(left))->lower_bound(right);
          // end of the iterator where you want to reach
        for(; it != _index.at(_fields.at(left))->end(); it++){
            for(int i = 0; i < (*it).value_list.size(); i++){
                new_records.push_back((*it).value_list.at(i)); // pushing back everything into a new vecotr of the record numbers
            }
        }
    }
    FileRecord filerecord;
    fstream file;
    open_fileRW(file, title.c_str()); // connecting the fstream object to the old binfile
    _results.clear();
    string newtitle = "new" + to_string(_serial);
    Table temp(newtitle, fields);
    vectorstr row;
    for(int i =0; i < new_records.size(); i++){
        filerecord.read(file, new_records[i]); // getting info from here to push back into row
        for(int j =0; j < fields.size(); j++){
            long index = _fields.at(fields[j]); // gives me the field numbers
            row.push_back(filerecord._record[index]); 
        }
        temp.insert_into(row);
        row.clear(); //making empty
    }
    //temp._results = new_records;
    _results = new_records;
    file.close();
    return temp;
}

vectorlong Table::select_recnos(){
    return _results;
}

Table Table::select_all(){ 
    FileRecord filerecord;
    fstream file;
    open_fileRW(file, title.c_str()); 
    string newtitle = "new" + to_string(_serial);
    Table temp(newtitle, field_names);
    vectorstr row;
    for(int i =0; i < _results.size(); i++){
        filerecord.read(file, _results[i]); // getting info from here to push back into row
        for(int j =0; j < field_names.size(); j++){
            long index = _fields.at(field_names[j]); // gives me the field numbers
            row.push_back(filerecord._record[index]); 
        }
        temp.insert_into(row);
        row.clear(); //making empty
    }
    //temp._results = new_records;
    file.close();
    return temp;
    
}

Table Table::select(vectorstr fields, Queue<Token*>& post){
    //ShuntingYard sy(post); // just the sy object
    Queue<Token*> tok = post;
    RPN rpn(tok);
    vectorlong eval = rpn.eval(_index, _fields); 
    // cout << "eval: " << eval << endl;
    // cout << "eval_size: " << eval.size() << endl;
    _results.clear();
    FileRecord r2;
    fstream oldfile;
    open_fileRW(oldfile, title.c_str());
    vectorstr row;
    string newtable = "new" + to_string(_serial);
    Table temp(newtable, fields);
    for(int i = 0; i < eval.size(); i++){
        r2.read(oldfile, eval[i]);
        for(int j =0; j < fields.size(); j++){
            long index = _fields.at(fields[j]); // gives me the field numbers
            row.push_back(r2._record[index]); 
        }
        temp.insert_into(row);
        row.clear(); //making empty
    }
    _results = eval;
    oldfile.close();
    return temp;
}

Table Table::select(vectorstr fields, vectorstr condition){
    Queue<Token*> post;
    for(int i = 0; i < condition.size(); i++){
        if(condition[i] == "("){
            //cout << "table: " << __LINE__ << endl;
            post.push(new LParen());
        }    
        else if(condition[i] == ")"){
            post.push(new RParen());
        }
        else if(condition[i] == "and" || condition[i] == "or"){
            post.push(new Logical(condition[i]));
        }
        else if(condition[i] == ">" || condition[i] == "<" || condition[i] == "=" || condition[i] == ">=" || condition[i] == "<="){
            post.push(new Relational(condition[i]));
        }else{
            post.push(new TokenStr(condition[i]));
        }
        
    }
    
    ShuntingYard sy(post);
    Queue<Token*> postfix = sy.postfix();
    //Queue<Token*> postfixtest = postfix;
    // for (int i = 0; i < postfix.size(); i++){
    //     cout << postfixtest.pop()->token_str() << endl;
    // }

    return select(fields, postfix);
}

void Table::set_fields(const vectorstr& fields){
    field_names = fields;
}

vectorstr Table::get_fields(){
    return field_names;
}

void Table::table_helper(Table &t, vectorlong results, FileRecord rec, fstream &fs) {

    // Test for grabbing only certain columns.
    long i = 0;
    long bytes = rec.read(fs, i);
    while (bytes > 0) {

        if (find(results.begin(), results.end(), i) != results.end()) {
            vectorstr row;
            int n = 0;
            while (rec._record[n][0] != '\0') {
                row.push_back(rec._record[n]);
                n++;
            }
            t.insert_into(row);
        }
        i++;
        bytes = rec.read(fs, i); 
    }
}
