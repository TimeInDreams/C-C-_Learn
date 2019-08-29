/*
背景：
我们的教材中已经介绍了表达式求值的算法，现在我们将该算法的功能进行扩展，要求可以处理的运算符包括：+、-、*、/、%（整数取余）、^（乘方）、（、）。

要求：
采用算符优先算法，计算的中间结果只保留整数。

输入：
第一行为整数N。表示下面有N个表达式

从第二行起的后面N行为N个由整数构成的表达式

输出：
共N行，每行为相应表达式的计算结果。

如果判断出表达式有错误，则输出：error.

如果在计算过程中出现除数为0的情况，则输出：Divide 0.

特殊情况说明：

在表达式中，如果操作数出现负数（例如-8），则要特别注意。例如：
10加-8表示为：10+-8。
10减-8表示为：10--8。


思路：
	入栈规则：
		1.左括号直接入栈
		2.右括号入栈前，逐次弹出所有操作符并进行运算直到左括号
		3.‘-’的处理：
			1.若‘-’前面为数字或者右括号则‘-’为减号
			2.其他情况都是负号，并用"#"代替，是一元算子
		4.四层优先级(-,+),(*,/),(^)(#)
//*/
#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <map>
using namespace std;
class Calculate {
	map<char, int> optPriority;
	string expression;
	//int value;
	int error;//error == 1, divided by 0; error == 2, expression is wrong
	stack<int> numStack;
	stack<char> optStack;


	int sTOi(int firstindex, int lastindex);//transport expression to number
	void changeMinus();//find '-' and judge if it means minus, if so, change it into '#'

	void pushINTOstack();
	void pushOPT(int index);//push the operation at index into optStack and calculate value if necessary

	void computeAB(char opt);//comput 'a opt b'

	void Error();//do when error occurs
public:
	Calculate(string expression);
	void cal();//calculate the final value and print it.
};
Calculate::Calculate(string expression)
{
	this->expression = expression;
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
					//这一步是考虑到指数运算和四则运算在进行同级运算时的不同之处
					//四则运算同级别从左往右
					//指数运算是从上到下，也即是表达式中的从右往左
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
void Calculate::cal()
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
		return;
	}
	cout << numStack.top() << endl;
	return;
}
int main()
{
	int N = 0;//NO. of expressions
	cin >> N;
	while (N--)
	{
		string expression;
		cin >> expression;
		Calculate calculator(expression);
		calculator.cal();
	}
	return 0;
}