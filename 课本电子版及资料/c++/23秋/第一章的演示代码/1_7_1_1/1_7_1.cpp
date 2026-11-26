#include <iostream>
using namespace std;

void main()
{
	int a[6]={1,2,3,4,5,6};

	cout<<"sizeof(a)="<<sizeof(a)<<endl;
	cout<<"sizeof(a[0])="<<sizeof(a[0])<<endl;
	cout<<"sizeof(a)/sizeof(a[0])="<<sizeof(a)/sizeof(a[0])<<endl;

}