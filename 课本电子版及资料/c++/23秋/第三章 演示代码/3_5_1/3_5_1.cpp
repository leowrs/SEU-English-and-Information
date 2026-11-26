#include <iostream>
using namespace std;

void main(){
	int a, b;
	cout<<"输入两个整数："<<endl;
	cin>>a>>b;
	cout<<"a="<<a<<"\t b="<<b<<endl;

	if(b>a){
		int t;
		t=a; a=b; b=t;
	}
	cout<<"a="<<a<<"\t b="<<b<<endl;
//	cout<<"t="<<t<<endl;   // 该语句出错，为什么？

/*	 
	for(int i=1; i<4;i++)   //for后面的小刮号中定义了 i，请问i的作用域
	{
		int sum=0;           //for后面的大刮号中定义了sum，请问sum的作用域
		sum = sum +i ;
	}

	cout<<"i="<<i<<endl;
	cout<<"sum="<<sum<<endl;
//*/

}