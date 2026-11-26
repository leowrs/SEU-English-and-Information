// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
int MinComMultiple(int n,int m);
int MaxCaoDevissor(int n,int m);
void main()
{
	int i,j;
	cout<<"请输入两个整数：";
	cin>>i>>j;
	cout<<"最大公约数是："<<MaxCaoDevissor(i,j)<<endl;
	cout<<"最小公倍数是："<<MinComMultiple(i,j)<<endl;
	system("pause");
}
int MaxCaoDevissor(int n,int m)
{
	int i;
	for( i=(m>=n?m:n);i>0;i--)
	{
		if(n%i==0&&m%i==0)
			break;
	}
	return i;
}
int MinComMultiple(int n,int m)
{
	int i;
	for(i=(m>=n?m:n);i>0;i++)
	{   if(i%n==0&&i%m==0)
	    break;
	}
	return i;
}