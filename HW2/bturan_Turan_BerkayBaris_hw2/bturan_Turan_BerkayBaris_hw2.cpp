#include <iostream>
#include <string>
#include <sstream> //for istringstream
using namespace std;

struct node
{
	int value;
	node *next;

	node()
	{}

	node(const int & s, node *link)
		: value(s), next(link)
	{}
};

/* Begin: code taken from ptrfunc.cpp */
void DisplayList (node * head)
{
	cout << "The list content is: ";
	node * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr ->value << " ";
		ptr = ptr->next;
	}
	cout << endl<<endl;
}
/* End: code taken from ptrfunc.cpp and updated */

/* Begin: code taken from ptrfunc.cpp */
void DeleteOneNode (node * toBeDeleted, node * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node * ptr;
		
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
	}
	else  //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while ptr point to the node just before toBeDeleted

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}
/* End: code taken from ptrfunc.cpp and updated */

/* Begin: code taken from ptrfunc.cpp and updated */
node * AddInOrder2_A(node * head, int newkey)
// pre: list is ascending sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
    node *  ptr = head;   // loop variable
	int deleted_node = 0;
	
	
	if(head == NULL || newkey < head->value)
	{
		node * temp = new node(newkey,head);
		//head = temp->next;

		cout << "Deleted nodes: ";

		while(temp->next != NULL)
		{
			cout << temp->next->value << " ";
			DeleteOneNode(temp->next,temp);
			deleted_node++;
			
		}

		if(deleted_node ==0)
			cout << "None" << endl;

		else
			cout << endl;

		cout << "Appended: " << newkey << endl;

		return temp;
	}

	while(ptr->next != NULL && ptr->next->value < newkey)
		ptr = ptr->next;

	if(ptr->next != NULL && ptr->next->value == newkey)
	{
		cout << newkey << " is already in the list!" << endl;
		return head;
	}

	else
	{

		cout << "Deleted nodes: ";

		while(ptr->next != NULL)
		{
			cout << ptr->next->value << " ";
			DeleteOneNode(ptr->next,ptr);
			deleted_node++;
		}

		if(deleted_node==0)
			cout << "None" << endl;

		else
			cout << endl;

		ptr->next = new node(newkey, NULL);
		cout << "Appended: "<< newkey << endl;

		return head;
	}
}
/* End: code taken from ptrfunc.cpp and updated */

/* Begin: code taken from ptrfunc.cpp and updated */
node * AddInOrder2_D(node * head, int newkey)
// pre: list is ascending sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
    node *  ptr = head;   // loop variable
	int deleted_node = 0;
	
	
	if(head == NULL || newkey > head->value)
	{
		node * temp = new node(newkey,head);
		//head = temp->next;

		cout << "Deleted nodes: ";

		while(temp->next != NULL)
		{
			cout << temp->next->value << " ";
			DeleteOneNode(temp->next,temp);
			deleted_node++;
			
		}

		if(deleted_node ==0)
			cout << "None" << endl;

		else
			cout << endl;

		cout << "Appended: " << newkey << endl;

		return temp;
	}

	while(ptr->next != NULL && ptr->next->value > newkey)
		ptr = ptr->next;

	if(ptr->next != NULL && ptr->next->value == newkey)
	{
		cout << newkey << " is already in the list!" << endl;
		return head;
	}

	else
	{

		cout << "Deleted nodes: ";

		while(ptr->next != NULL)
		{
			cout << ptr->next->value << " ";
			DeleteOneNode(ptr->next,ptr);
			deleted_node++;
		}

		if(deleted_node==0)
			cout << "None" << endl;

		else
			cout << endl;

		ptr->next = new node(newkey, NULL);
		cout << "Appended: "<< newkey << endl;

		return head;
	}
}
/* End: code taken from ptrfunc.cpp and updated */

void ClearList(node *head)
//Deletes all of the elements in the list
//And displays an appropriate massage
{
	cout << "All the nodes are deleted at the end of the program: "; 

	node * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr ->value << " ";
		ptr = ptr->next;
	}
	cout << endl;

	node *ptrr;
	while(head!=NULL)
	{
		ptrr=head;
		head=head->next;
		delete ptrr;
	}
}
/* End: code taken from ptrfunc.cpp and updated */

bool isEmpty(string numbers)
//returns true if there is no number in numbers
//returns false if there is any number
{
	if(numbers.empty())
		return true;
	else
	{
		for(int i=0; i< numbers.length(); i++)
		{
			if(numbers[i] != ' ' && numbers[i] != '\t')
				return false;
		}
		return true;
	}
}

int main()
{
	string order_mode, numbers;
	node *head = NULL;

	cout << "Please enter the order mode (A/D): ";
	cin >> order_mode;
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); //to  empty the input buffer after reading the order mode

	while (order_mode != "A" && order_mode != "D")
	{
		cout << "Please enter the order mode again (A/D): ";
		cin >> order_mode;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}


	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);

	cout << endl;

	if(isEmpty(numbers))
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
	else
	{
		if(order_mode == "A")
		{

			int current_number;
			istringstream input(numbers);

			while(input >> current_number)
			{
				cout << "Next number: " << current_number << endl;
				head = AddInOrder2_A(head,current_number);
				DisplayList(head);
			}
		}

		else // order_mode is "D"
		{
			int current_number;
			istringstream input(numbers);

			while(input >> current_number)
			{
				cout << "Next number: " << current_number << endl;
				head = AddInOrder2_D(head,current_number);
				DisplayList(head);
			}
		}

		ClearList(head);
	}
		
	return 0;
}