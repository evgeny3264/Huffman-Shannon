#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "shanon.h"

int main(void)
{
	setlocale(LC_ALL, "Russian");
	bool flag = true;
	string sHuffman("Метод Хаффмана");
	string sShannon("Метод Шеннона-Фано");
	string in;
	while (true){
		cout << "Выберете метод сжатия:\n1.Метод Хаффмана\n2.Метод Шеннона-Фано\n3.Выход\n";
		getline(cin, in);
		if (in.compare("1") == 0){
			cout << sHuffman << endl << "Введите строку :" << endl;
			flag = true;
		}
		else if (in.compare("2") == 0){
			cout << sShannon << endl << "Введите строку :" << endl;
			flag = false;
		}
		else if (in.compare("3") == 0){
			system("pause");
			return 0;
		}
		else{
			cout << "Ошибка, такого пункта меню не существует!" << endl;
			continue;
		}
		string input_str("");
		// Ввод строки
		getline(cin, input_str);
		char  *str = &input_str[0];
		OemToCharA(str, str);
		if (flag){
			// Создание дерева 
			htTree *codeTree = buildTree(str);
			// Создание таблицы символов
			hlTable *codeTable = buildTable(codeTree);
			// Печать таблицы 
			printTable(codeTable);
			// Кодирование 
			string code = encode(codeTable, str);
			//Декодирование
			decode(codeTree, code.c_str());
		}
		else
		{
			hlTable *_codeTable = _buildTable(str);
			printTable(_codeTable);
			string _code = encode(_codeTable, str);
			_decode(_codeTable, _code.c_str());
		}
	}
	system("pause");
	return 0;
}