#include <iostream>
using namespace std;

void output(int b[])
{ 
	cout<<"在output函数中：sizeof(b)="<<sizeof(b)<<endl;
	int c[]={1,2,3,4,5,6};
	cout<<"在output函数中：sizeof(c)="<<sizeof(c)<<endl;
}

void main()
{
	int a[]={1,2,3,4,5,6};
	cout<<"在main函数中：sizeof(a)="<<sizeof(a)<<endl;
	output(a);
}

//说明：数组被作为参数进行传递时会退化为指针，
//如果对形参数组用sizeof进行计算，得到的只是指针占据的空间，
//无法得到数组的长度。