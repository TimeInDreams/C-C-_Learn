/*
题意：给出n条线段，以米的单位给出，小数点后两位（精确到厘米），
要你对这些线段裁剪，裁剪出m条等长的线段，
并且让这些线段尽可能长另外线段的长度不能小于1厘米，如果筹不够m条，输出0.00 
下面是浮点数代码写法
 N (1 = N = 10000) and K (1 = K = 10000) 
 N块线段，要求分成K份
*/

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
const double esp = 1e-8;
int N, K;
double a[100100];
double max_len = 0;

bool OK(double mid)
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        cnt += (int)(a[i] / mid);
    }
    return cnt >= K;
}

int main(int argc, char const *argv[])
{

    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        if (max_len < a[i])
            max_len = a[i];
    }
    double l = 0, r = max_len;
    while (true)
        if (fabs(r - l) < esp)
        {
            //cout << fixed << setprecision(2) << r << endl;
            //int result = r * 100;
            //printf("%d.%02d\n", result / 100, result % 100);
            printf("%0.2lf\n",(floor(r*100))/100);//向下取整
            break;
        }
        else
        {
            double mid = (r + l) / 2.0;
            if (OK(mid))
                l = mid;
            else
                r = mid;
        }

    return 0;
}