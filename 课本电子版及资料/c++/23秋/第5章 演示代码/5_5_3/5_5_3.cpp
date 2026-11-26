#include <iostream>
using namespace std;
const int SIZE=3;

void main()
{
	int a[3]={1,2,3},i;
	int * p;

	cout<<"数组元素名\t 内存地址\t     元素值"<<endl;
	for(i=0;i<SIZE;i++)
		cout<<"a["<<i<<"] \t \t"<< a+i<<"\t \t"<<a[i]<<endl;

	p=a;
	cout<<endl<<"当p=a时，运行*p++语句时:";
	cout<<"正在运行：*p++的值："<<*p++<<"，p的值为"<<p<<endl<<endl;  // 在p++中，会先把p的值拿出来参加整个语句，在语句结束后再进行自增运算
	cout<<"运行完*p++语句，p的值变为"<<p<<endl;
}
