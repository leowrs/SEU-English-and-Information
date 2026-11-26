#include <iostream>
using namespace std;

void main()
{
	double s,d;
	cout<<"请输入购买金额：";
	cin>>s;
	switch( int ((s+1)/100) )   //强制转换表达式的数据类型，为什么？
	{
	case 0: d=0; break;
	case 1: d=0.05; break;
	case 2: case 3: d=0.1; break;
	case 4: case 5: case 6: d=0.15; break;
	default: d=0.2;
	}
	cout<<"折扣为："<<d<<endl;
	cout<<"打完折后，需支付金额为："<< (s*(1-d))<<endl;
}