#include <iostream>
#include <cmath>
using namespace std;

void main()
{
	double epsilon=0.0005; //5e-4
	int n=1;   //item中的分母；
	int sign= -1;   //保存符号
	double x,sinx,item; // x是要输入的值，sinx是x对应的正弦函数值，item是单项值

	cin>>x;   //输入的实数
	sinx=x;
	item=x;
	
	while(  fabs(item)>epsilon  ) 
    {
		item=item * x * x / (n+1) / (n+2);
		sinx=sinx+sign * item;
		n=n+2;
		sign= (-1) * sign;
	 }
	   cout<<"sinx="<<sinx<<endl;
}