#include <iostream>
using namespace std;

 float area(float r=6.5);  // 在函数声明是设定默认值
//给出默认值的地方一定要在main函数之前。且只能给一次。

void main()
{
	cout<<"设定r的默认值为6.5，面积为  "<<area()<<endl;
	cout<<"取r=10，面积为  "<<area(10)<<endl;
}


float area(float r  )    //此处不能再给出r的默认值r=6.5
{ 
	return 3.14*r*r;
}
// 不能在函数声明和函数定义同时设定默认值，即使默认值相同也不行