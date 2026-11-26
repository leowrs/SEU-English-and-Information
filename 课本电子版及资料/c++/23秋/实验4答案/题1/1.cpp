/*
4、课本《C++程序设计》P66，习题2.2，
（1）其中要求变量x和y的数据类型是int型，
请给出计算y的代码，注意x的值是由键盘输入的；
（2）计算y的奇偶性，并输出结果；
注意：把题中第三行的“x>=10”改为“x>10”。
*/
#include <iostream>   // 预处理命令，这里没有分号
using namespace std;

void main()
{
	int x,y;

	cout<<"请输入一个数：";
	cin>>x;

//	/*
	if(x<1)
		y=x; 
	else if(x<=10)  
		y=2*x-1;
	else
		y=3*x-11;
	cout<<"y="<<y<<endl;  //*/


	if(y%2 )  // 或者 y%2 == 1 ,注意是两个等号
		cout<<"y是奇数！"<<endl;
	else
		cout<<"y是偶数！"<<endl;
	/*
	y=100;
	if(1<=x<=10) //注意2：不能用连续的小于号
		y=2*x-1;
	cout<<"y="<<y<<endl;
	//*/
} 
