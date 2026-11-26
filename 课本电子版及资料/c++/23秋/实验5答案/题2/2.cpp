
#include <iostream>
using namespace std;

int main()
{
	int n,i,j;
	cout<<"请输入行数n：";
	cin>>n;

	cout<<"第一种图案如下："<<endl;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=i;j++)
		{
			cout<<"*";
		}
		cout<<endl;
	}

	cout<<endl<<"第二种图案如下："<<endl;

	int middle= (n+1)/2;
	for(i=1;i<=middle;i++)         // 先打印上半部分
	{
		for(j=1;j<=middle-i;j++)
			cout<<" ";
		for(j=0;j<2*i-1;j++)
			cout<<"*";
		cout<<endl;
	}
	for(i=1;i<middle;i++)        //再打印下半部分
	{
		for(j=1;j<=i;j++)
			cout<<" ";
		for(j=0;j<2*middle-1-2*i;j++)
			cout<<"*";
		cout<<endl;
	}
	cout<<endl;
	return 0;
}