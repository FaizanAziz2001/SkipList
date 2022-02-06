#include <iostream>
#include"SkipList.h"
using namespace std;

int main()
{
	SkipList T;
	T.Insert(5);
	T.Insert(15);
	T.Insert(35);
	T.Insert(7);
	T.Insert(-65);
	T.Insert(40);
	T.Insert(-100);
	T.Print();

	if (T.Search(100))
		cout << 100 << " Found";
	else
		cout << 100 << " Not found";

	cout << endl << endl;

	if (T.Delete(5))
		cout << 5 << " Deleted";
	else
		cout << 5 << " Not deleted";
	cout << endl << endl;
	T.Print();
}

