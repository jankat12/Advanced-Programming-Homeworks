#include <iostream>
#include <string>

#include "linkedlist.h"

/* 
*******************************************************************************************************************

CS-204 JANKAT YASAR 26635  TAKEHOME EXAM 2

*******************************************************************************************************************
*/
using namespace std;

int main()
{
	node * head = NULL;
	linkedlist * list = new linkedlist();
	int menuoption = 0;
	cout << "Welcome to the Election Sheet." << endl;
	cout << "Please make a choice from the following menu: \n1. Enter votes,\n2. Remove votes,\n3. Display "
			"current standings (from best to worst),\n4. Display current standings (from worst to best),\n"
			"5. Finish." << endl << endl;
	while (menuoption != 5)
	{
		cin >> menuoption;
		if (menuoption == 1)
		{
			string s;
			cout << "\nPlease enter party name and votes to add: ";
			cin.ignore();
			getline(cin,s);
			string partyname = s.substr(0,s.find(" "));
			int votenum = stoi(s.substr(s.find(" ")+1,s.size()));
			head = list->EnterVotes(head,partyname,votenum);
			cout << endl;
		}
		else if (menuoption == 2)
		{
			string s;
			cout << "\nPlease enter party name and votes to remove: ";
			cin.ignore();
			getline(cin,s);
			string partyname = s.substr(0,s.find(" "));
			int votenum = stoi(s.substr(s.find(" ")+1,s.size()));
			head = list->RemoveVotes(head,partyname,votenum);
			cout << endl;
		}
		else if (menuoption == 3)
		{
			if (head == NULL)
			{
				cout << endl;
				cout << "There aren't any records." << endl << endl;
				cout << "Please make a choice from the following menu: \n1. Enter votes,\n2. Remove votes,\n3. Display "
			"current standings (from best to worst),\n4. Display current standings (from worst to best),\n"
			"5. Finish." << endl << endl;
				continue;
			}
			cout << endl;
			list->Displaybest(head);
			cout << endl;
		}
		else if (menuoption == 4)
		{
			if (head == NULL)
			{
				cout << endl;
				cout << "There aren't any records." << endl << endl;
				cout << "Please make a choice from the following menu: \n1. Enter votes,\n2. Remove votes,\n3. Display "
			"current standings (from best to worst),\n4. Display current standings (from worst to best),\n"
			"5. Finish." << endl << endl;
				continue;
			}
			cout << endl;
			list->Displayworst(head);
			cout << endl;
		}
		else if (menuoption == 5)
		{
			cout << "\nProgram exiting.." << endl;
			continue;
		}
		else
		{
			cout << "Please enter a valid option!" << endl << endl;
			continue;
		}
		cout << "Please make a choice from the following menu: \n1. Enter votes,\n2. Remove votes,\n3. Display "
			"current standings (from best to worst),\n4. Display current standings (from worst to best),\n"
			"5. Finish." << endl << endl;
	}
	return 0;
}