#include <iostream>
#include "linkedlist.h"
using namespace std;

linkedlist::linkedlist()
{
	head = NULL;
	tail = NULL;
}

bool linkedlist::partysearch(node * head,string partyname) // function to check if partyname is already initialized.
{
	bool check = false;
	node * ptr = head;
	while (ptr != NULL)
	{
		if (ptr->name == partyname)
		{
			check = true;
		}
		ptr = ptr->next;
	}
	return check; // we return boolean to use it in the if else statements.
}

node * linkedlist::findparty(node * head,string partyname)		//function to find the party if its in the list
{
	node * ptr = head;
	while (ptr != NULL)
	{
		if (ptr->name == partyname)
		{
			break;
		}
		ptr = ptr->next;
	}
	return ptr; // we return the founded pointer to use it later.
}

void linkedlist::addparty(node * &head,node * addingptr)
{
	node * ptr = head;
	if (head == NULL || head->vote < addingptr->vote) // if new party has more votes than head(has the most votes)
	{
		node * temp = head;
		head = addingptr;
		head->next = temp;
		temp->prev = head;
	}
	else if (head->next == NULL) // if there is only one party in the list.
	{
		
		if (head->vote > addingptr->vote) 
		{
			tail = addingptr;
			tail->prev = head;
			head->next = tail;
		}
		else if (head->vote < addingptr->vote)
		{
			head = addingptr;
			tail->prev = head;
			head->next = tail;
		}
		else if (head->vote == addingptr->vote) // if new pointer has same vote num with current pointer.
		{ // then we ll look alphabetical order.
			int comparison; // compare func returns int value due to its alphabetical order.
			comparison = head->name.compare(addingptr->name); // comparing party names in alphabetical order with this function.
			if (comparison < 0) //if comparison has negative value, it means that first string in the compare func has priority.
			{
				tail = addingptr;
				tail->prev = head;
				head->next = tail;
			}
			else
			{
				head = addingptr;
				tail->prev = head;
				head->next = tail;
			}
		}	
	}
	else
	{
		while (ptr->next != NULL && addingptr->vote <= ptr->next->vote) // else if we re gonna add it middle or end.
		{                                                               // we check until the vote number is higher or equal.  
			ptr = ptr->next;  
		}
		if (ptr->next == NULL) // if we re going to add it to the end. 
		{
			addingptr->next = ptr->next;
			ptr->next = addingptr;
			addingptr->prev = ptr;
		}
		else if (addingptr->vote == ptr->next->vote) // if new pointer has same vote num with current pointer.
		{   // then we ll look alphabetical order.
			int comparison;  // compare func returns int value due to its alphabetical order.
			comparison = ptr->next->name.compare(addingptr->name); // returns - if current pointer has alphabetical priority.
			if (comparison < 0)//if comparison has negative value, it means that first string in the compare func has priority.
			{
				ptr->prev->next = addingptr;  // so we add new pointer between current pointer and previus one
				addingptr->prev = ptr->prev;
				addingptr->next = ptr;
				ptr->prev = addingptr;
			}
			else 
			{
				ptr->next->prev = addingptr; // if new pointer has alphabetical priority, we add it between current pointer
				addingptr->next = ptr->next; // and the next pointer.
				ptr->next = addingptr;
				addingptr->prev = ptr;
			}
		}
		else // we add new pointer between current pointer and its next, then connect them by prev and next pointers.
		{
			ptr->next->prev = addingptr; 
			addingptr->next = ptr->next;
			ptr->next = addingptr;
			addingptr->prev = ptr;
		}		
	}
}

void linkedlist::DeleteParty(node * &head,node * deletingptr)
{
	node * ptr;
	if (deletingptr == head && head->next == NULL) // if we re gonna delete the only party in the list.
	{
		head = NULL; // we just the head NULL to not lose the head.
	}
	else if (deletingptr == head) // if we re deleting the head.
	{
		head->next->prev = NULL; // prev will be NULL because head is the first node.
		head = head->next; 
		delete deletingptr;
	}
	else
	{
		ptr = head;
		while (ptr->next != deletingptr)
		{
			ptr = ptr->next;
		}
		if (deletingptr->next == NULL) // if the pointer we re gonna delete is the last one.
		{
			ptr->next = deletingptr->next;
		}
		else
		{
		deletingptr->next->prev = ptr;  // detaching the node we re gonna delete then connect previus and next ones.
		ptr->next = deletingptr->next;
		}
		delete deletingptr;
	}
}

node * linkedlist::EnterVotes(node * head,string partyname,int votenum)
{
	if (head == NULL) // if there is not any party yet.
	{
		node * temp = new node(partyname);
		temp->vote = votenum;
		head = temp;
		tail = temp;
	}
	else if (head->next == NULL)	// if there is only one party in list.
	{
		if (head->name == partyname) // if entered party is the same one in the list, we basically just add the given votes.
		{
			head->vote += votenum;
		}
		else
		{
			node * temp = new node(partyname);
			temp->vote = votenum;
			if (head->vote > temp->vote)
			{
				tail = temp;
				tail->prev = head;
				head->next = tail;
			}
			else if (head->vote < temp->vote)
			{
				head = temp;
				tail->prev = head;
				head->next = tail;
			}
			else if (head->vote == temp->vote) // if new party has same vote num with the head party.
			{
				int comparison; // compare func returns int value due to its alphabetical order.
				comparison = head->name.compare(temp->name); // comparing party names in alphabetical order with this function.
				if (comparison < 0)
				{
					tail = temp;
					tail->prev = head;
					head->next = tail;
				}
				else
				{
					head = temp;
					tail->prev = head;
					head->next = tail;
				}
			}
		}
	}
	else
	{
		bool partycheck = partysearch(head,partyname); // we first check if the given party name is in the list.
		if (partycheck == true) // if it is, then we re going to update it.
		{
			node * ptr = findparty(head,partyname); // function to find the given party's pointer to make changes.
			if (ptr == head) // if pointer is head, its already leading so adding votes wont change the order.
			{
				head->vote += votenum;
			}
			else // Detaching the pointer from the list to add it again in order.
			{
				int newvote = ptr->vote + votenum; // adding new votes to the current votes.
				DeleteParty(head,ptr);  // first delete the current one so that we can keep the list sorted.
				node * temp = new node(partyname); // create it as a new party with the same name.
				temp->vote = newvote; // adding the updated votes.
				addparty(head,temp); // then add it like a new party, so list can be sorted again.
			}
		}
		else // if there is no party with the given partyname
		{
			node * ptr = new node(partyname); // then we basically create new one and add it to the list.
			ptr->vote = votenum;
			addparty(head,ptr);
		}
	}
	cout << "Success!" << endl;
	return head;
}

node * linkedlist::RemoveVotes(node * head,string partyname,int votenum)
{
	bool partycheck = partysearch(head,partyname);
	if (partycheck == true)
	{
		node * ptr = findparty(head,partyname);
		int total = ptr->vote - votenum;
		if (total <= 0) // if party has no vote left, it should be deleted.
		{
			DeleteParty(head,ptr);
		}
		else
		{
			DeleteParty(head,ptr);
			node * temp = new node(partyname);
			temp->vote = total;
			addparty(head,temp);			
		}
		cout << "Success!" << endl;
	}
	else
	{
		cout << "Given party does not exist." << endl;
	}
	return head;
}

void linkedlist::Displaybest(node * head)
{
	node * ptr = head; // list is already sorted so if we start with the head and print it would be enough.
	while (ptr != NULL)
	{
		cout << ptr->name << "	" << ptr->vote << endl;
		ptr = ptr->next;
	}
}

void linkedlist::Displayworst(node * head)
{
	node * ptr = head; // list is sorted starting from best. our starting point is head so...
	while (ptr->next != NULL) // we should reach to the end of the list first so that we can go back starting from worst.
	{
		ptr = ptr->next; // to reach to end of the list.
	}
	while (ptr != NULL) // now we re going backwards and print it so list would be printed starting from worst votes.
	{
		cout << ptr->name << "	" << ptr->vote << endl;
		ptr = ptr->prev;
	}
}

