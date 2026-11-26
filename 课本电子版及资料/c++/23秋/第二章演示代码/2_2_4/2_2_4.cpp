#include <iostream>
using namespace std;

void main()
{
	int a=4, b=5, c=6; 
	 
    cout<<"第1种情况：带大括号，输出为：";
	if( a>c ) 
		{if(c>b) cout<<c<<endl;}
	else 
		cout<<a<<endl;
 //  /*
	cout<<"第2种情况：不带大括号，输出为："<<endl;
	if( a>c ) 
	if(c>b) cout<<c<<endl;
	else 
		cout<<a<<endl;
//*///

}
/*说明：由于else要与最近的if进行配对，所以第2中情况等价于 
	if( a>c ) 
	{if(c>b) cout<<c<<endl;
	  else 
		cout<<a<<endl;}
		*/