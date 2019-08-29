/*
在本实验中，需要同学们利用队列实现一个飞机场调度模拟，根据不同的输入参数得到不同的模拟结果。程序运行开始，首先需要输入以下参数：

机场跑道数，飞机降落占用跑道时间（整数）， 飞机起飞占用跑道时间（整数）

整个模拟的时间以分钟为单位，从 0 开始，每分钟的开始需要输入：

该分钟要求降落飞机数， 该分钟要求起飞飞机数

机场调度原则是降落优先起飞，在此原则下按来的顺序排队；每驾飞机都有一个编号，要起飞飞机从 1 开始，要降落飞机从 5001 开始；每驾飞机需要等待的时间是从其提要求开始到分配跑道为止；每个跑道都有一个编号（从 1 开始），都可以用来降落和起飞，但同一时间只能被一架飞机占用，占用时间为该飞机降落（起飞）占用跑道时间。

当输入的要求降落飞机数和要求起飞飞机数都小于 0 时，表示机场关闭，不再接受新的请求，但余下没有降落（起飞）的飞机需照常进行。

模拟过程中需要随时输出以下数据：

1. 当前时间 (%4d)

2. 所有从占用变为空闲的跑道编号 （在输入降落、起飞飞机数前输出）

3. 可以降落（起飞）飞机编号（％ 04d ）、跑道编号（％ 02d ） （在输入降落、起飞飞机数后输出）

模拟结束后，程序需输出以下统计结果：

1. 模拟时间（％ 4d ）

2. 降落平均等待时间（％ 4.1f ）

3. 起飞平均等待时间（％ 4.1f ）

4. 每条跑道被占用时间（％ 4d ）

5. 跑道平均被占用的百分比（％ 4.1f ， 平均占用时间× 100/ 模拟时间）
*/
#include <iostream>
#include <queue>

using namespace std;
const int MAXRUNWAYS = 100;
typedef struct
{
	int freeTime; //0 means free
	int busyTimeTotal;
} RunwayType;

typedef struct
{
	int airplaneID;
	int appearTime;
} ElementType;
int main()
{
	RunwayType runways[MAXRUNWAYS];
	queue<ElementType> arrivalQueue, departureQueue;
	int landWaitTimeTotal = 0;
	int takeoffWaitTimeTotal = 0;
	int busyTimeTotal = 0;
	int arrivalTotal = 0;
	int departureTotal = 0;
	int currentTime = 0;
	int landingTime, takeoffTime, numRunways;
	int i, numArrival, numDeparture;
	int finishFlag = 0, allRunwaysFree = 1;
	ElementType airplane;


	printf("Please input number of runways, landing time, takeoff time:\n");
	scanf("%d %d %d", &numRunways, &landingTime, &takeoffTime);
	for (i = 1; i <= numRunways; i++)
	{
		runways[i].freeTime = 0;
		runways[i].busyTimeTotal = 0;
	}
	printf("Current Time: %4d\n", currentTime);

	for (;;)
	{
		if (!finishFlag)
		{
			printf("Please input number of arrivals, number of departures required in next minute:\n");
			scanf("%d %d", &numArrival, &numDeparture);
			if ((numArrival < 0) && (numDeparture < 0))
				finishFlag = 1;
		}
		for (i = 0; i < numArrival; i++)
		{
			airplane.airplaneID = ++arrivalTotal + 5000;
			airplane.appearTime = currentTime;
			arrivalQueue.push(airplane);
		}
		for (i = 0; i < numDeparture; i++)
		{
			airplane.airplaneID = ++departureTotal;
			airplane.appearTime = currentTime;
			departureQueue.push(airplane);
		}
		for (i = 1; i <= numRunways; i++)
		{
			if (runways[i].freeTime == 0)
			{
				if (!arrivalQueue.empty())
				{
					airplane = arrivalQueue.front();
					arrivalQueue.pop();
					runways[i].freeTime = landingTime;
					runways[i].busyTimeTotal += landingTime;
					printf("airplane %04d is ready to land on runway %02d\n", airplane.airplaneID, i);
					landWaitTimeTotal += currentTime - airplane.appearTime;
				}
				else if (!departureQueue.empty())
				{
					airplane = departureQueue.front();
					departureQueue.pop();
					runways[i].freeTime = takeoffTime;
					runways[i].busyTimeTotal += takeoffTime;
					printf("airplane %04d is ready to takeoff on runway %02d\n", airplane.airplaneID, i);
					takeoffWaitTimeTotal += currentTime - airplane.appearTime;
				}
			}
		}
		currentTime++;
		printf("Current Time: %4d\n", currentTime);
		allRunwaysFree = 1;
		for (i = 1; i <= numRunways; i++)
			if (runways[i].freeTime)
			{
				runways[i].freeTime--;
				if (!runways[i].freeTime)
					printf("runway %02d is free\n", i);
				else
					allRunwaysFree = 0;
			}
		if (finishFlag && arrivalQueue.empty() && departureQueue.empty() && allRunwaysFree)
			break;
	}

	printf("simulation finished\n");
	printf("simulation time: %4d\n", currentTime);
	float avLandWaitTime = (float)landWaitTimeTotal / arrivalTotal;
	printf("average waiting time of landing: %4.1f\n", avLandWaitTime);
	float avTakeoffWaitTime = (float)takeoffWaitTimeTotal / departureTotal;
	printf("average waiting time of takeoff: %4.1f\n", avTakeoffWaitTime);
	for (i = 1; i <= numRunways; i++)
	{
		busyTimeTotal += runways[i].busyTimeTotal;
		printf("runway %02d busy time: %4d\n", i, runways[i].busyTimeTotal);
	}
	float busyPercentage = ((float)busyTimeTotal) / numRunways * 100 / currentTime;
	printf("runway average busy time percentage: %4.1f%%\n", busyPercentage);
	return 0;
}