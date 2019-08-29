//https://www.geeksforgeeks.org/tiling-with-dominoes/
//https://en.wikipedia.org/wiki/Domino_tiling#CITEREFKasteleyn1961
/*
这里给出的覆盖3*n的板子
*/
#include <iostream>
using namespace std;
int result[50];
void slove()
{
    int temp[50];
    result[0] = 1, result[1] = 0;
    temp[0] = 0, temp[1] = 1;
    for (int i = 2; i < 50; i++)
    {
        result[i] = result[i-2] + temp[i-1] * 2;
        temp[i] = result[i-1] + temp[i-2];
    }
    
}
int main(int argc, char const *argv[])
{
    slove();
    while (true)
    {
        int n = 0;
        cin >> n;
        if(n == -1) break;
        cout << result[n] << endl;
    }
    
    return 0;
}
