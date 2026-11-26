// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
int main()
{
	int n,i,a,p;
	cout<<"请输入行数n:";
	cin>>n;
	cout<<"第一种图形如下："<<endl;
	if(n%2==1){
		for(i=1;i<=n;i++){
			for(a=1;a<=i;a++)
				cout<<'*';
			cout<<endl;}}
	cout<<endl<<"第二种图案:"<<endl;
	if(n%2==1){
		for(p=1;p<=n;p+=2){
			for(a=(n-p)/2;a>0;a--)
				cout<<' ';
			for(a=1;a<=p;a++)
				cout<<'*';
				cout<<endl;}
		for(p=n-2;p>0;p-=2){
			for(a=(n-p)/2;a>0;a--)
				cout<<' ';
		for(a=p;a>0;a--)
				cout<<'*';
		cout<<endl;}}	
	system("pause");
	return 0;
}