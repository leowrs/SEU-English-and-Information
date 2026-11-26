#include <iostream>
using namespace std;
void main( )
{ 
	bool  test=true; 
    int i=0;    
    while(test)
	{
		i++;   
		cout<<i<<"  ";
		if(i>=10)  
			break; 
	}
	cout<<endl;
}
