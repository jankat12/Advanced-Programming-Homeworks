#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <string>
using namespace std;
struct node
{
	string name;
	int vote;
	node * prev;
	node * next;

	node(string party)
	{
		name = party;
		vote = 0;
		prev = NULL;
		next = NULL;
	}
};

class linkedlist 
{
private:
	node * head;
	node * tail;
public:
	linkedlist();
	node * EnterVotes(node * head,string partyname,int votenum);
	node * findparty(node * head,string partyname);
	bool partysearch(node * head,string partyname);
	void addparty(node * &head,node * ptr);
	void DeleteParty(node * &head,node * deletingptr);
	node * RemoveVotes(node * head,string partyname,int votenum);
	void Displaybest(node * head);
	void Displayworst(node * head);
};
#endif