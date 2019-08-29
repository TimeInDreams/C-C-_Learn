#include <iostream>
using namespace std;
typedef int ElementType;
class MINHEAP {
	int Capacity;
	int Size;
	ElementType *Elements;
	bool IsFull();
	bool IsEmpty();
	void PercolateDown(int index);
public:
	MINHEAP(int cap);
	void push(ElementType);
	ElementType front();
	void pop();
	void heapify();
};

MINHEAP::MINHEAP(int cap)
{
	this->Capacity = cap;
	this->Size = 0;
	this->Elements = new ElementType[cap + 1];
}

bool MINHEAP::IsFull()
{
	return this->Size == this->Capacity;
}

bool MINHEAP::IsEmpty()
{
	return this->Size == 0;
}

void MINHEAP::push(ElementType TmpElement)
{
	if (IsFull())
	{
		cout << "Heap is full." << endl;

	}
	this->Elements[++this->Size] = TmpElement;
}

ElementType MINHEAP::front()
{
	if (IsEmpty())
	{
		cout << "Heap is empty!\n";
		return INT16_MIN;
	}
	return this->Elements[1];
}

void MINHEAP::PercolateDown(int index)
{
	int i = index;
	ElementType FirstElement = Elements[index];
	int child = index;
	for (i = index; 2 * i <= Size; i = child)
	{
		child = i << 1;
		if (child + 1 <= Size && Elements[child] > Elements[child + 1])
			child++;
		if (FirstElement < Elements[child])
			break;
		else
			Elements[i] = Elements[child];
	}
	Elements[i] = FirstElement;
	return;
}

void MINHEAP::pop()
{
	if (IsEmpty())
	{
		cout << "Pop error! Heap is empty!\n";
	}
	Elements[1] = Elements[Size--];
	PercolateDown(1);
}

void MINHEAP::heapify()
{
	int index = Size >> 1;
	for (int i = Size >> 1; i > 0; --i)
	{
		PercolateDown(i);
	}
	return;
}

int main()
{
	MINHEAP heap(100);
	cout << "number of elements: \n";
	int NumOfElements = 0;
	cin >> NumOfElements;
	for (int i = 0; i < NumOfElements; ++i)
	{
		ElementType TmpElement;
		cin >> TmpElement;
		heap.push(TmpElement);
	}

	heap.heapify();

	for (int i = 0; i < NumOfElements; ++i)
	{
		cout << heap.front() << " ";
		heap.pop();
	}
	cout << endl;
	return 0;
}