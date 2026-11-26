#include <iostream>
using namespace std;
void main( )
{ 
	int i=0,sum=0;
	while(i<4)
	{
	    i++;
	    if(i==2)
//	       break;  
		continue;
	    sum+=i;
	}
	cout<<"sum="<<sum<<endl;

}
