#include <iostream>
using namespace std;

void main()
{ int a=0x0018FF3C;
  int *p=&a;   //把a的地址赋给指针变量p

   cout<<hex<<"a的值以16进制表示："<<a<<endl;
   cout<<"指针p的值："<<p<<endl;
//注意：虽然可以直接输出变量a和指针变量p的值，
//但是这两个值的内涵不一样。

   int *q,c;
   q=p;   //指针变量p的值可以赋给指针变量q

     c= (int)p;   //指针变量p的值不能直接赋给普通变量，
	 //如果要赋值，需要进行类型转换
	 cout<<"c="<<c<<endl;
   
	 q=(int*)a;    //普通变量的值不能直接赋给指针变量
	 //如果要赋值，需要进行类型转换
	 cout<<"q="<<q<<endl;
}
