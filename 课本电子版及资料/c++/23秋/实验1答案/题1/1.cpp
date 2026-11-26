#include<iostream>
using namespace std;
int max(int x,int y)
{
	if(x>=y)
		return x;
	else
		return y;
}
int main(void)
{
	int i=0,j=0;
	cout<<"输入i，j："<<endl;
	cin>>i>>j;
	cout<<"最大数是"<<max(i,j)<<endl;
	system("pause");
	return 0;
}
