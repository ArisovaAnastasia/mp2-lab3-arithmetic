#include "arithmetic.h"


TFormula::TFormula()
{
	n = 0;
}

TFormula::TFormula(string s)
{
	formula=s;
	this->Converter();
}

TFormula::~TFormula()
{
	n = 0;
	formula.clear();
	lecs.clear();
	rev_lecs.clear();
}

void TFormula::Write()
{
	getline(cin, formula);
	this->Converter();
	cout << formula << endl;
}

bool TFormula::Checker()
{
	int n_brace = 0;//���������� ������
	int i = 0;
	int indicator=1;//��������� ������������ ���������
	while (i < lecs.size()-1)
	{
		//���� ������� ������� �����, �� ��������� ������� ���� ������� �����, ���� ����������� ������
		if (lecs[i].isNum)
			if((!lecs[i + 1].isNum) && (lecs[i + 1].b != UN_MINUS) && (lecs[i + 1].b != O_BRACE))
			;
			else
			{
				indicator = 0;
				cout << "������ ������������ ������ ����� �����!" << endl;
			}

		//���� ������� ������� ����������� ������, �� ��������� ������� ���� �����, ���� ����������� ������,���� ������� �����
		if ((!lecs[i].isNum) && (lecs[i].b == O_BRACE))
		{
			if (((!lecs[i + 1].isNum) && ((lecs[i + 1].b == O_BRACE)|| (lecs[i + 1].b ==UN_MINUS))) || (lecs[i + 1].isNum))
				;
			else
			{
				indicator = 0;
				cout<<"������� ������������ ������ ����� ����������� ������!" << endl;
			}
			n_brace++;
		}

		//���� ������� ������� ����������� ������, �� ��������� ������� ���� ��������, ���� ����������� ������
		if ((!lecs[i].isNum) && (lecs[i].b == C_BRACE))
		{
			if (((!lecs[i + 1].isNum) && (lecs[i + 1].b !=O_BRACE)))
				;
			else
			{
				indicator = 0;
				cout<< "������ ������������ ������ ����� ����������� ������!" << endl;
			}
			n_brace--;
		}

		//���� ������� ������� ��������, �� ��������� ������� ���� �����, ���� ����������� ������, ���� ������� �����
		if ((!lecs[i].isNum) && (lecs[i].b != C_BRACE) && (lecs[i].b != O_BRACE))
		{
			if ((lecs[i + 1].isNum) || ((!lecs[i + 1].isNum) && ((lecs[i + 1].b == O_BRACE) || (lecs[i + 1].b == UN_MINUS))))
				;
			else
			{
				indicator = 0;
				cout<<"������ ����������� ������ ����� ��������!" << endl;
			}
		}

		//�������� ������� ������
		if (n_brace >= 0)
			;
		else
		{
			indicator = 0;
			cout<< "������ ������������ ������� ������!" << endl;
		}
		i++;
	}

	/*� ������ ���������� ��������� ����������� � ������, 
	������� ��������� ������� �������� ����������� ������, ������� ���� ������.*/
			n_brace--;

	//�������� ���������� ������
	if(n_brace==0)
	 ;
	else
	{
		cout << "������� ������������ ����� ������!" << endl;
		indicator = 0;
	}

	if (indicator)
	{
		return true;
	}	
	else
	{
		this->~TFormula();
		return false;
	}
}

void TFormula::Converter()
{
	int i = 0;
	string number;
	Lecsema temp;

	//��������� ������� ��������
	temp.isNum = false;
	temp.b = O_BRACE;
	lecs.push_back(temp);

	while (i < formula.size())
	{
		
			switch (formula[i])
			{
			case '+':
			{
				temp.isNum = false; temp.b = PLUS;
				lecs.push_back(temp);
				break;
			}
			case '-':
			{
				if ((lecs.back().b != C_BRACE) && (!lecs.back().isNum))
				{
					temp.isNum = false; temp.b = UN_MINUS;//������� �����
				}
				else
				{
					temp.isNum = false; temp.b = MINUS;//�������� �����
				}
				lecs.push_back(temp);
				break;
			}
			case '*':
			{
				temp.isNum = false; temp.b = MULT;
				lecs.push_back(temp);
				break;
			}
			case '/':
			{
				temp.isNum = false; temp.b = DIV;
				lecs.push_back(temp);
				break;
			}
			case '(':
			{
				temp.isNum = false; temp.b = O_BRACE;
				lecs.push_back(temp);
				break;
			}
			case ')':
			{
				temp.isNum = false; temp.b = C_BRACE;
				lecs.push_back(temp);
				break;
			}
			default:
			{
				break;
			}
			}
			if (((formula[i] <= '9') && (formula[i] >= '0')) || (formula[i] == '.'))//����������� �����, ���������� ������� ������ �����
			{
				while (((formula[i] <= '9') && (formula[i] >= '0')) || (formula[i] == '.')) {//���������� ����� � ���������� number
					number.push_back(formula[i]); i++;
				}
				i--;
				temp.isNum = true;
				temp.a = stod(number);
				lecs.push_back(temp);
				number.clear();
			}
		i++;
	}

	temp.isNum = false;
	temp.b = C_BRACE;
	lecs.push_back(temp);
	n = lecs.size();
	/*������ ������� ������(������ �� ����� �������)
	for (int i = 0; i < n; i++)
		if(lecs[i].isNum)
			cout << lecs[i].a<<endl;
		else 
			cout << lecs[i].b<<endl;
			*/
}

void TFormula::Postfix_Entry()
{
	Lecsema temp;
	int i = 0; 
	Stack <Op> T(n);
	int Prior[7] = {2,2,3,3,0,1,4};//������� ����������� 

	while (i<n)
	{
		//���� ������� ������� ����������� ������
		if ((lecs[i].b == O_BRACE)&&(lecs[i].isNum == false))
		{
			temp.b = lecs[i].b;
			T.Push(temp.b);
		}
		else
		{
			//���� ������� ������� �����
			if (lecs[i].isNum) 
			{
				temp.a = lecs[i].a;
				temp.isNum = true;
				rev_lecs.push_back(temp);
			}
			else
				if (!T.isEmpty())
				{
					//���� ������� ������� ����������� ������
					if (Prior[lecs[i].b] == 1)
					{
						//��������� ��� �������� �� ����������� ������
						while (T.Value() != O_BRACE)
						{
							temp.b = T.Pop();
							temp.isNum = false;
							rev_lecs.push_back(temp);
						}
						T.Pop();

					}
					//���� ������� ������� ��������
					else
					{
						//���� ������� ������� ������� �����, � ���������� ������� ���� ������� �����
						if((T.Value()==UN_MINUS)&&(lecs[i].b==UN_MINUS))
						{
							T.Push(lecs[i].b);
						}
						//���� ������� ������� �������� �������� ��� ������� ������������� ������� �����
						else
						{
							/*��������� ����������� ������� �������� � �������� �� �����.
							��������� �������� �� ����� �� ��� ���, 
							���� ��������� ������� �������� ������ ��� ����� ���������� �������� � �����*/
							while ((!T.isEmpty()) && (Prior[T.Value()] >= Prior[lecs[i].b]))
							{
								temp.b = T.Pop();
								temp.isNum = false;
								rev_lecs.push_back(temp);
							}
							T.Push(lecs[i].b);
						}
					}
				}
				else T.Push(lecs[i].b);
		}
	i++;	
	}
	//��������� ��� ���������� � ����� ��������
	while (!T.isEmpty())
	{
		temp.b = T.Pop(); 
		temp.isNum = false;
		rev_lecs.push_back(temp);
	}
	/*������ �������� �������� ������(������ �� ����� �������)
    for (int i = 0; i < rev_lecs.size(); i++)
		if (rev_lecs[i].isNum)
			cout << rev_lecs[i].a << endl;
		else
			cout << rev_lecs[i].b << endl;
			*/
}

double TFormula::Calculator()
{
	this->Postfix_Entry();

	Stack <double> T(rev_lecs.size());
	double a, b;
	
	for (int i = 0; i < rev_lecs.size(); i++)
	{
		//���� �����
		if (rev_lecs[i].isNum)
			T.Push(rev_lecs[i].a);
		//���� ��������
		else
		{
			if (rev_lecs[i].b == UN_MINUS)
			{
				a = T.Pop();
				T.Push((-1)*a);
			}
			else
			{
				b = T.Pop();
				a = T.Pop();
				switch (rev_lecs[i].b)
				{
				case PLUS:	T.Push(a + b); break;
				case MINUS:	T.Push(a - b); break;
				case MULT:	T.Push(a * b); break;
				case DIV:	T.Push(a / b); break;
				default:break;
				}
			}
		}
	}
	return T.Pop();
}