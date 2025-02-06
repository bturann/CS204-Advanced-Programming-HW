/*********************************
	Author: Berkay Baris Turan
	Date: 30.03.2021
*********************************/

#include "SubSeqsList.h"
#include <cstdlib> //for defining NULL
#include <iostream>
using namespace std;

SubSeqsList::SubSeqsList() :  hHead(NULL) {} // default constructor

void SubSeqsList::Display()
//display the entire structure
{
	SubSeqHeadNode *current_Subseq_Head = hHead;

	cout << endl <<"FINAL CONTENT" << endl;

	while(current_Subseq_Head != NULL)
	{
		cout << current_Subseq_Head->size << "| ";

		while(current_Subseq_Head->sHead != NULL)
		{
			cout << current_Subseq_Head->sHead->value << " ";

			if(current_Subseq_Head->sHead->next != NULL)
				cout << "--> ";

			current_Subseq_Head->sHead = current_Subseq_Head->sHead->next;
		}

		cout << endl;

		current_Subseq_Head = current_Subseq_Head->next;
	}

	if(hHead == NULL)
	{
		cout << "List is empty!" << endl;
	}
}

SubSeqHeadNode *SubSeqsList::Copy(SubSeqHeadNode *HeadNode)
//copies SubSeqHeadNode HeadNode pointer
{
	SubSeqHeadNode *copy_sHead = new SubSeqHeadNode(HeadNode->size,NULL,NULL);

	SubSeqNode *ptr = HeadNode->sHead;

	while(ptr !=NULL)
	{
		SubSeqNode *lastHead = copy_sHead->sHead;

		while(lastHead != NULL && lastHead->next != NULL)
		{
			lastHead = lastHead->next;
		}
		SubSeqNode *copy = new SubSeqNode(ptr->value,NULL);

		if(lastHead == NULL)
			copy_sHead->sHead = copy;

		else
		{
			lastHead->next = copy;
		}

		ptr = ptr->next;
	}

	return copy_sHead;
}

bool SubSeqsList::SubSeqHead_Exist(SubSeqHeadNode *new_sHead)
//whether parameter sequence exists in the list
//true if exists
//false if not exists
{
	SubSeqHeadNode *ptr = hHead;

	while(ptr != NULL)
	{
		if(ptr->size == new_sHead->size)
		{
			int count = 0;

			SubSeqNode *ptr_sHead = ptr->sHead;
			SubSeqNode *new_Seq = new_sHead->sHead;

			while(ptr_sHead != NULL && new_Seq != NULL)
			{
				if(ptr_sHead->value == new_Seq->value)
				{
					count++;
				}

				ptr_sHead = ptr_sHead->next;
				new_Seq = new_Seq->next;
			}

			if(count == new_sHead->size)
				return true;
		}
		ptr = ptr->next;
	}
	return false;
}

SubSeqHeadNode *SubSeqsList::AppropriatePlace (SubSeqHeadNode *new_sHead)
//find the appropriate place for new sequence
//and returns it.
{
	SubSeqHeadNode *ptr = hHead;

	SubSeqHeadNode *ptr_next =hHead->next;

	while(ptr != NULL)
	{

		if(ptr_next == NULL)
			return ptr;
		SubSeqNode *current_node = ptr->sHead;

		SubSeqNode *ptr_next_node = ptr_next->sHead;

		SubSeqNode *current_node_in_new_sHead = new_sHead->sHead; 

		if((ptr->size < new_sHead->size) && (ptr_next->size == new_sHead->size))
		{

			while((ptr_next_node != NULL) && (ptr_next_node->value == current_node_in_new_sHead->value))
			{
				ptr_next_node = ptr_next_node->next;
				current_node_in_new_sHead = current_node_in_new_sHead->next;
			}
			if(current_node_in_new_sHead->value < ptr_next_node->value)
				return ptr;
		}

		else if((ptr->size == new_sHead->size) && (ptr_next->size == new_sHead->size))
		{

			while((ptr_next_node != NULL) && (ptr_next_node->value == current_node_in_new_sHead->value))
			{
				ptr_next_node = ptr_next_node->next;
				current_node_in_new_sHead = current_node_in_new_sHead->next;
			}
			if(current_node_in_new_sHead->value < ptr_next_node->value)
				return ptr;
		}

		else if((ptr->size == new_sHead->size) && (ptr_next->size > new_sHead->size))
		{
			return ptr;
		}

		ptr = ptr->next;
		ptr_next = ptr_next->next;
	}
}

void SubSeqsList::Insert(SubSeqNode *node)
//inserts  new subsequence list that contains value of node to the data structure
{
	if(hHead == NULL)
	{
		cout << "Subsequence(s) containing "<< node->value <<" has/have been added" << endl;
		
		hHead = new SubSeqHeadNode(1,node,NULL);
	}

	else
	{
		SubSeqHeadNode *new_Headnode = new SubSeqHeadNode(1,node,NULL);

		SubSeqHeadNode *current_hHead = hHead;

		SubSeqHeadNode *next_hHead = hHead->next;

		bool a = true; //loop bool for breaking the loop when necessary

		while(current_hHead != NULL && a && current_hHead->size == 1)
		{
			if(next_hHead == NULL)
			{
				if(current_hHead->sHead->value > new_Headnode->sHead->value)
				{
					new_Headnode->next = current_hHead;
					hHead = new_Headnode;
					cout << "Subsequence(s) containing "<< node->value <<" has/have been added" << endl;
					a = false;
				}

				else
				{
					current_hHead->next = new_Headnode;
					cout << "Subsequence(s) containing "<< node->value <<" has/have been added" << endl;
					a = false;
				}
			}

			else if(current_hHead->sHead->value > new_Headnode->sHead->value)
			{
				new_Headnode->next = current_hHead;
				hHead = new_Headnode;
				cout << "Subsequence(s) containing "<< node->value <<" has/have been added" << endl;
				a = false;
			}

			else if((current_hHead->sHead->value < new_Headnode->sHead->value) && (next_hHead->sHead->value > new_Headnode->sHead->value))
			{
				new_Headnode->next = next_hHead;
				current_hHead->next = new_Headnode;
				cout << "Subsequence(s) containing "<< node->value <<" has/have been added" << endl;
				a = false;
			}

			else if((current_hHead->sHead->value < new_Headnode->sHead->value) && (next_hHead->size > 1))
			{
				new_Headnode->next = next_hHead;
				current_hHead->next = new_Headnode;
				cout << "Subsequence(s) containing "<< node->value <<" has/have been added" << endl;
				a = false;
			}

			current_hHead = current_hHead->next;
			if(next_hHead != NULL)
				next_hHead = next_hHead->next;


			SubSeqHeadNode *visiting_ptr = hHead;

			while(visiting_ptr != NULL)
			{
				SubSeqNode * visiting_node = visiting_ptr->sHead;
				bool loop_bool =true; //loop bool for breaking the loop when necessary

				while((visiting_node != NULL) && loop_bool)
				{
					SubSeqNode *new_one = new SubSeqNode(node->value,NULL);
					if((visiting_node->value < new_one->value) && (visiting_node->next == NULL))
					{
						SubSeqHeadNode *new_sHead = SubSeqsList::Copy(visiting_ptr);
						
						SubSeqNode *last_node = new_sHead->sHead;

						for(int i=0; i<new_sHead->size-1;i++)
						{
							last_node = last_node->next;
						}

						last_node->next = new_one; 
						new_sHead->size++;
						
						if(!SubSeqHead_Exist(new_sHead))
						{
							SubSeqHeadNode *appopriate_place = AppropriatePlace (new_sHead);
							new_sHead->next = appopriate_place->next;
							appopriate_place->next = new_sHead;
						}

					}

					visiting_node = visiting_node->next;
				}

				visiting_ptr = visiting_ptr->next;
			}
		}
	}
}

SubSeqHeadNode *SubSeqsList::Found_In_Sequence(int value)
//returns pointer that points sequence has value in it
{
	SubSeqHeadNode *ptr = hHead;

	while(ptr !=NULL)
	{
		SubSeqNode *suq_ptr = ptr->sHead;
		while(suq_ptr !=NULL)
		{
			if(suq_ptr->value == value)
				return ptr;

			suq_ptr = suq_ptr->next;
		}
		ptr = ptr->next;
	}

	return NULL;

}

void SubSeqsList::Delete(SubSeqHeadNode *head_to_delete)
//delete one subsequence list that parameter pointer points from the data structur
{
	if(head_to_delete == hHead)
	{
		hHead = head_to_delete->next;
	}

	else
	{
		SubSeqHeadNode *ptr = hHead;


		while((ptr != NULL)&&(ptr->next != NULL))
		{
			SubSeqHeadNode *ptr_next = ptr->next;

			if(ptr_next == head_to_delete)
			{
				SubSeqNode *ptr_node = ptr_next->sHead;

				while(ptr_node != NULL)
				{
					SubSeqNode *temp = ptr_node;
					ptr_node = ptr_node->next;
					delete temp;
				}
				ptr->next =ptr_next->next;
				delete ptr_next;
			}

			ptr = ptr->next;
		}
	}
}

bool SubSeqsList::Exists(int value)
//whether a particular value exists in the data structure
//true if exists
//false if not exists
{
	SubSeqHeadNode *ptr; 
	ptr = hHead;

	while (ptr != NULL)
	{
		
		if(ptr->sHead->value == value)
		{
			return true;
		}
		ptr = ptr->next;
	}

	return false;
}

void SubSeqsList::DeleteEntire()
//delete the entire data structure
{
	SubSeqHeadNode *ptrr;
	SubSeqNode *ptr_seq;

	while (hHead != NULL)
	{
		while(hHead->sHead != NULL)
		{
			ptr_seq = hHead->sHead;
			hHead->sHead = hHead->sHead->next;
			delete ptr_seq;
		}

		ptrr = hHead;
		hHead = hHead->next;
		delete ptrr;
	}
}