#include <iostream>
using namespace std;
void main()
{
	char str[6],str2[10];
	int i;

   // /* 整个字符串
	cout<<"（1）用cin来接受输入："; 
	cin>>str;  
	cout<<str<<endl;
//说明1：从第一个非空格字符开始接受，遇到空格、回车就会结束  
    // */
   cin.get();   // 吃掉回车
	cout<<"（2）input：";   
 	cin.getline(str2,10); 
//接受3个字符，最后一个存放\0； 可以接受空格。
	cout<<str2<<endl;
 
//*/

}
// 在“逐个字符输入输出”：可以输入有空格的字符串
// 在“整个字符串”：cin>>str 输入超过个数的字符串、输入空格/回车，看看结果。
//cin.get(str,4)中输入4个字符，看看接受几个