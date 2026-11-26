#include <iostream>
using namespace std;

void main(){
	char ch;
	cout<<"输入字符：";
	cin>>ch;

	cout<<"switch语句的输出为：";
	switch(ch){
	case'a': cout<<'a'<<'\t';  
	case 'b':cout<<'b'<<'\t';
	default: cout<<endl;
	}


}
 