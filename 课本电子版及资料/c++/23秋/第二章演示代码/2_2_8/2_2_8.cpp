#include <iostream>
using namespace std;

void main(){
	char ch;

	cout<<"输入字符：";
	cin>>ch;

	cout<<"switch语句的输出为："<<endl;
	switch(ch)
	{
	case 'a': cout<<'a'<<endl;   
	case 'b':cout<<'b'<<'\t'; cout<<"hello"<<endl;  
		  //对于case中的多个语句不需要加大刮号
	case 'c':cout<<'c'<<endl; 
	case 'd':cout<<'d'<<endl; break;
	case 'e':cout<<'e'<<endl;
	default: cout<<"default!"<<endl<<endl;
	}
}
// input:   b  ， h
