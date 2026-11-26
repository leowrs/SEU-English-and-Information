#include <iostream>
using namespace std;

const int SIZE=3;

void main()
{
	int a[SIZE]={1,2,3};
	int i;
		
	cout<<"数组a的内存地址是："<<a<<endl<<endl; 
	//数组名a是一个常量，表示的是数组的地址，不能被赋值
	
	for(i=0;i<SIZE;i++)
		cout<<"数组元素a["<<i<<"]的内存地址是："<<&a[i]<<endl; 
	// 输出每个数组元素的地址

	cout<<endl<<endl;
	cout<<"数组a的存储空间大小(字节数)："<<sizeof(a)<<endl;
	cout<<"数组a[0]的存储空间大小："<<sizeof(a[0])<<endl;
	cout<<"数组a的元素个数："<<sizeof(a)/sizeof(a[0])<<endl;

}