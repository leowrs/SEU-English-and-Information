#include <iostream>
using namespace std;

void  main( ) 
{
	int i=1,sum=0;
 

	while (i<=100) 		
	{ 
 		sum=sum+i;     
 		i++;
	}
//上面的{}里面的语句 等价于 sum = sum + i++;
	cout<<"sum="<<sum<<endl;
}
