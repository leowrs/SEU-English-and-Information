// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
int main()
{
	int a = 1, b = 23;
	b=a<<33;
	char c;
	cin.get(c);
	cout << c;
	cout << a<<"\t" << b << endl;
	cout << a * b++ << endl;
	cout << sizeof((double)b);
	return 0;
}