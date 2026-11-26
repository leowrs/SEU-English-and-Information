#include <iostream>
#include <cmath>   //包含数学函数头文件
using namespace std;

void main()
{
	double n=0,term=1,sum=0,pi;

	while(fabs(term)>1e-7)
	{
		sum = sum + term;
		n++;
		term = pow(-1,n)/(2*n+1);
	}
	pi=4*sum;
	cout<<"pi="<<pi<<endl;
}


/*
int main( )
{
    int sign=1;    // sign表示转换符号
    double n=1,t=1,pi=0;
    while((fabs(t))>1e-7)
    {
             pi=pi+t;   n=n+2;
             sign= -sign;     t=sign/n;
     }
     pi=pi*4;
     cout<<"pi="<<pi<<endl;
     return 1;
}
//*/