#include <iostream>
using namespace std;
void  p1(int x, int y);
void main( )
{        
        int a=1; 
        int b=2;
        p1(a,b);  //调用p1函数，a,b为实参
        cout<<"a="<<a<<"\t b="<<b<<endl;
		cout<<"x="<<x<<"\t y="<<y<<endl;  
//形参在没有出现函数调用时不占用内存空间，调用结束形参所占空间被收回；
} 
void  p1(int x, int y) //定义p1函数，x,y 是形参
{ 
        int z=4;
        x=x+y+z;
        y=3*y;
        cout<<"x="<<x<<"\t y="<<y<<endl;
}//函数调用结束
