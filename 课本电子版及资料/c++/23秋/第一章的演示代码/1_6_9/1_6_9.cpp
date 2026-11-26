#include <iostream>
using namespace std;

int main()
{
	int a;
	(a=7)=66;  //可以把“a="去掉，提示的错误是一样的
//	 a = 7 = 66;
	 cout << "a=" << a << endl; 
	return 0;
}