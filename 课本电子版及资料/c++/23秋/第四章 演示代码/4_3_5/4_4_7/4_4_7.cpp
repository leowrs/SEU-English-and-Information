#include <iostream>
using namespace std;

void main()
{
	int a=1;
	int &b=a;

	cout<<"a的地址："<<&a<<endl;
	cout<<"b的地址："<<&b<<endl;

	b=8;
	cout<<"在运行b=8后，a="<<a<<endl;

}