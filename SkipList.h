#pragma once
#include<iostream>
#include<vector>
using namespace std;

class SkipList
{
	struct Node
	{					
		Node* up;				//a single node with all connections and a key
		Node* down;
		Node* left;
		Node* right;
		int val;
		friend class SkipList;
	public:
		Node(int v = 0, Node* u = nullptr, Node* d = nullptr, Node* l = nullptr, Node* r = nullptr)
		{
			val = v;
			up = u;
			down = d;
			left = l;
			right = r;
		}
	};

	vector<Node*> head;				//vector to store starting head of all levels
	vector<Node*> tail;				//vector to store tail of all levels 

	int current_level;											

public:

	SkipList()
	{
		srand(static_cast<unsigned int>(time(NULL)));				//seed for random
		current_level = 0;
		Node* starting_head = new Node(INT_MIN);			    	//to handle boundry cases
		Node* starting_tail = new Node(INT_MAX);

		starting_head->right = starting_tail;					//initial head and tail
		starting_tail->left = starting_head;
		head.push_back(starting_head);
		tail.push_back(starting_tail);
	}

	Node* CreateNode(int val, int level)
	{
		int index = level;							//creates a node at a given level,does not deal with up and down links
		Node* insert = new Node(val);
		Node* itr = head[index];

		while (itr->right != nullptr && val > itr->val)				//iteration
			itr = itr->right;

		insert->right = itr;							//left and right connections
		insert->left = itr->left;

		itr->left->right = insert;
		itr->left = insert;

		return insert;
	}

	Node* Search(int val)
	{
		Node* itr = head[current_level];					//start from latest head and move downwards accordingly

		while (itr != nullptr)
		{
			if (val == itr->val)
				return itr;
			if (val > itr->val && val < itr->right->val)			//check the current node val and node->right val to determine the cases
			{
				if (itr->down)
				{
					itr = itr->down;
					continue;
				}
			}
			itr = itr->right;
		}
		return itr;
	}

	void Insert(int val)
	{
		int level = 0;
		Node* insert = CreateNode(val, 0);					//insert a node at bottom row

		while (RandomLevel() == 1)							
		{
			level++;							//increase level index if coin is 1
			if (level > current_level)
			{
				current_level++;					//increase total level number
				Node* new_head = new Node(INT_MIN);			//if upper level does not exist,create new tail and head
				Node* new_Tail = new Node(INT_MAX);

				new_head->down = head[level - 1];
				head[level - 1]->up = new_head;

				new_Tail->down = tail[level - 1];
				tail[level - 1] = new_Tail;				//make upper and downwards connection

				new_head->right = new_Tail;
				new_Tail->left = new_head;

				head.push_back(new_head);
				tail.push_back(new_Tail);				//push the new head and tail
			}

			insert->up = CreateNode(val, level);				//create a new node at upper level
			insert->up->down = insert;
			insert = insert->up;						//move to upper node as the loop can continue and a new node can be create on top of that layer
		}
	}

	void Print()
	{
		Node* itr;								//start printing from top row
		for (int i = 0; i < head.size(); i++)
		{
			itr = head[current_level - i];
			while (itr != nullptr)						//iteration
			{
				cout << itr->val << " ";
				itr = itr->right;
			}
			cout << endl << endl;
		}
	}

	bool Delete(int val)
	{
		Node* del = Search(val);						//delete the first searched value
		if (del == nullptr)							//if val does not exist,return
			return false;

		Node* L = del->left;
		Node* R = del->right;

		L->right = del->right;							//left right new connections
		R->left = del->left;

		if (del->down)								//up down new connections
		{
			del->down->up = nullptr;
			del->down = nullptr;
		}

		if (del->up)
		{
			del->up->down = nullptr;
			del->up = nullptr;
		}

		delete del;								//free memory
		return true;
	}

	int RandomLevel()
	{
		return rand() % 2;							//return a random number between 1 and 0
	}
};
