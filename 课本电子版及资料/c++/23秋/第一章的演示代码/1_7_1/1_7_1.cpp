#include <iostream>
using namespace std;

void main()
{
	int a[6]={1,2,3,4,5,6};
	cout<<endl<<"下标越界:a[6]="<<a[6]<<endl<<endl; 
	//编译程序不会检查数组的下标越界
}