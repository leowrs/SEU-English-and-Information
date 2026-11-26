#include <iostream>
using namespace std;

int max (int a, int b)//如果写成int max(int a,b)是错误的，（因为每个参数的数据类型都用给出）
{
	return (a>=b?a:b);
}

void main()
{
	int x=3,y=5,max1;
	max1 = max(x,y);
	cout<<"最大值："<<max1<<endl;
}