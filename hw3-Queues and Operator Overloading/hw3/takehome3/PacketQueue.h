#ifndef PACKETQUEUE_H
#define PACKETQUEUE_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Packet{
	string id;
	vector<string> routerHistory;
};
struct QueueNode{
	Packet value;
	QueueNode * next;
	QueueNode(){
		next = NULL;
	}
};

class PacketQueue{
private:
	QueueNode * front;
	QueueNode * rear;
public:
	int size;
	PacketQueue(void);
	/*PacketQueue(const PacketQueue &);*/
	~PacketQueue();
	bool isEmpty(void) const;
	void clear(void);
	const PacketQueue & operator << (const Packet & rhs);
	const PacketQueue & operator >> (Packet & rhs);
	friend ostream & operator << (ostream & os, PacketQueue & rhs);
};
#endif