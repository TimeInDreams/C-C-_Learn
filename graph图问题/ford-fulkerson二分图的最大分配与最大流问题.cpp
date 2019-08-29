/*
算法流程框架：
https://www.jianshu.com/p/efb2d79e2b0f
如何找增广路径，最大流与最小割的关系：
https://blog.csdn.net/weixin_43843835/article/details/88430362
persudo:
for each edge(u,v) in E(G) do:
    f(u,v) = 0
    f(v,u) = 0

//当存在增广路径的时候
while exists a path p from s to t in the residual network Gf:
    cf(p) = min{cf(u,v):(u,v) in p}
    for each edge(u,v) in p:
        f(u,v) = f(u,v) + cf(p)
        f(v,u) = -f(u,v)
        cf(u,v) -= cf(p)

//关于增广路径的求法
要理解如何求增广路径，就要理解如何最大流与最小割的关系
增广路径不存在，意味着找到了最小割集，最小割的流就是最大流
那么找增广路径就转化为了找最小割集
此时只需要动用dfs找到一个从源到汇的路径即可
dfs算法
dfs(Path &path, Graph &Gf, Point p)
{
    if p == t:
        path.push(p)
        return true
    
    path.push(p)
    for each next_point of p:
        if dfs(path,Gf,next_point):
            return true
    path.pop()
    return false
}

其他算法：
Edmonds-Krap以及Dinic算法
https://www.cnblogs.com/gtarcoder/p/4884117.html
*/