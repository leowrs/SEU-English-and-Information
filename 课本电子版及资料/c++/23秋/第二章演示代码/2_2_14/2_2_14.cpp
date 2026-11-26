#include <iostream>
using namespace std;

void main(){
	char ch;
	cout<<"输入字符：";
	cin>>ch;

	cout<<"switch语句的输出为：";
	switch(ch){
	case'a':    cout<<'a'<<'\t';  
 	case 97:    cout<<'b'<<'\t';
	case 90+7:  cout<<'c'<<'\t';
	case 'c'-2: cout<<'d'<<'\t';
	default: cout<<endl;
	}


}
 