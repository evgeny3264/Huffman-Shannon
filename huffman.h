#pragma once
#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

typedef struct _htNode {
	char symbol;
	struct _htNode *left, *right;
	double probability;
}htNode;


typedef struct _htTree {
	htNode *root;
}htTree;


typedef struct _hlNode {
	char symbol;
	char *code;
	double probability;
	struct _hlNode *next;
}hlNode;


typedef struct _hlTable {
	hlNode *first;
	hlNode *last;
}hlTable;

htTree * buildTree(char *inputString);
hlTable * buildTable(htTree *huffmanTree);
string encode(hlTable *table, char *stringToEncode);
void decode(htTree *tree,const char *stringToDecode);
void printTable(hlTable * hlT);
#endif