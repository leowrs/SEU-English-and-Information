//对半查找，迭代算法

#include <iostream>
using namespace std;
int BinarySearch(int [], int , int  );

void main()
{
	int arr[11]={2,3,5,8,10,15,16,18,24,28,30};
	int value,result;
	cout<<"请输入需要查找的整数：";
	cin>>value;

	result=BinarySearch(arr,sizeof(arr)/sizeof(arr[0]),value);
	if(-1!=result)
		cout<<"找到了，在数组中的下标是："<<result<<endl;
	else
		cout<<"没有找到！"<<endl;
}

int BinarySearch(int arr[], int size, int value)
{
	int mid, low=0,high=size-1;
	while(low<=high)
	{
		mid =(low+high)/2;
		if(value<arr[mid])
			high = mid - 1;
		else if(value>arr[mid])
			low = mid + 1;
		else return mid;
	}
	if(arr[mid] != value)
		return -1;
}