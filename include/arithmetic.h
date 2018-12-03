
// ���������� ������� � ������� ��� ���������� �������������� ���������
#pragma once
#include <iostream>
#include "cstdlib"
#include <string>
#include <vector>
#ifndef arithmetic_H
#define arithmetic_H


#include "cstdio"
#include "Stack.h"



enum operation {PLUS, MINUS, MULT, DIV, O_BRACE, C_BRACE,UN_MINUS};

typedef operation Op;

struct Lecsema
{
	bool isNum;//k=1 �����, ���� k=0  ��������
	double a;//�����
	Op b;//��������
};

class TFormula
{
private:
	string formula;//���������
	vector <Lecsema> lecs;//������ ������
	vector <Lecsema> rev_lecs;//�������� �������� ������
	int n;//���������� ������ � ���������

public:
	TFormula();//�����������
	TFormula(string s);//����������� � ����������
	~TFormula();//����������
	void Write();//������ ��������� �������������
	bool Checker();//�������� ������������ ��������� ���������
	void Converter();//������ ��������� �� ������ ������
	void Postfix_Entry();//������� � �������� �������� ������
	double Calculator();//���������� ���������
};

#endif // !arithmetic_H