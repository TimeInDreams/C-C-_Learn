//#include "pch.h"
#include <iostream>
using namespace std;

class LINT
{
public:
	LINT();
	LINT(const LINT&);
	LINT(char *a, int lena, char SYM = '+');//从char数组实例化
	~LINT();

	void Print();//测试代码
	void getINT();//拿到int
	LINT Add(const LINT&); //Achieve the sum of two big numbers

private:
	static int SIZE;//m数组大小
	int LEN;//数值长度
	char *m;//存储值
	bool symbol;//标志正负,1正，0负


	void add(char* a, char* b, char *c, int lena, int lenb, int lenc);//c = a + b
	void minus(char* a, char* b, char *c, int lena, int lenb, int lenc);//c = a - b,符号相异的两个数相加
	void Set(char* a, int lena);//对char数组初始化为-1
	void Copy(char* a, char* b, int start_index_of_a = 0,
		int start_index_of_b = 0, int end_of_b = SIZE);//将b拷贝给a
	int Format(char*, int);//进行格式化处理，取消前导0，如将012转为12,00转为0,返回值为处理后长度
	//LINT Minus(const LINT*); //得到this减去another的值
};

int LINT::SIZE = 110;

LINT::LINT()
{
	LEN = 0;
	m = new char[SIZE];
	symbol = 1;
	Set(m, SIZE);
}
LINT::LINT(const LINT& another)
{
	LEN = another.LEN;
	m = new char[SIZE];
	symbol = another.symbol;
	Copy(m, another.m, 0, 0, LEN);
}
LINT::LINT(char *a, int lena, char SYM)
{
	m = new char[SIZE];
	symbol = !(SYM == '-');//SYM == ‘-’ 则symbol=0
	LEN = lena;
	Copy(m, a, 0, 0, LEN);
}

LINT::~LINT()
{
	delete[] m;
}

LINT LINT::Add(const LINT& input)
{
	LINT another = input;
	int lena = this->LEN;
	int lenb = another.LEN;
	int lenc = lena > lenb ? lena : lenb;
	lenc++;//增加一位借位
	bool SYM;//方便下面确定返回值LINT的正负
	char *c = new char[lenc];
	Set(c, lenc);


	if (this->symbol == another.symbol)//二者同号，直接相加
	{
		add(this->m, another.m, c, lena, lenb, lenc);
		SYM = this->symbol;
	}
	else
	{
		if (this->LEN > another.LEN)//this的绝对值大于another
		{
			minus(this->m, another.m, c, lena, lenb, lenc);
			SYM = this->symbol;//正负有this决定
		}
		else if (this->LEN == another.LEN)
		{
			bool flag = 0;//方便下面确认this和another的绝对值大小
			for (int i = 0; i < this->LEN; i++)
			{
				if (this->m[i] > another.m[i])//this绝对值较大
				{
					minus(this->m, another.m, c, lena, lenb, lenc);
					flag = 1;
					SYM = this->symbol;
					break;
				}
				else if (this->m[i] < another.m[i])//another绝对值较大
				{
					minus(another.m, this->m, c, lena, lenb, lenc);
					flag = 1;
					SYM = another.symbol;
					break;
				}
			}
			if (!flag)//二者相等
			{
				for (int i = 0; i < lenc; i++)
					c[i] = 0;
				lenc = 1;
				SYM = 1;//默认为+0
			}
		}
	}

	//对c进行格式化处理，取消前导0，如将012转为12,00转为0
	lenc = Format(c, lenc);

	LINT output(c, lenc);
	output.symbol = SYM;//确定正负
	//output.Print();
	return output;
}

void LINT::add(char* a, char* b, char *c, int lena, int lenb, int lenc)
{
	char carry = 0;//进位
	while (lena && lenb)
	{
		char tm = a[--lena] + b[--lenb] + carry;
		if (tm > 9)
		{
			carry = 1;
			tm -= 10;
		}
		else
			carry = 0;
		c[--lenc] = tm;
	}
	while (lena)
	{
		char tm = a[--lena] + carry;
		if (tm > 9)
		{
			carry = 1;
			tm -= 10;
		}
		else
			carry = 0;
		c[--lenc] = tm;
	}
	while (lenb)
	{
		char tm = b[--lenb] + carry;
		if (tm > 9)
		{
			carry = 1;
			tm -= 10;
		}
		else
			carry = 0;
		c[--lenc] = tm;
	}
	c[--lenc] = carry;
}

void LINT::minus(char* a, char* b, char *c, int lena, int lenb, int lenc)
{
	//由于确保了大数减去小数，则lena>=lenb
	char carry = 0;
	while (lenb)
	{
		char tm = a[--lena] - b[--lenb] - carry;
		if (tm < 0)
		{
			carry = 1;
			tm += 10;
		}
		else
			carry = 0;
		c[--lenc] = tm;
	}
	while (lena)
	{
		char tm = a[--lena] - carry;
		if (tm < 0)
		{
			carry = 1;
			tm += 10;
		}
		else
			carry = 0;
		c[--lenc] = tm;
	}
	c[--lenc] = carry;
}


void LINT::Set(char* a, int lena)
{
	for (int i = 0; i < lena; i++)
		a[i] = -1;
}

void LINT::getINT()
{
	int i = 0;
	char tmp = -1;
	tmp = getchar();
	if (tmp == '-')
		symbol = 0;//负数设置为0
	else
	{
		symbol = 1;
		if (tmp >= '0' && tmp <= '9')//防止出现'+'
		{
			m[i++] = tmp - '0';
		}
	}
	while (tmp = getchar())
	{
		if (tmp == '\n')
			break;
		m[i++] = tmp - '0';
	}
	LEN = i;
}

void LINT::Copy(char* a, char* b, int start_index_of_a,
	int start_index_of_b, int end_of_b)
{
	for (int i = start_index_of_a, j = start_index_of_b; j < end_of_b; i++, j++)
		a[i] = b[j];
}


int LINT::Format(char* a, int len)
{
	int i = 0;
	while (a[i] == 0 && i < len)//找到第一个不为0的位置
	{
		i++;
	}
	if (i == len)//若所有的值均为0则设置长度为1
	{
		a[0] = 0;
		len = 1;
	}
	else
	{
		char *b = new char[len];
		Copy(b, a, 0, 0, len);//把a完整拷贝给b
		Copy(a, b, 0, i, len);//取消前导0
		len -= i;
	}
	return len;
}

void LINT::Print()
{
	if (symbol == 0)
		cout << "-";
	for (int i = 0; i < LEN; i++)
		cout << (int)m[i];
	cout << endl;
}

int main()
{
	char a[20], b[20];
	for (int i = 1, j = 9; i < 10; i++, j--)
	{
		a[i - 1] = j;
		b[i - 1] = i;
	}
	LINT s1(a, 9), s2(b, 9,'-');
	s1.Print();
	s2.Print();
	(s1.Add(s2)).Print();


	LINT s3, s4;
	s3.getINT();
	s4.getINT();
	s3.Print();
	s4.Print();
	(s4.Add(s3)).Print();

	return 0;
}