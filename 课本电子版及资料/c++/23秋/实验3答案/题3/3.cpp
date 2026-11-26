
#include<iostream>  
#include<cmath>
using namespace std;
#define PI 3.14    // 符号常量   
// 强调一下，3.14后面不能带分号
//如果写成 #define PI 3.14;  此时编译器就会用“3.14;”来替换所有的PI，
//这样就会出现异常的数值，但是程序还是可以运行的
const double C=2.8;  // 常变量

int main()
{
	double a[3],x[3];

	cout<<"请输入三个数:";
	cin>>x[0]>>x[1]>>x[2];

	a[0]=0.5*PI+2*C+3*sin(x[0]);
	a[1]=0.5*PI+2*C+3*sin(x[1]);
	a[2]=0.5*PI+2*C+3*sin(x[2]);

	cout<<"a[0]="<<a[0]<<endl;
	cout<<"a[1]="<<a[1]<<endl;
	cout<<"a[2]="<<a[2]<<endl;

	return 0;
}