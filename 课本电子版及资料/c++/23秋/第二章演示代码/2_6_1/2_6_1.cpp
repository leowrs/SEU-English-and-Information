#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void main(){


	int m,k,i,n=0;
	bool prime;      //定义布尔变量prime

	for(m=101;m<=200;m=m+2)  //判别m是否为素数 
	{  
		prime=true;   //循环开始时设prime为真，即先认为m为素数
        k=int(sqrt(m));   //用k代表根号m的整数部分
        for(i=2;i<=k;i++) //此循环将m被2~根号m除，检查是否能整除
		{
			if(m%i==0)  //如果能整除，表示m不是素数
			{      prime=false; break;    }
        } 
        if (prime ) //如果m为素数
		{
	       cout<<setw(5)<<m;    n=n+1;   //n累计输出素数个数 
		}
        if(n%10==0)  cout<<endl;  //输出10个数后换行
	}  //for循环结束
     cout<<endl;         //最后执行一次换行





}