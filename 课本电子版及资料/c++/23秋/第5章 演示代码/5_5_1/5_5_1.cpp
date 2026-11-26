#include <iostream>
#include <typeinfo>
using namespace std;

void main()
{
	int a[4]={0};
	cout<<"数组名a的值："<<a<<endl;
	cout<<"数组第一个元素a[0]的地址："<<&a[0]<<endl;
	cout <<"数组名a的数据类型：" <<typeid(a).name(); 
	cout<< endl<<endl;

	int q[4]={4};
 //	a = q;  // 错误。数组名是指针常量，不能被修改

}