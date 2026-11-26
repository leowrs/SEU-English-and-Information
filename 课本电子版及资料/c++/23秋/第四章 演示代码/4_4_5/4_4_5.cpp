#include <iostream>
using namespace std;
void  swap(int a, int b) //定义swap函数，a,b 是形参   
{ 
        int t;
        t=b;   b=a;  a=t;
   cout<<"在函数swap中：形参a="<<a<<"\t b="<<b<<endl<<endl;
} 

void main( )
{    
	int a=3,b=5; 
    cout<<"a="<<a<<"\t b="<<b<<endl<<endl;
    swap(a,b);  //调用swap函数，a,b为实参
    cout<<"调用函数swap后，a="<<a<<"\t b="<<b<<endl;
} 



