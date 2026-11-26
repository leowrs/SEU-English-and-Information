#include <iostream>
using namespace std;

class E
{
private: 
	int x,y;
public:
	E(int a, int b){x=a; y=b;}
	E(){x=y=0;}
	void P(){ cout<<x<<'\t'<<y<<endl;}
};

void main()
{
 	E e();    // 表示函数原型的说明，
//	E e;      // 定义类E的一个对象e
 	e.P();   // 
 
}
