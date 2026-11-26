// 字符数组和指针的初始化的区别
#include <iostream>
using namespace std;

void main()
{
	char str[10]="C++!";
	str[0]='D';
	cout<<str<<endl;

	char *p = "C++!"; //指针p指向了一个字符串常量
	p[0] = 'D';  //编译不提示出差，但是运行会出错。
	// 不能修改字符串常量
	cout<<p<<endl;
}