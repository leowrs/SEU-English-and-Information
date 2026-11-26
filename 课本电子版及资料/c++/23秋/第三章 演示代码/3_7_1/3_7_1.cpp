#include <iostream>
using namespace std;
int fact(int k){
	int y;
	if(k==1)
		y=1;
	else	
	{
		cout<<"计算k="<<k<<"：fact("<<k<<")="<<k<<"*fact("<<k-1<<")"<<endl;
		y=k*fact(k-1);	
	}
	cout<<"结束调用fact("<<k<<"),并返回该值："<<y<<endl;
	return y;
}
void main(){
	int k=4;
	cout<<endl<<"fact(4)="<<k<<"!="<<fact(k)<<endl<<endl;
}
