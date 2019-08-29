//http://www.cppblog.com/menjitianya/archive/2015/11/19/212292.html
/*
http://poj.org/problem?id=3169
该问题可以转化为最短路径问题
like的好理解就是xj - xi <= n(j > i)
dislike就是xj - xi >= n ====> xi - xj <= -n  (j > i)
也就是说在最短路径问题中出现了负路径
最短哈密顿通路问题
注意题目中有一个隐含条件：xj - xi >= 0(j > i)

这个题目就是求存在负路径的最短路径问题
可以采用SPFA算法
*/
#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <cstring>
#include <climits>
#include <limits.h>
using namespace std;
const long long INF = (long long)1 << 60;
typedef pair<long long, long long> P;
bool operator<(P& a, P& b) //返回值为true表示 a 的优先级小于 b
{
	if (a.second == b.second)
		return a.first > b.first;
	return a.second > b.second;
}
class SPFA
{
private:
	list<P>* vertix;
	long long num_of_vertix;

public:
	SPFA(/* args */);
	SPFA(long long n);
	~SPFA();
	void addedge(long long from, long long to, long long weight);
	long long shortest_weight(long long source, long long goal);
};

SPFA::SPFA(/* args */)
{
	num_of_vertix = 0;
	vertix = NULL;
}
SPFA::SPFA(long long n)
{
	num_of_vertix = n;
	vertix = new list<P>[n + 1];
}
SPFA::~SPFA()
{
	if (vertix)
	{
		delete[] vertix;
		vertix = NULL;
	}
}
void SPFA::addedge(long long from, long long to, long long weight)
{
	vertix[from].push_back(P(to, weight));
}
long long SPFA::shortest_weight(long long source, long long goal)
{
	priority_queue<long long> q;

	bool flag = false;                            //声明是否存在负圈，假定不存在
	bool* inq = new bool[num_of_vertix + 1];      //判断节点i是否在队列中
	long long* d = new long long[num_of_vertix + 1];          //记录source到节点i的距离
	long long* visitCount = new long long[num_of_vertix + 1]; //对节点i访问次数
	for (long long i = 0; i < num_of_vertix + 1; i++)
	{
		d[i] = INF;
		visitCount[i] = 0;
		inq[i] = false;
	}
	inq[source] = true;
	q.push(source);
	d[source] = 0; //从source到source为0

	while (!q.empty())
	{
		long long from = q.top();
		q.pop();
		inq[from] = false;
		if (visitCount[from]++ > num_of_vertix) //访问次数超过这么多，说明存在负圈
		{
			flag = true;
			break;
		}
		//对每条边都进行检查
		for (list<P>::iterator iter = vertix[from].begin(); iter != vertix[from].end(); iter++)
		{
			long long to = (*iter).first;
			long long weight = (*iter).second;
			if (d[from] + weight < d[to])//进行松弛操作
			{
				d[to] = d[from] + weight;
				if (!inq[to])//不重复添加节点，重复添加无意义
				{
					inq[to] = true;
					q.push(to);
				}
			}
		}
	}

	delete[] inq;
	delete[] visitCount;
	if (flag) return -1;//存在负圈
	else if (d[goal] == INF) return -2;//不连通
	return d[goal];
	//return 0;
}


int main()
{
	long long n, ml, md;
	cin >> n >> ml >> md;
	SPFA s(n);
	for (long long i = 0; i < ml; i++)
	{
		long long from, to, weight;
		cin >> from >> to >> weight;
		if (from == to)
		{
			s.addedge(from, to, 0);
			s.addedge(to, from, 0);
		}
		else s.addedge(from, to, weight);
	}
	for (long long i = 0; i < md; i++)
	{
		long long from, to, weight;
		cin >> to >> from >> weight;
		if (from == to)
		{
			s.addedge(from, to, 0);
			s.addedge(to, from, 0);
		}
		else s.addedge(from, to, -weight);
	}
	cout << s.shortest_weight(1, n) << endl;
	return 0;
}
