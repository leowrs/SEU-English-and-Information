#include<iostream>
using namespace std;
int main()
{
	unsigned short int a=65535,b=4,sum;
	sum=a+b;
	cout<<sum<<endl;
	return 0;
}
	//输出是0，因为unsigned short int ，
	//占用2个字节，取值范围是0~65535，sum=65535+1=2^16,发生了溢出
// 注意：2^16是个17位的二进制数，即 1  0000   0000    0000   0000
//
//    1111 1111 1111 1111
//+                    10
// 1  0000 0000 0000 0001