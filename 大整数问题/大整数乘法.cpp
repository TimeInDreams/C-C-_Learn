/*

大整数乘法有很多降低复杂度的算法：其中快速傅里叶变换也可以
这里的算法复杂度仍然是O(N^2)
算法是：
依据小学竖式计算

*/
#include <iostream>
#include <cstring>
using namespace std;
const int SIZE = 20020;
//这里是把大整数转换成数组进行存储
int getINT(int *m)
{
    int i = 0;
    int tmp;
    while (tmp = getchar())
    {
        if (tmp == '\n')
            break;
        m[i++] = tmp - '0';
    }
    return i;
}

void multiplication(int *x, int *y, int lenx, int leny)
{
    int lenz = lenx + leny;
    int *z = new int[lenz];
    for (int i = 0; i < lenz; i++)
        z[i] = 0;

    //乘法计算
    for (int i = lenx - 1; i >= 0; i--)
    {
        for (int j = leny - 1; j >= 0; j--)
        {
            z[i + j + 1] += x[i] * y[j];
        }
    }

    //format，得到最终结果
    for (int i = lenz - 1; i > 0; i--)
    {
        z[i - 1] += z[i] / 10;
        z[i] %= 10;
    }

    int i = 0;
    while (z[i] == 0)
    {
        i++;
    }

    for (; i < lenz; i++)
    {
        cout << (int)z[i];
    }
    cout << endl;
    //return z;
}

int main(int argc, char const *argv[])
{
    int a[SIZE], b[SIZE];
    int lena = getINT(a);
    int lenb = getINT(b);
    multiplication(a, b, lena, lenb);
    //cin.ignore();
    return 0;
}
