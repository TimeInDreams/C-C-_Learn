#include <iostream>
#include <cstring>
#include <ctime>
#include <math.h>
#define MAXN 10000
#define TEAM_LEN 4
#define MAXSIZE 100
using namespace std;
class BigINT
{
  public:
	//constructor and destructor
	BigINT();
	BigINT(char *);
	BigINT(const BigINT &);
	BigINT(long long);
	BigINT &operator=(const BigINT &);
	~BigINT() {}

	//cin and cout
	friend istream &operator>>(istream &, BigINT &);
	friend ostream &operator<<(ostream &, const BigINT &);

	//+ - *
	bool operator>(const BigINT &) const;
	bool operator<(const BigINT &) const;
	bool operator==(const BigINT &) const;
	friend BigINT operator+(const BigINT &, const BigINT &);
	friend BigINT operator-(const BigINT &, const BigINT &);
	friend BigINT operator*(const BigINT &, const BigINT &);
	friend void POW10(BigINT &, int); //这里是进行移位操作，每向后移动一位，相当于*10^4
	friend BigINT multi(const BigINT &, const BigINT &);

  private:
	int a[MAXSIZE];
	int len;
	bool sign; //0正，1,负，默认为正

	void minus(const BigINT &, const BigINT &);
	void add(const BigINT &, const BigINT &);
	void char_TO_BigINT(char *, int);
	friend int ABSCompare(const BigINT &, const BigINT &); //比较二者绝对值大小
};
BigINT::BigINT()
{
	sign = 0;
	len = 0;
	memset(a, 0, sizeof a);
}
BigINT::BigINT(const BigINT &input)
{
	sign = input.sign;
	len = input.len;
	for (int i = 0; i < len; i++)
		a[i] = input.a[i];
	memset(a + len, 0, (MAXSIZE - len) * sizeof(int));
}
BigINT::BigINT(char *s)
{
	len = 0;
	memset(a, 0, sizeof a);
	sign = s[0] == '-';
	if (s[0] == '-' || s[0] == '+')
	{
		char_TO_BigINT(s, 1);
	}
	else
	{
		char_TO_BigINT(s, 0);
	}
}
BigINT::BigINT(long long in)
{
	sign = in < 0;
	memset(a, 0, sizeof a);
	if (in == 0)
		len = 1;
	else
		len = 0;

	in = abs(in);
	while (in >= MAXN)
	{
		//尽量避免取模运算
		long long tmp = in / MAXN;
		a[len++] = in - tmp * MAXN;
		in = tmp;
	}
	if (in)
		a[len++] = in;
}
BigINT &BigINT::operator=(const BigINT &in)
{
	sign = in.sign;
	len = in.len;
	//memset(a, 0, sizeof a);
	for (int i = 0; i < len; i++)
		a[i] = in.a[i];
	memset(a + len, 0, (MAXSIZE - len) * sizeof(int));
	return *this;
}
istream &operator>>(istream &in, BigINT &t)
{
	char s[2 * MAXSIZE];
	in >> s;
	t.len = 0;
	memset(t.a, 0, sizeof t.a);
	t.sign = s[0] == '-';

	int s_len = strlen(s);
	int team_no;
	if (s[0] == '-' || s[0] == '+')
	{
		t.char_TO_BigINT(s, 1);
	}
	else
	{
		t.char_TO_BigINT(s, 0);
	}
	return in;
}
ostream &operator<<(ostream &out, const BigINT &t)
{
	if (t.sign) //如果为负数
	{
		cout << "-";
	}
	//下面的顺序是为了防止出现前导零
	cout << t.a[t.len - 1];
	for (int i = t.len - 2; i >= 0; i--)
	{
		cout.width(TEAM_LEN);
		cout.fill('0');
		cout << t.a[i];
	}
	return out;
}
void BigINT::char_TO_BigINT(char *s, int start)
{
	int s_len = strlen(s);
	int team_no = (s_len - start) / TEAM_LEN; //TEAM_LEN位整数为一组
	len = team_no;							  //一共有多少组整数
	if ((s_len - start) > team_no * TEAM_LEN) //避免取模运算
		len++;

	int h = 0, i = s_len - 1;
	while (team_no--)
	{
		int sum = 0;
		for (int k = TEAM_LEN - 1; k >= 0; k--)
		{
			sum *= 10;
			sum += s[i - k] - '0';
		}
		i -= TEAM_LEN;
		a[h++] = sum;
	}
	if (h == len - 1)
	{
		for (i = 0; i < s_len - (len - 1) * TEAM_LEN; i++)
		{
			a[len - 1] *= 10;
			a[len - 1] += s[i] - '0';
		}
	}
}

bool BigINT::operator==(const BigINT &in) const
{
	return ABSCompare(*this,in);
}
bool BigINT::operator>(const BigINT &in) const
{
	if (this->sign == false) //this是正数
	{
		if (in.sign) //in为负数
			return true;
		return ABSCompare(*this,in) == 1; //二者同正
	}
	else
	{
		if (in.sign == 0) //this为负，in为正
			return false;
		return ABSCompare(*this,in) == -1; //二者同负
	}
}
bool BigINT::operator<(const BigINT &in) const
{
	if (this->sign == false) //this是正数
	{
		if (in.sign) //in为负数
			return false;
		return ABSCompare(*this,in) == -1; //二者同正
	}
	else
	{
		if (in.sign == 0) //this为负，in为正
			return true;
		return ABSCompare(*this,in) == 1; //二者同负
	}
}
int ABSCompare(const BigINT &in1, const BigINT &in2)
{
	if (in1.len > in2.len)
	{
		return 1;
	}
	if (in1.len < in2.len)
	{
		return -1;
	}
	for (int i = in1.len - 1; i >= 0; i--)
	{
		if (in1.a[i] > in2.a[i])
			return 1;
		if (in1.a[i] < in2.a[i])
			return -1;
	}
	return 0; //in1 == in2
}


BigINT operator+(const BigINT &in1, const BigINT &in2)
{
	BigINT out;
	if (in1.sign == in2.sign)
	{
		out.sign = in1.sign;
		out.add(in1, in2);
	}
	else
	{
		if (ABSCompare(in1,in2))
		{
			out.minus(in1, in2);
			out.sign = in1.sign;
		}
		else
		{
			out.minus(in2, in1);
			out.sign = in2.sign;
		}
	}
	return out;
}
void BigINT::add(const BigINT &in1, const BigINT &in2)
{
	len = in1.len > in2.len ? in1.len : in2.len;
	for (int i = 0; i < len; i++)
	{
		a[i] += in1.a[i] + in2.a[i];
		if (a[i] >= MAXN)
		{
			a[i] -= MAXN;
			a[i + 1] += 1;
		}
	}
	if (a[len])
		len++;
}
BigINT operator-(const BigINT &in1, const BigINT &in2)
{
	BigINT in2_tmp(in2);
	in2_tmp.sign ^= 1;
	return (in1 + in2_tmp);
	/*
	if (in1.sign == in2.sign)
	{
		if (BigINT(in1).ABSGreater(in2))
		{
			out.sign = in1.sign;
			out.minus(in1, in2);
		}
		else
		{
			out.minus(in2, in1);
			if (in1.sign)
			{
				out.sign = 0;
			}
			else
				out.sign = 1;
		}
	}
	else
	{
		out.add(in1, in2);
		out.sign = in1.sign;
	}

	return out;

	//*/
}
void BigINT::minus(const BigINT &in1, const BigINT &in2)
{
	len = in1.len;
	//memset(a, 0, sizeof a);
	for (int i = 0; i < len; i++)
	{
		a[i] += in1.a[i] - in2.a[i];
		if (a[i] < 0)
		{
			a[i] += MAXN;
			a[i + 1] -= 1;
		}
	}
	while (len > 1 && a[len - 1] == 0)
	{
		len--;
	}
	return;
}
BigINT operator*(const BigINT &X, const BigINT &Y)
{
	BigINT out;
	if (X.sign == Y.sign)
		out.sign = 0;
	else
		out.sign = 1;

	if (X.len > Y.len)
		out = multi(X, Y);
	else
		out = multi(Y, X);
	return out;
}
BigINT multi(const BigINT &x, const BigINT &y)
{
	if (x.len == 1)
	{
		return BigINT(x.a[0] * y.a[0]);
	}
	//下面进行拆分
	BigINT A, B, C, D;
	for (int i = 0; i < x.len / 2; i++) //后半段
	{
		B.a[i] = x.a[i];
		D.a[i] = y.a[i];
	}
	for (int i = x.len / 2; i < x.len; i++) //x前半段
	{
		A.a[i - x.len / 2] = x.a[i];
	}
	for (int i = x.len / 2; i < y.len; i++) //y前半段
	{
		C.a[i - x.len / 2] = y.a[i];
	}
	B.len = D.len = x.len / 2;
	A.len = C.len = x.len - B.len;

	//分治递归
	BigINT AC = A * C;
	BigINT BD = B * D;
	BigINT TMP = (A + B) * (C + D) - AC - BD;
	int n = (x.len - x.len / 2);
	POW10(AC, 2 * n);
	POW10(TMP, n);
	return (AC + TMP + BD);
}
void POW10(BigINT &x, int n)
{
	for (int i = x.len - 1; i >= 0; i--)
	{
		x.a[i + n] = x.a[i];
	}
	memset(x.a, 0, n * (sizeof(int)));
	x.len += n;
	return;
}

int main()
{
	//*
	//这是测试代码
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		//*
		long long aa = rand(), bb = -rand();
		BigINT a(aa), b(bb);
		//if( (a+b) > (aa+bb) || (a+b) < (aa+bb))
		//if ((a*b) > (aa*bb) || (a*b) < (aa*bb))
		//{
		cout << "a:" << a << endl;
		cout << "b:" << b << endl;
		//cout << "a+b:\n" << a + b << "\n" << aa + bb << endl;
		//cout << "a-b:\n" << a - b << "\n" << aa - bb << endl;
		cout << "a*b:\n"
			 << a * b << "\n"
			 << aa * bb << endl;
		cout << endl;
		//}
		//*/

		/*
		//用于手动输入测试特殊用例
		BigINT a, b;
		cin >> a >> b;
		cout << "a:" << a << endl;
		cout << "b:" << b << endl;
		//cout << "a+b:\n" << a + b << "\n" << endl;
		//cout << "a-b:\n" << a - b << "\n" << endl;
		cout << "a*b:\n" << a * b << "\n" << endl;
		cout << "\n\n\n\n\n\n\n\n" << endl;
		//*/
	}
	//*/

	/*
	BigINT a, b;
	cin >> a >> b;
	cout << a * b << endl;
	//*/
	return 0;
}