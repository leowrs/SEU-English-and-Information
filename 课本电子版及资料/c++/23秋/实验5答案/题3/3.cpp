/* 《C++程序设计》P67的题2.9。
*/
#include <iostream>

using namespace std;

int main()
{
	int arr[100],i=0,sum=0,pcount=0,ncount=0;
	// i:计数； sum：求和；  pcount：正数个数； ncount：负数个数
	cout<<"请输入一组非0的整数，以输入0为结束标志:"<<endl;
	cin>>arr[0];
	while(arr[i]!=0)
	{
		sum+=arr[i];  //求和
		if(arr[i]>0) 
			pcount++;
		else 
			ncount++;
		i++;
		cin>>arr[i];
	}

	if(i==0) 
		cout<<"输入了0个整数"<<endl;
	else
	{
		cout<<"平均值="<< (1.0*sum/i)<<endl;  //注意这里为什么要乘以1.0
		cout<<"正数的个数="<<pcount<<endl;
		cout<<"负数的个数="<<ncount<<endl;
	}

	return 0;
}