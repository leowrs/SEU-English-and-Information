#include <iostream>
using namespace std;

void main()
{
	char s1[4] = "abc";
	cout<<s1<<endl;
		
	char s2[3] = {'a','b','c'};
	cout<<s2<<endl;

	char s3[4] = {'a','b','c'};
	cout<<s3<<endl;

	char s4[4] = {'a','b','c','\0'};
	cout<<s4<<endl;

	char s5[4] = {'a','b','c',0};
	cout<<s5<<endl;

	char ss[10]={'a',0,'b','\0'}; //问题：输出是什么，为什么？
 	cout<<ss<<endl;

}