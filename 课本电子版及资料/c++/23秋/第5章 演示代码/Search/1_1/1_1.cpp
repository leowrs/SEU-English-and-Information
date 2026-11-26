#include <iostream>
using namespace std;

int Search(int arr[],int arr_size,int value);

void main()
{
	int arr[5]={23,34,50,199,232};
	int value,result;

	cout<<"请输入整数：";
	cin>>value;
	result = Search(arr,sizeof(arr)/sizeof(arr[0]),value);
	if(-1 != result)
		cout<<"找到了："<<value<<"坐在的数组下标是"<<result<<endl;
	else
		cout<<"没有找到"<<endl;
}


int Search(int arr[],int arr_size,int value)
{
	int i;
	for(i=0;i<arr_size;i++)
		if(arr[i]==value)
			return i;
 
	return -1;
}