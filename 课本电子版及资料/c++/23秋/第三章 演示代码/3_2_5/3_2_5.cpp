#include <iostream>
using namespace std;
void dream(int a,int b)   
{
	a=a*5;      b=b*5;
}

void main()
{
	int a=2,b=3;
	dream(a,b);
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
}
