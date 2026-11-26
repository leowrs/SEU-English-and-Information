#include <iostream>
using namespace std;

void main()
{
	char str1[] = {'P','r','o','g','r','a','m','\0'}; 
//如果要使用字符串函数对str1进行计算，就必须在最后加个串结束符
	cout<<"str1="<<str1<<endl;
	cout<<"strlen(str1)="<<strlen(str1)<<endl;
	cout<<"sizeof(str1)="<<sizeof(str1)<<endl<<endl;

 	char str2[] = "Program";
	cout<<"str2="<<str2<<endl;
	cout<<"strlen(str2)="<<strlen(str2)<<endl;
	cout<<"sizeof(str2)="<<sizeof(str2)<<endl<<endl;

}