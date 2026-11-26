#include <iostream>
using namespace std;

class E
{
private: 
	int x,y;
public:
	E(int a=0, int b=0){x=a; y=b;}
	E(){}
	void P(){ cout<<x<<'\t'<<y<<endl;}
};

void main()
{
 	E e;
}
