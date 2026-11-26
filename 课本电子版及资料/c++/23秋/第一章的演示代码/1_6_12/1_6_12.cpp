#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int main()
{
	int a=1,b=2,c=3;
	bool result;
	result = a||b++||c++;

    cout<<"result="<<result<<endl;
	cout<<"a="<<a<<endl;  
	cout<<"b="<<b<<endl; 
	cout<<"c="<<c<<endl; 
	return 0;
} 
