/***** 
* 
*算 24点（包括小数） 
*输出计算过程 
* 
*****/
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
using namespace std;
const double PRECISION = 1E-6;
const int COUNT_OF_NUMBER = 4;
const int NUMBER_TO_BE_CAL = 24;
double number[COUNT_OF_NUMBER];
string expression[COUNT_OF_NUMBER];
bool Search(int n)
{
    /*n==1表示一次计算结束，number[0]中即为计算的结果*/
    if (n == 1)
    {
        if (fabs(number[0] - NUMBER_TO_BE_CAL) < PRECISION)
        { /*expression[0]中保存了求解过程*/
            return true;
        }
        else
        {
            return false;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double a, b;
            string expa, expb;
            a = number[i];
            b = number[j];
            /********************************** 
                     *将剩下的有效数字往前挪， 
                     *由于两数计算结果保存在number[i]中， 
                     *所以将数组末元素覆盖number[j]即可 
                     **********************************/
            number[j] = number[n - 1];
            expa = expression[i];
            expb = expression[j];
            expression[j] = expression[n - 1];
            /*计算a+b*/
            expression[i] = '(' + expa + '+' + expb + ')';
            number[i] = a + b;
            if (Search(n - 1))
                return true;
            /*计算a-b*/
            expression[i] = '(' + expa + '-' + expb + ')';
            number[i] = a - b;
            if (Search(n - 1))
                return true;
            /*计算b-a*/
            expression[i] = '(' + expb + '-' + expa + ')';
            number[i] = b - a;
            if (Search(n - 1))
                return true;
            /*计算(a*b)*/
            expression[i] = '(' + expa + '*' + expb + ')';
            number[i] = a * b;
            if (Search(n - 1))
                return true;
            /*计算(a/b)*/
            if (b != 0)
            {
                expression[i] = '(' + expa + '/' + expb + ')';
                number[i] = a / b;
                if (Search(n - 1))
                    return true;
            }
            /*计算(b/a)*/
            if (a != 0)
            {
                expression[i] = '(' + expb + '/' + expa + ')';
                number[i] = b / a;
                if (Search(n - 1))
                    return true;
            }
            /*恢复现场*/
            number[i] = a;
            number[j] = b;
            expression[i] = expa;
            expression[j] = expb;
        }
    }
    return false;
}
int main()
{
    for (int i = 0; i < COUNT_OF_NUMBER; i++)
    {
        char buffer[20];
        memset(buffer, 0, sizeof(char));
        int x;
        cin >> x;
        number[i] = x;
        string buffer_tmp = to_string(x);
        for (int h = 0; h < buffer_tmp.length(); h++)
            buffer[h] = buffer_tmp[h];
        expression[i] = buffer;
    }
    if (Search(COUNT_OF_NUMBER))
    {
        cout << "Success" << endl;
        cout << expression[0] << endl;
    }
    else
    {
        cout << "Fail" << endl;
    }
    return 0;
}