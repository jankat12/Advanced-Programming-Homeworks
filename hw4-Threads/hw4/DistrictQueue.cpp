#include "DistrictQueue.h"
#include <iostream>
using namespace std;

template <class itemtype>
DistrictQueue<itemtype>::DistrictQueue()
{
	front = NULL;
	rear = NULL;
}

template <class itemtype>
DistrictQueue<itemtype>::~DistrictQueue()
{
	clear();
}

template <class itemtype>
void DistrictQueue<itemtype>:: enqueue(itemtype item)
{
	if (isEmpty())  //if the queue is empty
	{
		front = new DistrictNode<itemtype>(item);
		rear = front;
	}
	else
	{
		rear->next = new DistrictNode<itemtype>(item);
		rear = rear->next;
	}
}

template <class itemtype>
void DistrictQueue<itemtype>:: dequeue(itemtype & item){
	DistrictNode<itemtype> * temp;
	if (!isEmpty())
	{
		item = front->info;
		temp = front;
		front = front->next;
		delete temp;
	}
}

template <class itemtype>
bool DistrictQueue<itemtype>::isEmpty(void) const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

template <class itemtype>
void DistrictQueue<itemtype>::clear(void)
{
	itemtype temp; // dummy for dequeue
	while (!isEmpty())
	{
		dequeue(temp);
	}
}