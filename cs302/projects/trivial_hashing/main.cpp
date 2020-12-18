#include <iostream>

using namespace std;

//change as needed
const int MAX = 1000;

//true if the value is stored
//first column holds positive numbers
//second column holds negative numbers
bool map[MAX+1][2];

bool search(int x)
{
	//testing positive values
	if (x >= 0)
	{
		if (map[x][0] == 1)
			return true; //value exists
		else
			return false;
	}

	//if x is not positive, it is negative
	x = -x;
	if (map[x][1] == 1)
		return true;
	return false;
}

void insert(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
		if (arr[i] >= 0) //insert positive numbers
			map[arr[i]][0] = 1;
		else //insert negative numbers
			map[-arr[i]][1] = 1;
}

int main()
{
    int a[] = { -1, 9, -5, -8, -5, -2 };
    int n = sizeof(a)/sizeof(a[0]);
    insert(a, n);
    int X = -5;
    if (search(X) == true)
       cout << "Present" << endl;
    else
       cout << "Not Present" << endl;
    return 0;
}

