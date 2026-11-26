#include <iostream>
#include <iomanip>
using namespace std;

int main()
{      
	   int i = 123, j=123456;
	   cout<<setw(5)<<i<<endl;
	   cout<<setw(5)<<j<<endl;  //j的长度超过域宽5，setw函数将不起作用
	   cout<<i<<endl;  //上次的setw函数不会影响下次cout的输出格式

	   return 0;

}
