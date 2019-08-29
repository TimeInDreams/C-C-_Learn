//这种方法得到的并查集不可撤销
int par[MAX_N];//父亲结点
int height[MAX_N];//树高
//初始化
void init()
{
    for ( int i = 0; i < n; i++ ){
        par[i] = i;
        height[i] = 0;
    }
    return;
}
//查询树的根，若具有相同的根，则在同一个树上
//返回值是父亲结点的值
int fnd(int x)
{
    if ( par[x] == x ) return x;
    else return par[x] = fnd(par[x]);
}
//合并x,y所在的集合
void union(int x, int y)
{
    x = fnd(x);
    y = fnd(y);
    if ( x == y ) return;
    if ( height[x] < height[y] ){
        par[x] = y;
    }
    else{
        par[y] = x;
        if ( height[x] == height[y] )
            height[x]++;
    }
    return;
}


