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
	string sHuffman("����� ��������");
	string sShannon("����� �������-����");
	string in;
	while (true){
		cout << "�������� ����� ������:\n1.����� ��������\n2.����� �������-����\n3.�����\n";
		getline(cin, in);
		if (in.compare("1") == 0){
			cout << sHuffman << endl << "������� ������ :" << endl;
			flag = true;
		}
		else if (in.compare("2") == 0){
			cout << sShannon << endl << "������� ������ :" << endl;
			flag = false;
		}
		else if (in.compare("3") == 0){
			system("pause");
			return 0;
		}
		else{
			cout << "������, ������ ������ ���� �� ����������!" << endl;
			continue;
		}
		string input_str("");
		// ���� ������
		getline(cin, input_str);
		char  *str = &input_str[0];
		OemToCharA(str, str);
		if (flag){
			// �������� ������ 
			htTree *codeTree = buildTree(str);
			// �������� ������� ��������
			hlTable *codeTable = buildTable(codeTree);
			// ������ ������� 
			printTable(codeTable);
			// ����������� 
			string code = encode(codeTable, str);
			//�������������
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