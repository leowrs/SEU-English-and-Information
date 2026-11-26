#include <iostream>
using namespace std;
void output(int a[]);//输出数组a中的所有元素。
void main()
{
	int a[]={1,2,3,4,5,6},*p1,*p2,temp;
	for(p1=a,p2=&a[5];p1<p2;p1++,p2--)  //两个指针进行比较
	{
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}
	output(a);
}


void output(int a[])
{ 
	for(int i=0;i<6;i++)
      cout<<a[i]<<"  ";
    cout<<endl;
}