#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "PacketQueue.h"

using namespace std;

//  JANKAT YASAR 26635 TAKEHOME 3



struct mainrouter
{
	PacketQueue queue;
	string routername;
	vector<string> connections;
	int size;
	mainrouter(){
	size = 0;
	}
};

int main()
{
	vector<string> routers; // contain router lines.

	string srouters,spackets;
	ifstream routerinput,packetinput;
	cout << "Please enter the name of the file for routers: ";
	cin >> srouters;
	cout << "Please enter the name of the file for packets: ";
	cin >> spackets;
	string line;
	int totalrouter = 0;
	routerinput.open(srouters.c_str());
	while (getline(routerinput,line))
	{
		if (line.find("-") != string::npos) // only adding the lines with the character "-" to not add the 11 in the beginning.
		{
			routers.push_back(line); // pushing back the lines of the router file
			totalrouter ++;
		}
	}
	routerinput.close();
	vector<mainrouter*> list;
	for (int j = 0; j < totalrouter; j++) // Create a 2d vector which contains an object for each character in router text.
	{
		string line = routers[j]; // routers line
		stringstream ss(line); // to get it word by word
		string word;
		mainrouter * router = new mainrouter();
		while (ss >> word)
		{

			if (line[0] == word[0])
			{
				router->routername = word;  // start of the line is the main router.
			}
			else if(word != "-")
			{
				router->connections.push_back(word); // after the starting line and without "-" other words are the connector routers.
			}									
		}
		list.push_back(router);
	}
	mainrouter * routerT = new mainrouter();  // there is no line for terminal in routers vector so we add it manually.
	routerT->routername = "T";
	list.push_back(routerT);
	PacketQueue * ptr = new PacketQueue(); // our temporary object pointer which will obtain all the packets.
	packetinput.open(spackets.c_str());
	while (getline(packetinput,line)) // enqueue all the packets to the E router first
	{
		Packet temp;
		for (int i = 0; i < line.size(); i++)
		{
			if (isdigit(line[i]) || isalpha(line[i]))  // for the extreme cases :D
			{
				temp.id += line[i];
			}
		}
		temp.routerHistory.push_back("E"); // all packets start with E router.		
		*ptr << temp;
		ptr->size ++;
	}
	packetinput.close();
	list[0]->queue = *ptr;  // assinging the queue with packets to first index of list, which is the router E.
	list[0]->size = ptr->size;

	for (int i = 0; i < list.size(); i++)
	{
		
		int index = 0;
		if (list[i]->connections.size() > 0)  // for every router
		{
			while(!list[i]->queue.isEmpty()) // until we reach the T, every router should empty itself and send packets.
			{
				int min = -1; // default min value for each time loop passes a packet.
				for (int c = 0; c < list[i]->connections.size(); c++) // this loop checks for the same name for all conector ruters, then picks the router
				{
					for (int r = 0; r < list.size(); r++)  // by the size, if sizes are same, it adds in order.
					{
						if (list[r]->routername == list[i]->connections[c])
						{
							if (min == -1)  // always assing the first index as min to compare with others.
							{
								index = r;
								min = list[r]->size;
							}
							else if (list[r]->size < min)  // if this queue's size is smaller than previus one, we save index to use it later in enqueue.
							{
								index = r;
								min = list[r]->size;
							}
							break;
						}
					}					
				}
					Packet packet; // object to get the packet out of queue.
					list[i]->queue >> packet;  // dequeue with function overload
					list[i]->size --;
					packet.routerHistory.push_back(list[index]->routername);  // we add the router history to the packet.
					list[index]->queue << packet;  // enqueue with function overload
					list[index]->size ++;	// size is for the sending packet order above.		 				
			}
		}
	}	
	cout << list[list.size()-1]->queue;	// printing with ostream overload. T is the last item in the list.
	for (int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}
	list.clear();
	return 0;
}