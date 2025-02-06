/*********************************
	Author: Berkay Baris Turan
	Date: 30.03.2021
*********************************/

#ifndef _SubSeqsList
#define _SubSeqsList

struct SubSeqNode
{
	int value;
	SubSeqNode * next;

	SubSeqNode::SubSeqNode(int number, SubSeqNode *next_node ) //constructor
		:value(number),
		next(next_node)
	{
	}

};

struct SubSeqHeadNode
{
	int size;  // number of elements in the subsequence
	SubSeqNode * sHead;  // head of the subsequence list
	SubSeqHeadNode * next;

	SubSeqHeadNode(int num_ele, SubSeqNode * head_of_subseq, SubSeqHeadNode * next_node) //constructor
		:size(num_ele),
		sHead(head_of_subseq),
		next(next_node)
	{
	}

};

class SubSeqsList
{
public:
	SubSeqsList(); //default constructor that creates an empty list
	void Display(); //display the entire structure
	void Insert(SubSeqNode *seq); //insert one subsequence list to the data structure
	void Delete(SubSeqHeadNode *head_to_delete); //delete one subsequence list from the data structur
	bool Exists(int value); //whether a particular value exists in the data structure
	void DeleteEntire(); //delete the entire data structure
	SubSeqHeadNode *Copy(SubSeqHeadNode *HeadNode); //copies SubSeqHeadNode pointer
	bool SubSeqsList::SubSeqHead_Exist(SubSeqHeadNode *new_sHead); //whether parameter sequence exists in the list
	SubSeqHeadNode *SubSeqsList::AppropriatePlace (SubSeqHeadNode *new_sHead); //find the appropriate place for new sequence
	SubSeqHeadNode *SubSeqsList::Found_In_Sequence( int value); //returns pointer that points sequence has value in it 

private:
	SubSeqHeadNode * hHead;
};

#endif