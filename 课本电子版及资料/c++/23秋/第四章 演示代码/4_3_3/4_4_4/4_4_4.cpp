#include <iostream>
using namespace std;

void triple(int a,int b)   // void triple(int &x, int &y)
{
	a=3*a;
	b=3*b;
	cout<<"在triple函数中:"<<endl;
	cout<<"形参a的地址："<<&a<<"   形参b的地址："<<&b<<endl<<endl;
}
void main()
{
	int a=1,b=2;

	cout<<"在main函数中："<<endl;
	cout<<"实参a的地址："<<&a<<"   实参b的地址："<<&b<<endl<<endl;
	triple(a,b);
	cout<<"调用triple函数后： 实参a="<<a<<"\t 实参b="<<b<<endl<<endl;
}

