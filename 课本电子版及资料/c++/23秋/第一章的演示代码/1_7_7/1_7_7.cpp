#include <iostream>
using namespace std;

void main()
{
	int a[2]={1}; //对数组a进行初始化，当初始化的个数少于数组长度时
	              // 编译器自动补0
    int b[2];   // 没有进行初始化，编译器不会补0
	cout<<"数组a:"<<a[0]<<"\t\t\t\t"<<a[1]<<endl;
	cout<<"数组b:"<<b[0]<<"\t\t"<<b[1]<<endl;
}