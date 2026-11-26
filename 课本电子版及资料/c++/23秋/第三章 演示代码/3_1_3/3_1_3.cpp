#include <iostream>
using namespace std;

int max (int a, int b)
{
   // /*  // 函数不能嵌套定义！
	void TableHead ( )  
	{
      cout<<"******************\n"<<endl;
      cout<<"* Welcome to C++! *\n"<<endl;
      cout<<"******************\n"<<endl;
	}
//*/
	return (a>=b?a:b);
}


void main()
{
	int a=3,b=5;
	cout<<"最大值："<<max(a,b)<<endl;

}