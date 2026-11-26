#include<iostream> 
using namespace std;
int n=100;
void func()
{
	n*=2;
}
int main()
{
	 n*=2;
	 cout<<n<<endl;  //200
	 func();
	 cout<<n<<endl;  //400
	 return 0;
}
// 问题1：如果不对n进行初始化，运行结果是固定的吗？
//问题2：把n的定义放到main函数中，同时传递给func，运行结果是什么