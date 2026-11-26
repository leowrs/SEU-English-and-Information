#include <iostream>
using namespace std;

class E
{
private: 
	int x,y;
public:
	E(int a, int b){x=a; y=b;}
	void P(){ cout<<x<<'\t'<<y<<endl;}
};

void main()
{
	E e;
}
