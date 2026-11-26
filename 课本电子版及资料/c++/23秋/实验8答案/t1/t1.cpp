// 题1：课本《C++程序设计》P183，题5.3。
//杨辉三角
#include <iostream>
#include <iomanip>
using namespace std;

void output(int a[][11], int n)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<11; j++)
			if(a[i][j]!=0)
				cout<<setw(6)<<a[i][j];
			else cout<<setw(6);
		cout<<endl;
	}
}

void main()
{
	int a[10][11]={0,1};// a[0][0]=0,a[0][1]=1
	int i,j;

	for(i=1; i<10; i++)
		for(j=1;j<=i+1;j++)
			a[i][j] = a[i-1][j-1]+a[i-1][j];
        // 杨辉三角：每个数等于它上方两数之和。
	output(a,10);
}

