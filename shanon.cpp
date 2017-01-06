#include "shanon.h"


hlTable * _buildTable(char *inputString)
{
	int lStr=strlen(inputString);
	hlTable *table = (hlTable *)malloc(sizeof(hlTable));
	table->first = NULL;
	table->last = NULL;
	// Создать массив размер 256(ANSII 256)
	int * probability = (int *)malloc(sizeof(int)*256);
	
	//Инициализацировать массив
	init(probability);
	int cur_max=0;
	//Индекс массива в соотвестие символу
	for(int i=0; inputString[i]!='\0'; i++){
		probability[(unsigned char) inputString[i]]++;
		if(probability[(unsigned char) inputString[i]]> cur_max)
			cur_max=probability[(unsigned char) inputString[i]];
	}	
	
	hlNode *cur=table->first;	
	for(int j=1; j<=cur_max;j++){		
	for(int i=0; i<256; i++){
		if(probability[i]==j)
		{
		if(cur!=NULL){			
		hlNode *temp=cur;
		cur=(hlNode *)malloc(sizeof(hlNode));
		cur->next=temp;
		}
	    else{
			table->last=(hlNode *)malloc(sizeof(hlNode));
			cur=table->last;
		}
		    cur->symbol=(char) i;
			cur->code="0";
			cur->probability=(double)j/(double)lStr;
		}
	}	
}
	table->first=cur;
	table->last->next=NULL;
	getCode(table,lStr);
	return table;
}

int * init(int * arr)
{
	for(int i=0; i<256; i++)
		arr[i]=0;
	return arr;
}

void getCode(hlTable *table, int max_len)
{
	char * arr=(char *)malloc(sizeof(char)*max_len);
	arr[0]='1';
	arr[1]='\0';
	int k=0;
	bool flag=false;
	hlNode* cur=table->first;
	while(cur!=NULL)
	{
		cur->code=(char *)malloc(sizeof(char)*max_len);
		int i=0;
		for(i=0;arr[i]!='\0';i++)
			cur->code[i]=arr[i];
		cur->code[i]='\0';
		if(flag==false)
		{
			cur=cur->next;
			arr[k]='0';
		    k++;
			arr[k]='0';
			flag=true;
			arr[k+1]='\0';
		}
		else 
		{
			if(cur->next!=NULL)
			arr[k]='1';
			flag =false;			
		}
	}

}

void _decode(hlTable *table,const char *stringToDecode)
{
	hlTable *temp=(hlTable *)malloc(sizeof(hlTable));
	temp->first=NULL;
    temp->last=NULL;
	hlNode* cur=table->first;
	hlNode* aux;
	char*result=(char *)malloc(sizeof(char)*128);
	while(cur!=NULL)
	{
		if(temp->first==NULL){
		temp->first=(hlNode *)malloc(sizeof(hlNode));
		temp->first->code=cur->code;
		temp->first->symbol=cur->symbol;
		aux=temp->first;
		temp->last=aux;
		}
		else
		{
			hlNode* t=aux;
			aux=(hlNode *)malloc(sizeof(hlNode));
			aux->code=cur->code;
			aux->symbol=cur->symbol;
			aux->next=t;
		}
		cur=cur->next;			
	}	
	temp->first=aux;
	temp->last->next=NULL;
	cur=temp->first;
	string res="";
	int i=0;
	
	while(i<strlen(stringToDecode))
	{
	while(cur!=NULL)
	{
		bool flag = true;
		int j=0;
		int k=i;
		for(;j<strlen(cur->code);j++,k++)
		{
			if(cur->code[j]!=stringToDecode[k]){
				flag=false;
				break;
			}
		}
		if(flag==true)
		{
			res+=cur->symbol;
			i+=j;
		}
			cur=cur->next;
	}
	cur=temp->first;
	}
	printf("Декодирование\nВходящая строка:%s\nРезултат:%s\n",stringToDecode,res.c_str());
	return;
}