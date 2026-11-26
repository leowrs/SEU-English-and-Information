#include <iostream>
using namespace std;
int main()
{
int i,fibon[10]={0,1,1,2,3,5,8,13,21,34},*pfib1,*pfib2;
pfib1 = pfib2 = fibon; //也可以用pfib1=pfib2=&fibon[0]

cout<<"1、使用数组显示斐波那契数列"<<endl;
for(i=0; i<10; i++)
	cout<<fibon[i]<<'\t'<<pfib1[i]<<endl;

cout<<"2、使用指针显示斐波那契数列"<<endl;
for(i=0; i<10; i++)
	cout<<*(fibon+i)<<'\t'<<*pfib2++<<endl;
//注意：fibon++是错误的，而pfib2++是正确的

cout<<"3、显示指针相减,应为数组长度:";
cout<<pfib2-pfib1<<endl<<endl; //pfib2已指向数组末尾,输出元素个数
return 0;
}
