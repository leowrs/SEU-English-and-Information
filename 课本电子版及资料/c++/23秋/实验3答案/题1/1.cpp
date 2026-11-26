#include<iostream>
using namespace std;
int main()
{
	int a;
	float b;
	char c ;
	double d;

	cout<<"请分别输入a，b，c，d（用空格来间隔这四个输入）："<<endl;
	cin>>a>>b>>c>>d;
	cout<<endl;
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
	cout<<"c="<<c<<endl;
	cout<<"d="<<d<<endl;
	cout<<"a+b+c+d="<<(a+b+c+d)<<endl;//4个变量的和是double类型
	
	return 0;
}
// 字符变量里面保存的字符c，在运算时，通过数据类型转换，变成其ascii码值进行计算。