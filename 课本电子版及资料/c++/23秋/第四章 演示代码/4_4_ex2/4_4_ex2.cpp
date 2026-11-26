#include <iostream>
using namespace std;

class A
{
public:
	A(int x){cout<<x<<endl;}
	~A(){cout<<"Îö¹¹A"<<endl;}
};

	
class B
{
public:
	B(int x){cout<<x<<endl;}
		~B(){cout<<"Îö¹¹B"<<endl;}
};

class C
{
	B B1;
	A A1; 
public:
	C(int a=2, int b=2):A1(a),B1(b)
	{cout<<a+b<<endl;}
	~C(){cout<<"Îö¹¹C"<<endl;}
};

void main()
{
	C C1(1);
}