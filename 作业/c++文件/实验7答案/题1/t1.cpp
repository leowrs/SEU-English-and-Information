// Original Author: GitHub @leowrs (https://github.com/leowrs)
/*1、《C++程序设计》P103的题3.4。要求：
题中的数字是从屏幕中进行输入；
在文件开始出给出函数声明，函数定义放在main()函数后面。
*/
#include <iostream>
using namespace std;

int MaxComDevisor(int n, int m); //求出m和n的最大公约数
int MinComMultiple(int n, int m);//求出m和n的最小公倍数

void main()
{
	int i,j;
	cout<<"请输入两个整数：";
	cin>>i>>j;

	cout<<"最大公约数是："<<MaxComDevisor(i,j)<<endl;
	cout<<"最小公倍数是："<<MinComMultiple(i,j)<<endl;

}

int MaxComDevisor(int n, int m)
{
	int i;
	for(i=(n>m?m:n) ; i>=1;i--)
		if(n%i==0 && m%i==0)
		break;
		
	return i;
}

int MinComMultiple(int n, int m)
{
	int i;
	for(i=(n<m?m:n) ; i<=m*n;i++)
		if(i%m==0 && i%n==0)
		break;
		
	return i;
}