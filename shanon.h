#include "huffman.h"
hlTable * _buildTable(char *inputString);
int * init(int * arr);
void getCode(hlTable *table, int max_len);
void _decode(hlTable *table,const char *stringToDecode);