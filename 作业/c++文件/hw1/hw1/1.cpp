// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double x,epsilon=1e-5;
	cout<<"请输入初始值：";
	cin>>x;
	cout<<endl;
	while(fabs(x*x+10*cos(x))>epsilon)
		x=(x*x-10*(x*sin(x)+cos(x)))/(2*x-10*sin(x));
	cout<<"方程的近似根为："<<x<<endl;
	cout<<"方程的近似程度："<<x*x+10*cos(x)<<endl;
	system("pause");
	return 0;
}