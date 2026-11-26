#include <iostream>
using namespace std;

void main(){
	double x;
	int i=1;  // 统计循环次数
	cout<<"input:";
 	cin>>x;

	while(x)  //  （）里面不能空
	{
		cout<<"循环"<<i++<<"次"<<endl;
		x = 0;
	}

}

// input: x= 0.00001，数值转换为布尔值
// input  x=0， 表示布尔值为false
