#include <iostream>
#include <iomanip>
using namespace std;

int main()
{	
	int i,j,k;  //都输入20
	cin>>oct>>i;  //输入为8进制数
	cin>>hex>>j;  //输入为16进制数
	cin>>k;       //输入的进制数还是16进制数

	cout<<endl<<"i="<<i<<endl;//输出默认为10进制
	//设置输入的进制数，不影响输出的进制数
	cout<<"j="<<j<<endl;

	cout<<"k="<<k<<endl;

   return 0;
 
}
