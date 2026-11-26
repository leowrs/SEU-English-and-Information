#include <iostream>
using namespace std;

void main( )
{ 
	int i,j,product;
    for(i=1;i<10;i++)   //外循环
    {
		for(j=1;j<=i;j++)   //内循环
	    {  
			product=i*j;
            cout<<i<<"*"<<j<<"="<<product<<"   ";
         } //内循环结束        
 
		 cout<<endl;
     } //外循环结束
 }	 
