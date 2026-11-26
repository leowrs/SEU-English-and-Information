#include  <iostream>
using namespace std;
class Box
{
	int x,y,z;
public:
	Box(int a=1,int b=1,int c=1)
	{
		x=a;  y=b; z=c;
		cout<<"调用了构造函数!\n";
	}
	Box(const Box &b)//若未定义，则系统提供默认拷贝构造函数
	{
		x=b.x;  y=b.y; z=b.z;
		cout<<"调用了拷贝构造函数!\n";
	}
	void Show() {  cout << "x="<<x<<"\t y="<<y<<"\t z="<<z<<endl; }
 };

void fun(Box b)
 {
};

void  main(void) 
{
      Box box1(5,10,12); 
 
	  fun(box1);
}
