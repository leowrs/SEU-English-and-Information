#include <iostream>
using namespace std;

void main()  //指针常量
{
    int N=5, M=2;   
    int * const p=&N;  // 说明1：p是指针常量
	*p = 10;   // 说明2：指针常量可以修改指向的值；
//	p = &M;   //错误。说明3：指针常量不能改变指向
	
}
