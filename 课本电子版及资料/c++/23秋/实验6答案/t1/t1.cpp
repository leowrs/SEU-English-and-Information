
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double x0,x1;
	const double epsilon=1e-5;
	const int h=1e5;
	int n=0;//用来统计循环次数的

	cout<<"请输入初始值：";
	cin>>x1;     // 由方程可知，x<=sqrt(10), 结果是：3.16,1.97

	cout<<endl;
	do
	{
		x0=x1;
		x1=(x0*x0-10*(x0*sin(x0)+cos(x0)))/(2*x0-10*sin(x0));
		n++;
	}while(fabs(x1-x0)>epsilon && n<h);

	if(n==h)
		cout<<"迭代计算的次数超过了"<<h<<"次"<<endl;
	else
		cout<<"方程的近似根为："<<x1<<endl;

	cout<<"方程的近似程度："<<x1*x1+10*cos(x1)<<endl;

	return 0;
}