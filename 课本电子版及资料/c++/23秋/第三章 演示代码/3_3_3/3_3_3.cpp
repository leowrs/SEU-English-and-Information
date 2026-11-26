#include<iostream>
using namespace std;
void fun()
{
	auto t=5;	// 局部变量//vs中不允许使用auto int
	//vs中对于auto进行了新的定义
	cout<<"fun()中的t="<<t<<endl;
}

int main()
{
	float t=3.5;	//局部变量
	cout<<"main()中的t="<<t<<endl;
	fun();
	cout<<"main()中的t="<<t<<endl;

	int flag=1;
	while(flag)
	{
		int x=3;        //局部变量：定义在块中
		cout<<"块中的x="<<x<<endl;
		flag=0;
	}

//	cout<<"块中的x="<<x<<endl;   // 发生错误
        return 0;
}

//运行main中的倒数第二句语句，看看为什么出错。