// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
class Test
{
	int x, y;
public:
	Test(int a,int b)
	{
		x = a; y = b;
		cout << "调用了构造函数！\n";
	}
	Test( Test& t) {
		x = t.x; y = t.y;
		cout << "调用了拷贝构造函数！\n";
	}
	void show()
	{
		cout << "x=" << x << '\t' << "y=" << y << "\n";
	}
};
int main()
{
	Test t1(10, 10);
	Test t2 = t1;
	Test t3(t1);
	t1.show();
	t2.show();
	t3.show();
	return 0;
}