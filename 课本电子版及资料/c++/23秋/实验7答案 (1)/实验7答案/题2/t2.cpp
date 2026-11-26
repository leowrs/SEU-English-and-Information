/*
4、《C++程序设计》P103的题3.7。
要求：将结果输出到屏幕中，每行输出5个等式。
*/
#include <iostream>
#include <cmath>
#include<iomanip>
using namespace std;

bool IsPrime(int );

void main()
{
	int num,k,i=0;

	cout<<"4~50之间的偶数可以表示为两个素数之和："<<endl;

	for(num=4;num<=50;num=num+2)
	{	for(k=2;k<=num/2;k++)
			if(IsPrime(k) && IsPrime(num-k) )
			{
				cout<<setw(2)<<num<<"="<<setw(2)<<k<<"+"<<setw(2)<<num-k<<'\t';
				if(++i%5==0)
					cout<<endl;
			}
	}
	cout<<endl;

}

bool IsPrime(int k)
{
	for ( int i=2; i<=sqrt((double)k);i++)
		if(k%i == 0 )
			return false;
	return true;
}