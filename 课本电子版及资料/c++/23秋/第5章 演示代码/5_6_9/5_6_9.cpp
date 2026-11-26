#include <iostream>
#include <string>
using namespace std;

void main()
{
	string s1("12345  C");  //s1初始化
	string s2,s3,s4("ab");            // s2,s3是空串

 	s2="0hello";    //对s1进行赋值
	s3=s1+s2;     // 合并s1，s2
 	cout<<"s2="<<s2<<endl;
 	cout<<"s3="<<s3<<endl;
	
	s1=s4;  //就是用s4覆盖s1
	cout<<s1<<endl;
 

 
}
 