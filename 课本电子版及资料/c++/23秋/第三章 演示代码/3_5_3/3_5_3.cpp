#include<iostream>
using namespace std;
int n=100;
void main()
{
	int i=200,j=300;
	cout<<"在main函数中：n="<< n<<"\t i="<<i<<"\t j="<<j<<endl<<endl; 
	{   //内部块
	    int i=500,j=600,n;
	    n=i+j;
	    cout<<"在内部块中：n="<< n<<"\t i="<<i<<"\t j="<<j<<endl<<endl;
	    cout<<"在内部块中调用::n="<<::n<<endl<<endl;	
	}
	n=i+j;		
	cout<<"在main函数中：n="<< n<<"\t i="<<i<<"\t j="<<j<<endl<<endl; 
}
