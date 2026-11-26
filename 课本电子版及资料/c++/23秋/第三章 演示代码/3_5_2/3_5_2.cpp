 #include <iostream>
using namespace std;
void  swap(int, int );
void main( )
{
        int a=3,b=5; 
        swap(a, b);  //调用swap函数，a,b为实参
        cout<<"在main函数中：a="<<a<<"\t b="<<b<<endl;
} 
void  swap(int a, int b) //定义p1函数，a,b 是形参
{ 
        int t;
        t=a;   a=b;  b=t;
        cout<<"在swap函数中：a="<<a<<"\t b="<<b<<endl;
}//函数调用结束
