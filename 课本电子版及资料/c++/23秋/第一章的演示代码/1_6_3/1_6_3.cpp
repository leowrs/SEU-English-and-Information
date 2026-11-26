#include <iostream>
using namespace std;
int main( )
{
       int a,b;
       a=7;  
	   b=a++;
       cout<<"\t执行a=7;b=a++后，a值为"<<a<<",b值为"<<b<<endl;
      
	   a=7;    b=++a;
       cout<<"\t执行a=7;b=++a后，a值为"<<a<<",b值为"<<b<<endl; 

	   a=7;    b=a--;
	   cout<<"\t执行a=7;b=a--后，a值为"<<a<<",b值为"<<b<<endl;
	
	   a=7;   b=--a;  
	   cout<<"\t执行a=7;b=--a后，a值为"<<a<<",b值为"<<b<<endl;    
        
	   return 0;
}
