#include  <iostream>
using namespace std;
class Box
{
	int x, y, z;
public:
	Box(int a = 1, int b = 1, int c = 1)
	{
		x = a;  y = b; z = c;
		cout << "调用了构造函数!" << endl;
	}
	Box(const Box& b)//若未定义，则系统提供默认拷贝构造函数
	{
		x = b.x;  y = b.y; z = b.z;
		cout << "调用了拷贝构造函数!" << endl;
	}
};

Box fun()
{
	cout << "定义对象box2:" << endl;
	Box box2(100, 200, 300);
	cout << "******函数fun()调用结束！" << endl << endl;
	return box2;
};

void  main(void)
{
	fun();
}
