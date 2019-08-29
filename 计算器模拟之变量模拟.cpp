/*
abc=10
def=8
c=abc+def
abc=abc+5-c*2
? c
? abc
end

�����Ϊ��

c=18
abc=-21

ע�⣺Ϊ�˼򻯱��ʵ�֣������ֻ�У������������� ��%�ͣޣ�ָ�����㣩�����Դ���Բ���ţ��������ٶ�������������ʽ��ȷ��

Ҫ��ʹ��ջ�ṹʵ�֡�

���룺���ʽ����

�����ȫ��ָ��������ֵ

���ʽ�е�ȫ����������Ϊ����������ڼ�������г��ֳ���Ϊ0��������������Divide 0.

�������˵����
�ڱ��ʽ�У�������������ָ���������-8������Ҫ�ر�ע�⡣���磺
10��-8��ʾΪ��10+-8��
10��-8��ʾΪ��10--8��


˼·��
	��ջ����
		1.������ֱ����ջ
		2.��������ջǰ����ε������в���������������ֱ��������
		3.��-���Ĵ���
			1.����-��ǰ��Ϊ���ֻ�����������-��Ϊ����
			2.����������Ǹ��ţ�����"#"���棬��һԪ����
		4.�Ĳ����ȼ�(-,+),(*,/,%),(^)(#)
//*/
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <math.h>
#include <map>
using namespace std;
class Calculate {
	map<char, int> optPriority;
	string expression;
	map<string, int> dict;//�洢�����Լ����������ֵ
	int error;//error == 1, divided by 0; error == 2, expression is wrong
	stack<int> numStack;
	stack<char> optStack;


	int sTOi(int firstindex, int lastindex);//transport expression to number
	string iTOs(int num);//translate number to string
	void changeMinus();//find '-' and judge if it means minus, if so, change it into '#'

	void pushINTOstack();
	void pushOPT(int index);//push the operation at index into optStack and calculate value if necessary

	void computeAB(char opt);//comput 'a opt b'

	void Error();//do when error occurs
	int cal();
public:
	Calculate();
	void start(string expression);
};
Calculate::Calculate()
{
	//this->expression = expression;
	//value = 0;
	error = 0;
	optPriority['('] = 0;
	optPriority['-'] = 1;
	optPriority['+'] = 1;
	optPriority['*'] = 2;
	optPriority['/'] = 2;
	optPriority['%'] = 2;
	optPriority['^'] = 3;
	optPriority['#'] = 4;
}
int Calculate::sTOi(int firstindex, int lastindex)
{
	string tmp = expression.substr(firstindex, lastindex - firstindex);
	int num_tmp = 0;
	for (int i = 0; i < (int)tmp.size(); i++)
	{
		num_tmp *= 10;
		num_tmp += tmp[i] - '0';
	}
	return num_tmp;
}
string Calculate::iTOs(int num)
{
	ostringstream s;
	s << num;
	string tmp = s.str();
	return tmp;
}
void Calculate::changeMinus()
{
	if (expression[0] == '-')
		expression[0] = '#';
	for (int i = 1; i < (int)expression.size(); ++i)
	{
		if (expression[i] == '-')
		{
			if (expression[i - 1] == ')')
				continue;
			if (expression[i - 1] >= '0' && expression[i - 1] <= '9')
				continue;
			expression[i] = '#';
		}
	}
	return;
}

void Calculate::computeAB(char opt)
{
	if (numStack.empty())//not enough number
	{
		if (!error)
			error = 2;
		return;
	}
	if (opt == '#')
	{
		int b = numStack.top();
		numStack.pop();
		numStack.push(-b);
		return;
	}



	int b = numStack.top();
	numStack.pop();
	if (numStack.empty())//not enough number
	{
		if (!error)
			error = 2;
		return;
	}
	int a = numStack.top();
	numStack.pop();
	int c = 0;
	double ad = a, bd = b;
	switch (opt)
	{
	case '-':c = a - b; break;
	case '+':c = a + b; break;
	case '*':c = a * b; break;
	case '%':c = a % b; break;
	case '/':
		if (b == 0)
		{
			if (!error)
				error = 1;//divided by 0
		}
		else
			c = a / b;
		break;
	case '^':
		if (b < 0)
		{
			if (!error)
				error = 2;
		}
		c = (int)pow(ad, bd);
		break;
	default:
		if (!error)
			error = 2;
		break;
	}
	numStack.push(c);
	return;
}

void Calculate::Error()
{
	if (error == 1)
	{
		cout << "Divide 0.\n";
	}
	else
	{
		cout << "error.\n";
	}
	return;
}

void Calculate::pushOPT(int index)
{
	char opt = expression[index];
	if (opt == '(' || opt == '#')
	{
		optStack.push(opt);
		return;
	}
	else
	{
		if (opt == ')')
		{
			int flag = 1;//mark expression is wrong for there is no '('
			while (!optStack.empty())
			{
				char opt_tmp = optStack.top();
				optStack.pop();
				if (opt_tmp == '(')
				{
					flag = 0;
					break;
				}
				computeAB(opt_tmp);
				if (error)
					return;
			}
			if (flag)//there is no '('
			{
				if (!error)
					error = 2;
				return;
			}
		}
		else
		{
			if (index)
			{
				if (expression[index - 1] == '(')
				{
					error = 2;
					return;
				}
			}
			while (!optStack.empty())
			{
				char opt_tmp = optStack.top();
				optStack.pop();
				if (optPriority[opt] >= optPriority[opt_tmp])
				{
					if (opt == '^')
					{
						optStack.push(opt_tmp);
						break;
					}
					else
					{
						if (optPriority[opt] > optPriority[opt_tmp])
						{
							optStack.push(opt_tmp);
							break;
						}
					}
				}
				computeAB(opt_tmp);
				if (error)
				{
					return;
				}
			}
			optStack.push(opt);
		}
	}
	return;
}
void Calculate::pushINTOstack()
{
	for (int i = 0; i < (int)expression.size(); ++i)
	{
		if (expression[i] >= '0' && expression[i] <= '9')
		{
			int j = i;
			for (; expression[j] >= '0' && expression[j] <= '9'; j++);
			numStack.push(sTOi(i, j));
			i = j - 1;
		}
		else
		{
			pushOPT(i);
		}
		if (error)
			return;
	}
	return;
}
int Calculate::cal()
{
	changeMinus();
	pushINTOstack();
	while (!optStack.empty())
	{
		if (error)
			break;
		char opt_tmp = optStack.top();
		optStack.pop();
		if (opt_tmp == '(')
		{
			if (!error)
				error = 2;
		}
		computeAB(opt_tmp);
	}
	if (numStack.size() != 1)
	{
		if (!error)
			error = 2;
	}

	if (error)
	{
		Error();
		return 0;
	}
	int value = numStack.top();
	while (!numStack.empty())
	{
		numStack.pop();
	}
	while (!optStack.empty())
	{
		optStack.pop();
	}
	return value;
}

void Calculate::start(string s)
{
	//��ѯ����
	if (s[0] == '?')
	{
		this->expression = s.substr(1);
		cout << expression << "=" << dict[expression] << endl;
		return;
	}

	int index = s.find_first_of('=');
	int flag = 1;//Ĭ�����Ǹ�ֵ����
	for (int i = index + 1; i < (int)s.size() && flag; ++i)
	{
		if (s[i] < '0' || s[i] > '9')
			flag = 0;
	}

	//��ֵ����
	if (flag)
	{
		this->expression = s;
		string tmp = s.substr(0, index);
		int value = sTOi(index + 1, (int)s.size());
		dict[tmp] = value;
		return;
	}

	//�������
	else
	{
		this->expression = "";
		string variable = s.substr(0, index);
		for (int i = index + 1; i < (int)s.size(); ++i)
		{
			int j = i;
			while (s[j] >= 'a' && s[j] <= 'z')
			{
				j++;
			}
			while (s[j] >= '0' && s[j] <= '9')
			{
				j++;
			}
			string tmp = s.substr(i, j - i);
			if (tmp[0] >= 'a' && tmp[0] <= 'z')
				this->expression += iTOs(dict[tmp]);
			else
				this->expression += tmp;
			if (j < (int)s.size())
				this->expression += s[j];
			i = j;
		}
		dict[variable] = cal();
	}
	return;
}
int main()
{
	string END("end");
	Calculate calculator;
	while (true)
	{
		string expression;
		while (true)
		{
			char tmp = getchar();
			if (tmp == '\n')
			{
				break;
			}
			if (tmp == ' ')
				continue;
			expression += tmp;
		}

		if (expression == END)
			break;
		calculator.start(expression);
	}
	return 0;
}