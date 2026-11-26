#include <iostream>
using namespace std;

void main()
{
	double a=3.5, b=10;
	double *p1=&a, *p2=&b;

	cout<<"p1的内存地址："<<&p1<<"，p1的值："<<p1
		<<"    p1所指向的内存数据 *p1="<<*p1<<endl;
	cout<<"p2的内存地址："<<&p2<<"，p2的值："<<p2
		<<"    p2所指向的内存数据 *p2="<<*p2<<endl;

	cout<<endl<<"执行赋值语句p1=p2后："<<endl;
	p1=p2;
	cout<<"p1的内存地址："<<&p1<<"，p1的值："<<p1
		<<"   p1所指向的内存数据 *p1="<<*p1<<endl;
	cout<<"p2的内存地址："<<&p2<<"，p2的值："<<p2
		<<"    p2所指向的内存数据 *p2="<<*p2<<endl;
}