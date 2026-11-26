#include <iostream>
using namespace std;
void main( )
{
	int i,j ;
	cout<<"九九乘法表："<<endl;
	i=1;  //外循环开始时，注意i必须是1
	while (i<=9)   
    {  //外循环
		j=1;  	 //内循环开始时，j必须是1
		while (j<=i)
        {  //内循环
		    cout<<i<<"*"<<j<<"="<<i*j<<"   ";
            j++;   //当j超过i时，内循环就结束
         }
         cout<<endl;
         i++;    //当i超过9时，外循环就结束
     }
	   cout<<endl;
}
