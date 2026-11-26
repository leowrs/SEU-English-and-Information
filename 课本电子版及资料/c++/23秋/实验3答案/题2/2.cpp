/*
2、实现课本《C++程序设计》P30，习题1.7和1.8，
请将运行结果以注释的形式写在程序代码中。
*/

#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d;
	cin>>oct>>a>>b>>hex>>c>>dec>>d;
	cout<<a<<'\t'<<b<<'\t'<<c<<'\t'<<d<<'\t'<<endl;  //习题1.7的输出
	cout<<a<<'\t'<<hex<<b<<'\t'<<oct<<c<<endl;    //习题1.8的输出
	return 0;
}

/* 此处是注释，程序输出结果为
19      19      35      23
19      13      43
*/