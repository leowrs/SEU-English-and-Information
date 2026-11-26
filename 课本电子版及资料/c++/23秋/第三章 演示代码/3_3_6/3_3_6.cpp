#include <iostream>
using namespace std;
int x=1;
void  fun(int );
void main()
{
     int a=3;
     fun(a);
     x+=a++;
     cout<<x<<endl;
}

void fun(int a)
{
 	int x=5;  // ÐÐa
    x+=++a;
	a = a+3;
    cout<<x<<endl;
}
