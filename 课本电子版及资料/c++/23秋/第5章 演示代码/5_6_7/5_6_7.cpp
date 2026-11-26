#include <iostream>
#include <string>
using namespace std;

void main()
{
	char s1[20]="book";
	char s2[]="pen";
 
 	cout<<"strcmp(s1,s2)的结果是："<<strcmp(s1,s2)<<endl<<endl;

	cout<<"s1>s2的结果是："<<(s1>s2)<<endl;
	cout<<"s1 address:"<<(void*)s1<<endl;
	cout<<"s2 address:"<<(void*)s2<<endl<<endl;

 
}
 