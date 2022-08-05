#ifndef TABLE_H
#define TABLE_H

#include "../queue/MyQueue.h"
#include "../token/token_children.h"
#include "../binary_files/file_record.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "typedefs.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class Table{
    public:
    Table();
    //exactly the same as the third on, except you are setting default name and default fields in the vector


    Table(const string& name);
    //do this if you already have a binary file
    //based on the data in the binary file, you reindex the fields and make the table again 



    Table(const string& name, vectorstr fields); //start with this one first, 
    //creating bin file with the name param
    //insert the field name into the first line of the binary file
    //index is going to store this into 
    //initialize the rest of the members


    void insert_into(vectorstr row);
    //add a new record at the end of the file
    //add record number to the _results

    
    Table select(vectorstr fields, string left, string oper, string right); // start here and build your way down by return the last one
    Table select(vectorstr fields, Queue<Token*>& post);
    Table select(vectorstr fields, vectorstr condition);
    Table select_all();
    void reindex();

    vectorlong select_recnos();
    vectorstr get_fields();

    void set_fields(const vectorstr& fields);
    void loop_table(Table& t, vectorlong results, FileRecord rec, fstream& f);

    void table_helper(Table &t, vectorlong results, FileRecord rec, fstream &fs);



    friend ostream& operator<<(ostream& outs, const Table& printme){
        FileRecord record;
        fstream f;
        string name = printme.title;
        open_fileRW(f, name.c_str());
        int selected = 0;
        // string temp = "table_selected" + printme.title + "extra" + to_string(_serial);
        // cout << temp << endl;
        outs << setw(25) <<  "record" << setw(25);
        for(int i =0; i < printme.field_names.size(); i++){
            outs << setw(25) << printme.field_names[i];
        }
        outs << endl;
        for(int i =0; i < printme._results.size(); i++){
            record.read(f, printme._results[i]);
            outs << setw(25) << i << setw(25) << record <<endl;
        }
        f.close();
        return outs;
    }


    private:
    string title;
    vector<mmap_sl*> _index; // most important member 
    vectorlong _results;
    map_sl _fields;
    vectorstr field_names;
    static int _serial;
    long last_record;
    bool empty;
};



#endif