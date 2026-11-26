#include <iostream>
using namespace std;

int main()
{
	int price,level; 
	
	cout<<"输入price: " ;
	cin>>price;

	if( price>1000 ) 
		level=1;
	else if(price>700)  // else 和 if 之间有空格
		level=2;
	else if(price>300)
		level=3;
	else 
		level=0;
 
	cout<<"level= "<<level<<endl;
	return 0;

// input 1 :  price = 1200,800,600,200，验证下程序执行的结果


}
