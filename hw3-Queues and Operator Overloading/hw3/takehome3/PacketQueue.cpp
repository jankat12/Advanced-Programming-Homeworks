#include <iostream>
#include "PacketQueue.h"

using namespace std;

PacketQueue::PacketQueue(void) // ctor
{
	front = NULL;
	rear = NULL;
	size = 0;
}

//PacketQueue::PacketQueue(const PacketQueue & copy)
//{
//	rear = copy.createClone();
//	QueueNode * ptr = rear;
//	while (ptr->next != NULL)
//	{
//		ptr = ptr->next;
//	}
//	front = ptr;
//	size = 0;
//}

PacketQueue::~PacketQueue() // destructor
{
	Packet packet; // dummy packet to destroy.
	while (!isEmpty())
	{
		*this >> packet;
	}
}

//void PacketQueue::dequeue(Packet & packet)
//{
//	if (!isEmpty())
//	{
//		QueueNode * temp;
//		packet = front->value;
//		temp = front;
//		front = front->next;
//		size--;
//		delete temp;
//	}
//}

bool PacketQueue::isEmpty(void) const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//void PacketQueue::clear(void)
//{
//	Packet packet;
//	while (isEmpty())
//	{
//		*this >> packet;
//	}
//}

//QueueNode * PacketQueue::createFront (void) const
//{
//	if (front  == NULL)
//	{
//		return NULL;
//	}
//
//}
//
//QueueNode * PacketQueue::createClone (void) const
//{
//	if (rear == NULL)
//	{
//		return NULL;
//	}
//	QueueNode * rearclone = new QueueNode();
//	rearclone->value = rear->value;
//	QueueNode * ptr = rear->next;
//	QueueNode * ptrclone = rearclone;
//	while (ptr != NULL)
//	{
//		ptrclone->next = new QueueNode();
//		ptrclone->next->value = ptr->value;
//		ptr = ptr->next;
//		ptrclone = ptrclone->next;
//	}
//	return rearclone;
//}

const PacketQueue & PacketQueue:: operator << (const Packet & rhs)
{
	if (isEmpty())
	{   //if the queue is empty
		//make it the first element
		front = new QueueNode();
		front->value = rhs;
		rear = front;
	}
    else
	{  //if the queue is not empty
		//add it after rear
		rear->next = new QueueNode();
		rear->next->value = rhs;
		rear = rear->next;
	} 
	//size ++;
	return *this;
}

const PacketQueue & PacketQueue:: operator >> ( Packet & rhs)
{
	if (!isEmpty())
	{
		QueueNode * temp;
		rhs = front->value;
		temp = front;
		front = front->next;
		//size--;
		delete temp;
	}
	return *this;
}

ostream & operator << (ostream & os, PacketQueue & que)
{
	
	cout << "Packets are displayed in the order they arrive in the terminal router, along with their router visit history:\n";
	while (!que.isEmpty())
	{
		Packet packet;
		que >> packet;
		cout << packet.id + ":";
		for (int i = 0; i < packet.routerHistory.size(); i++)
		{
			if (i == packet.routerHistory.size()-1)
			{
				cout <<" "<<packet.routerHistory[i] << endl;
			}
			else
			{
				cout <<" "<<packet.routerHistory[i] <<",";
			}			
		}
	}
	return os;
}