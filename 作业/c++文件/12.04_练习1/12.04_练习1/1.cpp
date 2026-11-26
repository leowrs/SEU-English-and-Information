// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
class Q
{
	int x,y;
public:
	Q(int a = 0,int b = 0)
	{
		x = a; y = b;
	}
	void P()
	{
		cout << x << ',' << y << '\n';
	}
	~Q()
	{
		cout << "调用析构函数" << '\n';
	}
};
int main()
{
	Q q(50, 100);
	q.P();
	Q qq;
	qq.P();
	cout << "退出主函数！\n";
	return 0;
}