#ifndef PARSER_H
#define PARSER_H

#include "../bplustree/multimap.h"
#include "../bplustree/map.h"
#include "../queue/MyQueue.h"
#include "../tokenizer/stokenize.h"
#include "typedefs.h"
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Parser
{
private:
   mmap_ss ptree;
   Map<string, int> keywords;
   Queue<string> input_q;
   enum keys{SELECT = 1, MAKE, INSERT, CREATE, DROP, VALUE, FIELDS, SYMBOL, FROM, STAR, WHERE, TABLE, ZERO, INTO, CONDITION};
   bool fail_flag;
   int _table[256][256];
public:
    Parser();

    Parser(const char* s);
    
    const mmap_ss& parse_tree() ;
    bool get_parse_tree();

    
    void set_string(string str);
    Map<string, int> get_column();
    void build_keyword_list();
    void make_parse_table(int _table[][256]); // making the keyword table
    void init_parse_table(int _table[][256]); // makes intial table
    bool is_fail();
    
};








#endif