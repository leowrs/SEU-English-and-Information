#include<iostream>
using namespace std;

int sum(int a,int b) { return a+b;}
double sum(double a,double b) {return  a+b;}

void main()
{	

// show1: 需要注释掉  int sum() 的代码，否则编译器会找到了两个类似的重载函数
	cout<<"2.2+5="<<sum(2.2,5)<<endl; //错误
	cout << "2.2+5=" << sum(2.2, (double)5) << endl  ;//正确
 

}



