#include <iostream>
#include <string>
using namespace  std;
void main()
{
	char str1[20],str2[]="China";

	strcpy_s(str1,str2);  
	cout<<str1<<endl<<endl;
 
	char ss[90]="程序设计语言C++";
	strcpy_s(ss,"学生");  //ss中原来的字符串全没有了
	cout<<ss<<endl;

}