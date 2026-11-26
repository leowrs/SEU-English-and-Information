#include <iostream>
using namespace std;
 

void main()
{
	int i,j;
	for( i=0; i < 10; i++)
		for(j=0;j<10; j++)
			if(i+j==4)
				goto label;
			//goto语句：控制程序从goto语句处直接转移到label处

	cout<<"Hello!"<<endl; //该语句不会被执行

	label: cout<<"goto语句调出循环"<<endl;
	cout<<"i="<<i<<"   j="<<j<<endl;
}