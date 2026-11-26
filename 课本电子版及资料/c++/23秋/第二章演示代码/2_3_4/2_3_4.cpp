#include  <iostream>
using namespace std;

 void main()
{
        int f1=0,f2=1,f3;
        int m=20;  //cin>>m;
        cout<<'\t'<<f1<<'\t'<<f2;
        for(int n=3;n<=m;n++)
	{
		f3=f1+f2;
		cout<<'\t'<<f3;
		if(n%5==0)  cout<<endl;	//控制每行5个数据
		f1=f2; 
		f2=f3;
	}
}
