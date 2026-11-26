#include <iostream>
using namespace std;
const int SIZE=4;

void main()
{
	int a[4]={1,2,3,4},i;
	int * p=a;

	cout<<"数组元素名\t 内存地址\t     元素值"<<endl;
	for(i=0;i<SIZE;i++)
		cout<<"a["<<i<<"] \t \t"<<a+i<<"\t \t"<<a[i]<<endl;

	cout<<endl<<endl<<"按照下标法访问数组元素"<<endl;
	for(i=0;i<SIZE;i++)
		cout<<"a["<<i<<"]="<<a[i]<<"\t \t p["<<i<<"]="
		<<p[i]<<endl;

	cout<<endl<<endl<<"按照指针法访问数组元素"<<endl;	
	for(i=0;i<SIZE;i++)
		cout<<"*(a+"<<i<<")="<<*(a+i)<<"\t  *(p+"<<i<<")="
		<<*(p+i)<<endl;

	cout<<endl<<"a+i与p+i的地址："<<endl;
	for(i=0;i<SIZE;i++)
		cout<<"a+"<<i<<"="<<a+i<<"\t  p+"<<i<<"="<<p+i<<endl;


	cout<<endl<<endl;
}