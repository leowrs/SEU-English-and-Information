#include <iostream>
using namespace std;
void main( )
{ 
	int i,j;  
    for(i=1;i<4;i++)
	{
		cout<<"执行外循环第"<<i<<"次"<<endl;
		for(j=1;j<5;j++)
		{
			cout<<"执行内循环第"<<j<<"次"<<endl;
			break;
		}
		cout<<endl;
	}
}
