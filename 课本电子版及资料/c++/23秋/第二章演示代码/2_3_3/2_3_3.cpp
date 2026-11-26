#include <iostream>
#include <cmath>
using namespace std;

void main(){

	float x0,x1,a;
	
	cout<<"输入一个正数：";
	cin>>a;
	
	if(a>0)
	{
		x1=a/2;
		do
		{
			x0=x1;
			x1=(x0+a/x0)/2;
		} while(fabs(x1-x0)>=1e-5);
		cout<<a<<"的平方根为："<<x1<<endl;

	}
	else if(a==0)
		cout<<a<<"的平方根为：0"<<endl;
	else
		cout<<a<<"不能开平方"<<endl;
}

 // change: 把a>0 改为 a>=0，再输入0，看看结果
