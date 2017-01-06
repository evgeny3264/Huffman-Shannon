#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"
#include "pQueue.h"

void traverseTree(htNode *treeNode, hlTable **table, int k, char code[256])
{
	
	if(treeNode->left == NULL && treeNode->right == NULL)
	{
		code[k] = '\0';
		hlNode *aux = (hlNode *)malloc(sizeof(hlNode));
		aux->code = (char *)malloc(sizeof(char)*(strlen(code)+1));
		strcpy(aux->code,code);
		aux->symbol = treeNode->symbol;
		aux->next = NULL;
		aux->probability=treeNode->probability;
		if((*table)->first == NULL)
		{
			(*table)->first = aux;
			(*table)->last = aux;
		}
		else
		{
			(*table)->last->next = aux;
			(*table)->last = aux;
		}
		
	}
	
	if(treeNode->left!=NULL)
	{
		code[k]='0';
		traverseTree(treeNode->left,table,k+1,code);
		
	}
	
	if(treeNode->right!=NULL)
	{
		code[k]='1';
		traverseTree(treeNode->right,table,k+1,code);
		
	}
}

hlTable * buildTable(htTree * huffmanTree)
{
	//Инициализировать таблицу 
	hlTable *table = (hlTable *)malloc(sizeof(hlTable));
	table->first = NULL;
	table->last = NULL;
	
	char code[256];
	//уровень обхода дерева
	int k=0;

	//Обойти дерево и вычислить коды
	traverseTree(huffmanTree->root,&table,k,code);
	return table;
}

htTree * buildTree(char *inputString)
{
	int lStr=strlen(inputString);
	// Создать массив размер 256(ANSII 256)
	int * probability = (int *)malloc(sizeof(int)*256);
	
	//Инициализацировать массив
	for(int i=0; i<256; i++)
		probability[i]=0;

	//Индекс массива в соотвестие символу
	for(int i=0; inputString[i]!='\0'; i++)
		probability[(unsigned char) inputString[i]]++;

	//Объявить очередь и выделить память 
	pQueue * huffmanQueue;
	initPQueue(&huffmanQueue);

	//Создать узел в очереди
	for(int i=0; i<256; i++)
		if(probability[i]!=0)
		{
			htNode *aux = (htNode *)malloc(sizeof(htNode));
			aux->left = NULL;
			aux->right = NULL;
			aux->symbol = (char) i;
			
			addPQueue(&huffmanQueue,aux,probability[i]);
		}

	//Освободить память
	free(probability);

	//Построить дерево
	while(huffmanQueue->size!=1)
	{
		int priority=huffmanQueue->first->priority;
		int priorityNext=huffmanQueue->first->next->priority;
		htNode *left = getPQueue(&huffmanQueue);
		left->probability=(double)priority/(double)lStr;
		htNode *right = getPQueue(&huffmanQueue);
		right->probability=(double)priorityNext/(double)lStr;

		htNode *newNode = (htNode *)malloc(sizeof(htNode));
		newNode->left = left;
		newNode->right = right;		
		priority+=priorityNext;
		addPQueue(&huffmanQueue,newNode,priority);
	}
		
	htTree *tree = (htTree *) malloc(sizeof(htTree));

	tree->root = getPQueue(&huffmanQueue);
	
	return tree;
}

string encode(hlTable *table, char *stringToEncode)
{
	hlNode *traversal;
	
	printf("\nКодирование\nВходящая строка : %s\nРезультат : \n",stringToEncode);

	string temp="";
	for(int i=0; stringToEncode[i]!='\0'; i++)
	{
		traversal = table->first;
		while(traversal->symbol != stringToEncode[i])
			traversal = traversal->next;
		printf("%s",traversal->code);
		temp+=traversal->code;
	}

	printf("\n");
	return temp;
}

void decode(htTree *tree,const char *stringToDecode)
{
	htNode *traversal = tree->root;
	printf("\nДекодирование\nВходящая строка: %s\nРезультат : \n",stringToDecode);
		
	for(int i=0; stringToDecode[i]!='\0'; i++)
	{
		if(traversal->left == NULL && traversal->right == NULL)
		{
			printf("%c",traversal->symbol);
			traversal = tree->root;
		}
		
		if(stringToDecode[i] == '0')
			traversal = traversal->left;

		if(stringToDecode[i] == '1')
			traversal = traversal->right;

		if(stringToDecode[i]!='0'&&stringToDecode[i]!='1')
		{
			printf("Входящая строка некорректна!\n");
			return;
		}
	}

	if(traversal->left == NULL && traversal->right == NULL)
	{
		printf("%c",traversal->symbol);
		traversal = tree->root;
	}

	printf("\n");
}

void printTable(hlTable * hlT)
{
	hlNode* cur=hlT->first;
	printf("\nCимвол\tКод\tВероятность\tЭнтропия");
	while(cur!=NULL)
	{
		double probability=cur->probability;
		double entropy=-(log10(probability)/log10(2));
		printf("\n  %c\t%s\t%.3f\t\t%.3f",cur->symbol,cur->code,probability,entropy);
		cur=cur->next;		
	}
	printf("\n");
}