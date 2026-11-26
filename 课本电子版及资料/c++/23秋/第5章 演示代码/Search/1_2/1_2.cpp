//对半查找，递归算法

#include <iostream>
using namespace std;
int BinarySearch(int [], int , int , int );
void main()
{
	int arr[11]={2,3,5,8,10,15,16,18,24,28,30};
	int value,result;
	cout<<"请输入需要查找的整数：";
	cin>>value;

	result=BinarySearch(arr,0,sizeof(arr)/sizeof(arr[0])-1,value);
	if(-1!=result)
		cout<<"找到了，下标是"<<result<<endl;
	else
		cout<<"没有找到！"<<endl;
}

int BinarySearch(int arr[], int low, int high, int value)
{
	int mid=-1;
	if(low<=high)
	{
		mid=(low+high)/2;
		if(arr[mid]<value)
			mid = BinarySearch(arr,mid+1,high,value);
		if(arr[mid]>value)
			mid = BinarySearch(arr,low,mid-1,value);
	}
	return mid;
}