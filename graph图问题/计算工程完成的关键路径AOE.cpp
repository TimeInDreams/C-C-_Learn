/*
说明： AOE 网络是有向无环加权图，其中顶点表示事件，弧表示活动，权表示活动持续的时间，通常可以用来估算工程完成的时间，即图中从开始点到结束点之间最长的路径对应的时间。请完成一个程序，完成下列任务：

1 、计算 AOE 网络对应的拓扑排序。如果排序结果不唯一，请输出按照从小到大的顺序排列的结果。从小到大的顺序就是输入的节点序列顺序（参见下面关于输入格式的说明）。如图1中满足要求的拓扑排序是： a-b-c-d-e-f-g-h-k ,图2中满足要求的拓扑排序是：v1-v3-v5-v2-v6-v4-v7-v8-v9

2 、计算 AOE 网络的关键路径。注意关键路径可能不唯一，要求输出所有的关键路径。同样，按照是按照从小到大的顺序输出。例，如果得到两条关键路径，分别是0-1-3-6-8-9和0-1-3-4-5-8-9，那么先输出后一条路径，因为两条路径中前三个节点相同，而后一条路径第四个节点的编号小。

测试用例的输入输出格式说明：

输入：

节点的个数，边的条数；

各个节点的名称序列

边： < 起点 , 终点 , 权值 > 。说明起点和终点是在各个点在输入序列中的位置，如图1中边 <a,b> 表示为 <0,1,6> 。

输出：

拓扑排序；

关键路径

*/
#include <iostream>
#include <queue>
#include <string>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
using namespace std;
typedef struct Vet0
{
	string vet;
	int etime, ltime;//该事件发生的最早时间和最晚时间
	int d_in, d_out;//记录该顶点的入度和出度
	int known;//用于在输出关键路径时回溯
}Vertex;
typedef struct Adj0
{
	int vet_id;
	int weight;//这个是记录边的相关情况
	struct Adj0* next;
}Adjvet;
typedef struct Head0
{
	Adjvet* adjvet;
}Headvet;


const int N = 1e2;
const int INF = 1e5;
Vertex vertex[N];
Headvet headvet[N];
int path[N];//用于记录关键路径


void Get_vertexs(int amount_vet)
{
	string s;
	cin >> s;
	for (int i = 0; i < amount_vet; i++)
	{
		string tmp;
		int index = s.find_first_of(',');
		tmp.assign(s, 0, index);
		s.erase(0, index + 1);
		vertex[i].vet = tmp;
		vertex[i].etime = -INF;
		vertex[i].ltime = INF;
		vertex[i].d_in = 0;
		vertex[i].d_out = 0;
		vertex[i].known = 0;
		//cout << vertex[i].vet;
	}
	return;
}
void Enque(Headvet headvet, int pre_vet, int aft_vet, int vet, int weight)
{
	Adjvet* p = headvet.adjvet;
	//按照编号从小到大排列
	while (p && p->next && vet >= p->next->vet_id)
		p = p->next;
	Adjvet* tmp = p->next;
	p->next = new Adjvet;
	p->next->vet_id = vet;
	p->next->weight = weight;
	p->next->next = tmp;
	vertex[pre_vet].d_out++;
	vertex[aft_vet].d_in++;
	return;
}
void Get_sides(int amount_side)
{
	for (int i = 0; i < N; i++)
	{
		//初始化
		headvet[i].adjvet = new Adjvet;
		headvet[i].adjvet->next = NULL;
	}
	int pre_vet, aft_vet, weight;
	char c = 0;
	int sum = 0, sign = 1, flag = 1;
	c = getchar();//拿到输入顶点时残留的回车
	while ((c = getchar()) != '\n')
	{
		if (c == '<')
		{
			sum = 0;
			sign = 1;
			flag = 1;
		}
		else if (c == '-')
			sign = -1;
		else if (c >= '0'&& c <= '9')
		{
			sum = sum * 10 + c - '0';
		}
		else if (c == ',')
		{
			if (flag == 1)
			{
				pre_vet = sign * sum;
				sum = 0;
				sign = 1;
			}
			if (flag == 2)
			{
				aft_vet = sign * sum;
				sum = 0;
				sign = 1;
			}
			flag++;
		}
		else if (c == '>')
		{
			weight = sign * sum;
			sum = 0;
			sign = 1;
			Enque(headvet[pre_vet], pre_vet, aft_vet, aft_vet, weight);
		}
	}
	return;
}

int ToplogicalSort(int amount_vet)
{
	int *indegree = new int[amount_vet];
	priority_queue<int> inq;//用于过程,因为拓扑排序可能有多个，这个时候输出序号小的那个，这里借用了大顶堆，下面使用负数即可实现小顶堆
	queue<int> outq;//用于储存输出的信息
	for (int i = 0; i < amount_vet; i++)
	{
		indegree[i] = vertex[i].d_in;
		if (vertex[i].d_in == 0)
			inq.push(-i);//找到起始点，也即是入度为0的点
	}
	while (!inq.empty())
	{
		int index = -1 * (int)inq.top();
		inq.pop();
		outq.push(index);
		Adjvet* p = headvet[index].adjvet->next;
		while (p)
		{
			//以vertex[index]为前驱节点的所有节点的入度减去1
			indegree[p->vet_id]--;
			if (indegree[p->vet_id] == 0)
				inq.push(-1 * p->vet_id);
			p = p->next;
		}
	}
	if ((int)outq.size() != amount_vet)
	{
		cout << "NOTOPOLOGICALPATH\n";
		return 0;
	}
	else
	{
		while ((int)outq.size() != 1)
		{
			int index = outq.front();
			outq.pop();
			cout << vertex[index].vet << "-";
		}
		cout << vertex[outq.front()].vet << endl;
		return 1;
	}
}


int CalculateLtime(int vet_id)
{
	//dfs配合dp
	if (vertex[vet_id].ltime != INF)
		return vertex[vet_id].ltime;
	Adjvet* p = headvet[vet_id].adjvet->next;
	while (p)
	{
		//活动的最晚发生时间是从结束点到该点的最小路径
		vertex[vet_id].ltime = min(vertex[vet_id].ltime, CalculateLtime(p->vet_id) - p->weight);
		p = p->next;
	}
	return vertex[vet_id].ltime;
}
void CalculateVertexELtime(int amount_vet)
{
	vertex[0].etime = 0;
	for (int i = 0; i < amount_vet; i++)
	{
		Adjvet* p = headvet[i].adjvet->next;
		int pre_vet = i;
		while (p)
		{
			int aft_vet = p->vet_id;
			//活动的最早时间是从起始点到该点的最大路径
			vertex[aft_vet].etime = max(vertex[aft_vet].etime, vertex[pre_vet].etime + p->weight);
			p = p->next;
		}
	}
	vertex[amount_vet - 1].ltime = vertex[amount_vet - 1].etime;
	CalculateLtime(0);
	return;
}


void CPathPrint(int step)
{
	for (int i = 0; i < step; i++)
	{
		cout << vertex[path[i]].vet << "-";
	}
	cout << vertex[path[step]].vet << endl;
	return;
}
void CPath(int vet_id, int amount_vet, int step)
{
	/*本质上是dfs*/
	if (vet_id == amount_vet - 1)
	{
		//到达了结束位置，说明找到了这样的关键路径
		path[step] = vet_id;
		CPathPrint(step);
		vertex[vet_id].known = 0;
		return;
	}

	Adjvet* p = headvet[vet_id].adjvet;
	//对该顶点的每一个直接后继顶点进行深搜
	if (p)
		while (p->next)
		{
			int vet = p->next->vet_id;
			int weight = p->next->weight;
			if (vertex[vet].known || vertex[vet].etime != vertex[vet_id].ltime + weight || vertex[vet_id].etime != vertex[vet_id].ltime)
			{
				//剪枝
				p = p->next;
				continue;
			}
			path[step] = vet_id;
			vertex[vet].known = 1;//避免重复访问，事实上不会对同一个顶点进行重复访问，这里只是反映dfs的避免重复以及可回溯性
			CPath(vet, amount_vet, step + 1);
			p = p->next;
		}
	vertex[vet_id].known = 0;//用于回溯
	return;
}
void CriticalPath(int amount_vet)
{
	CalculateVertexELtime(amount_vet);
	/*因为要求输出所有的critical path，所以我们先将所有在关键路径上的顶点进行标记*/
	CPath(0, amount_vet, 0);
	return;
}
int main()
{
	int amount_vet, amount_side;
	char tmp;
	cin >> amount_vet >> tmp >> amount_side;
	//scanf_s("%d%*c%d%*c", &amount_vet, &amount_side);
	Get_vertexs(amount_vet);
	Get_sides(amount_side);
	if (ToplogicalSort(amount_vet))
		CriticalPath(amount_vet);
	return 0;
}