// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
int main()
{
	int num2,n=0,num1;
	int digit[7];
	cout<<"请输入一个不超过7位数的正整数：";
	cin>>num1;
	num2=num1;
	do
	{
		digit[n]=num1%10;
		num1=num1/10;
		n++;
	}while(num1>0);
	for(int i=0;i<n;i++)
		num1=num1*10+digit[i];
	if(num1==num2)
		cout<<num2<<"是回文数！"<<endl;
	else 
		cout<<num2<<"不是回文数"<<endl;
	system("pause");
	return 0;
}