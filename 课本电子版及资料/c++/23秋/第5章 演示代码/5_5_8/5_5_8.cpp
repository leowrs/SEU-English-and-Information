#include <iostream>
using namespace std;

void main()
{
	int a[]={1,2,3,4,5,6};
	int *p, *q;
	p=a;
	q=&a[5];
	cout<<"q-p: "<<q-p<<endl;
	cout<<"p-q: "<<p-q<<endl;

	int *r;
	r=p+ (q-p)/2;  //r指向哪个元素？
	cout<<"*r="<<*r<<endl;
 //    r= p/2+ q/2;  //错误：指针变量的除法没有意义

}