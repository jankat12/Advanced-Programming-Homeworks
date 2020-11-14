#ifndef DISTRICTQUEUE_H
#define DISTRICTQUEUE_H
#include <iostream>

using namespace std;

struct District {
	int id;
	int medianAge;
	double AverageRooms;
	double AverageBedrooms;
	double Latitude;
	double Longitude;
	int medianPrice;
};
struct DistrictData{  // to keep districts and dissimilarity values at the same time, to compare them easily later.
	District dist;
	double value;
	DistrictData(){
	dist;
	value = 0;
	}
};

template <class itemtype>
struct DistrictNode {
	itemtype info;
	DistrictNode * next;
	DistrictNode(itemtype x){
		info = x;
		next = NULL;
	}
};

template <class itemtype>
class DistrictQueue{
private:
	DistrictNode<itemtype> * front;
	DistrictNode<itemtype> * rear;
public:
	DistrictQueue();
	~DistrictQueue();
	void enqueue(itemtype);
	void dequeue(itemtype &);
	bool isEmpty(void) const;
	void clear(void);
};

#include "DistrictQueue.cpp"
#endif 