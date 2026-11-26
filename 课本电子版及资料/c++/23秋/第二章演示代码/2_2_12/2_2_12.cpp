#include <iostream>
using namespace std;
void main()
{
	int x,y;
	cin>>x>>y;
	if(x>y)
	  x=y; y=x;   //{ x=y; y=x; }
	else
 	     x++;
	cout<<x<<y<<endl;
}
