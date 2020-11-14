#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <mutex>
#include "DistrictQueue.h"
#include "strutils.h"

using namespace std;
// JANKAT YASAR 26635 TAKEHOME EXAM 4

mutex myMutex,coutMutex,pushMutex,finalMutex;


DistrictQueue<District> storage;
DistrictQueue<DistrictData> results;

void Display(DistrictQueue<DistrictData> & queue){
	DistrictData temp1,temp2,temp3;
	DistrictData dummy;
	while (!queue.isEmpty())
	{
		queue.dequeue(dummy);
		if (temp1.value == 0) // 0 is for first time
		{
			temp1 = dummy;
		}
		else if (temp2.value == 0)
		{
			temp2 = dummy;
		}
		else if (temp3.value == 0)
		{
			temp3 = dummy;
		}
		else if (dummy.value <= temp1.value)
		{
			temp3 = temp2;
			temp2 = temp1;
			temp1 = dummy;
		}
		else if (dummy.value <= temp2.value)
		{
			temp3 = temp2;
			temp2 = dummy;
		}
		else if (dummy.value <= temp3.value)
		{
			temp3 = dummy;
		}
	}
	int avgmedprice = (temp1.dist.medianPrice + temp2.dist.medianPrice + temp3.dist.medianPrice) / 3;
	cout << "\nClosest District 1\n--------\nId: " << temp1.dist.id << "\nMedian Price: " << temp1.dist.medianPrice << "\nCalculated Dissimilarity"
		" Metric: " << temp1.value << endl << endl << "Closest District 2\n--------\nId: " << temp2.dist.id << "\nMedian Price: " << temp2.dist.medianPrice << 
		"\nCalculated Dissimilarity Metric: " << temp2.value << endl << endl << "Closest District 3\n--------\nId: " << temp3.dist.id << "\nMedian Price: " 
		<< temp3.dist.medianPrice << "\nCalculated Dissimilarity Metric: " << temp3.value << endl << endl << "Average median price of three closest districts: "
		<< avgmedprice << endl;
}

void Dissimilarity(double age,double avgroom, double avgbroom, double latit,double longi)
{
	District dist1,dist2,dist3;  // we re gonna take 3 districts in the end.
	double min1,min2,min3;  // 3 metric values going to be with them in a struct, so we can compare them later.
	int counter = 0;
	min1 = -1; // giving them a default value;
	min2 = -1;
	min3 = -1;
	myMutex.lock();  // lock to make threads reach storage one by one
	while (!storage.isEmpty())
	{
		counter ++; //count for cout every 1000th value.
		District district;  // dummy district to take value from dequeue
		
		storage.dequeue(district);
		myMutex.unlock();
		if (counter % 1000 == 0)
		{
			coutMutex.lock();
			cout << "Thread with id " << this_thread::get_id() << " is processing its " << counter << "th item." << endl;
			coutMutex.unlock();
		}
		double agediff = district.medianAge - age;  // basically taking their difference and its absolute values with the statements.
		if (agediff < 0) 
		{
			agediff = -(agediff);
		}
		double roomdiff = district.AverageRooms - avgroom;
		if (roomdiff < 0)
		{
			roomdiff = -(roomdiff);
		}
		double broomdiff = district.AverageBedrooms - avgbroom;
		if (broomdiff < 0)
		{
			broomdiff = -(broomdiff);
		}
		double latitudediff = district.Latitude - latit;
		if (latitudediff < 0)
		{
			latitudediff = -(latitudediff);
		}
		double longitudediff = district.Longitude - longi;
		if (longitudediff < 0)
		{
			longitudediff = -(longitudediff);
		}
		double metric = (agediff/26)*(agediff/26) + (roomdiff/10)*(roomdiff/10) + (broomdiff/4)*(broomdiff/4) + latitudediff*latitudediff  // formula
			+ longitudediff*longitudediff;
		metric = sqrt(metric);  // taking square root
		if (min1 == -1) // for the first time thread reads an element
		{
			min1 = metric;
			dist1 = district;
		}
		else if (min2 == -1)  // for the second time thread reads an element
		{
			if (metric <= min1)
			{
				min2 = min1;
				min1 = metric;
				dist2 = dist1;
				dist1 = district;
			}
			else
			{
				min2 = metric;
				dist2 = district;
			}
		}
		else if (min3 == -1)  // for the third time thread reads an element
		{
			if (metric <= min1)
			{
				min3 = min2;
				min2 = min1;
				min1 = metric;
				dist3 = dist2;
				dist2 = dist1;
				dist1 = district;
			}
			else if (metric <= min2)
			{
				min3 = min2;
				min2 = metric;
				dist3 = dist2;
				dist2 = district;
			}
			else
			{
				min3 = metric;
				dist3 = district;
			}
		}
		else  // if there is already 3 districts assigned in the thread stack, then compare other dequeued districts.
		{
			if (metric <= min1)
			{
				min3 = min2;
				min2 = min1;
				min1 = metric;
				dist3 = dist2;
				dist2 = dist1;
				dist1 = district;
			}
			else if (metric <= min2)
			{
				min3 = min2;
				min2 = metric;
				dist3 = dist2;
				dist2 = district;
			}
			else if (metric <= min3)
			{
				min3 = metric;
				dist3 = district;
			}
		}
		myMutex.lock();  // lock again for while loop
	}
	myMutex.unlock(); // unlock here for when while loop ends.
	DistrictData data1;
	data1.dist = dist1;
	data1.value = min1;
	DistrictData data2;
	data2.dist = dist2;
	data2.value = min2;
	DistrictData data3;
	data3.dist = dist3;
	data3.value = min3;
	pushMutex.lock(); // lock here to make sure that threads push their values seperately.
	results.enqueue(data1);
	results.enqueue(data2);
	results.enqueue(data3);
	pushMutex.unlock();
	finalMutex.lock();
	this_thread::sleep_for(chrono::milliseconds(200));  // to make sure exit messages get out lastly.
	cout << "Thread with id " << this_thread::get_id() << " is exiting." << endl; 
	finalMutex.unlock();
}

int main()
{
	ifstream input("data.tsv");
	string line;
	while (getline(input,line))
	{
		if (!isdigit(line[0]))
		{
			continue;
		}
		stringstream ss(line);
		string word;
		int ctr = 0;
		District district;
		while (getline(ss,word,'\t'))  // get it word by word and parse when it sees \t
		{
			ctr ++;  // we keep the index for each word to match them accordingly.
			if (ctr == 1)
			{
				int temp = atoi(word);
				district.id = temp;
			}
			else if (ctr == 2)
			{
				int temp = atoi(word);
				district.medianAge = temp;
			}
			else if (ctr == 3)
			{
				double temp = atof(word);
				district.AverageRooms = temp;
			}
			else if (ctr == 4)
			{
				double temp = atof(word);
				district.AverageBedrooms = temp;
			}
			else if (ctr == 5)
			{
				double temp = atof(word);
				district.Latitude = temp;
			}
			else if (ctr == 6)
			{
				double temp = atof(word);
				district.Longitude = temp;
			}
			else if (ctr == 7)
			{
				int temp = atoi(word);
				district.medianPrice = temp;
				storage.enqueue(district);
			}			
		}
	}
	input.close();
	cout << "20640 districts have been loaded." << endl;

	int threadnum,houseage,roomnum,bedroomnum;
	double latitudenum,longitudenum;
	cout << "How many threads?: ";
	cin >> threadnum;

	cout << "\nWhat is the age of the house?: ";
	cin >> houseage;
	cout << "How many rooms does the house have?: ";
	cin >> roomnum;
	cout << "How many bedrooms does the house have?: ";
	cin >> bedroomnum;
	cout << "What is the latitude of the house?: ";
	cin >> latitudenum;
	cout << "What is the longitude of the house?: ";
	cin >> longitudenum;
	cout << endl;

	thread * arr = new thread[threadnum];  // dynamic array iin order to push threads according to the user input.
	for (int i = 0; i < threadnum; i++)
	{
		arr[i] = thread(Dissimilarity,houseage,roomnum,bedroomnum,latitudenum,longitudenum);
	}
	for (int i = 0; i < threadnum; i++)
	{
		arr[i].join();
	}
	Display(results);
	delete[] arr;
	return 0;
}