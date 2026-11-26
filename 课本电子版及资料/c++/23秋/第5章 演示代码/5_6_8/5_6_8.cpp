#include <iostream>
#include <string>
using namespace std;
void main()
{
	char s1[5]="";
	cout<<"strlen(s1)="<<strlen(s1)<<endl;
	cout<<"sizeof(s1)="<<sizeof(s1)<<endl<<endl;

	char c[20]="stringLength";
	cout<<"strlen(c)="<<strlen(c)<<endl<<endl;

	cout<<"strlen(\"students\")="<<strlen("students")<<endl<<endl;
	cout<<"strlen(教师)="<<strlen("教师")<<endl<<endl;

	char d[2]={'a','b'};
	cout<<strlen(d)<<endl; //错误结果
}