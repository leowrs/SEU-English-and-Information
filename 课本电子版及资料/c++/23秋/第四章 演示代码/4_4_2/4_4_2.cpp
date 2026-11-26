#include <iostream>
using namespace std;
void swap(int &a,int &b)      //形参是引用类型
{     
       int t;
       t=a;    a=b;    b=t;
	   cout<<"在函数swap中，a地址："<<&a<<endl;
	   cout<<"在函数swap中，b地址："<<&b<<endl;
}

void main( ) 
{
         int i=3,j=5;
		 cout<<"i地址:"<<&i<<endl;
		 cout<<"j地址:"<<&j<<endl;
         swap(i,j);
         cout<<"调用swap函数后， i="<<i<<"\t j="<<j<<endl;
}

