#include <iostream>
using namespace std;
static int count=0;  // count的功能是计数
void move(char source, char target)
{
	cout<<source<<"-->"<<target<<'\t';
}

void hanoi(int n, char source, char temp, char target)
{
	::count++;
	if(n==1)
		move(source,target);
	else
	{
		hanoi(n-1,source,target,temp);
		move(source,target);
		hanoi(n-1,temp,source,target);
	}
}

void main()
{
	int n;
	cout<<"输入盘子数量："<<endl;
	cin>>n;
	cout<<"具体操作："<<endl;
	hanoi(n,'A','B','C');
	cout<<endl;
	cout<<"操作次数："<<::count<<endl<<endl;
}