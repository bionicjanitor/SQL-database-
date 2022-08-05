#ifndef SQL_H
#define SQL_H

#include "../table/table.h"
#include "../parser/parser.h"

class SQL{
public:
    SQL();
    Table command(const string& str);
    vectorlong select_recnos();


private:
    vectorlong record_numbers;
    

};


#endif