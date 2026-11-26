#include <iostream>
using namespace std;
float power(float,int);
void main()
{
	int n=3;
	double x=4.6;
	char c='a';
	cout<<"power("<<x<<","<<n<<")="<<power(x,n)<<endl<<endl;
	cout<<"power("<<n<<","<<x<<")="<<power(n,x)<<endl<<endl;
	cout<<"power("<<c<<","<<n<<")="<<power(c,n)<<endl<<endl;

//	power(x,n,c);   //错误的函数调用：参数个数不一致
 //	power(x);

	
//	char string[10]="Nanjing";  //错误的函数调用：无法进行类型转换
//	power(x,string);

}
float power(float x,int n)
{
	float pow=1;
	while(n--)
		pow*=x;
	return pow;
}