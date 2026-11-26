#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void maxmin(int [], int);
const int SIZE=15;
int main()
{
	srand((unsigned)time(NULL));
	cout<<time(0)<<endl;  // 从1970年1月1日0时0分0秒到当下的秒数
    int arr[SIZE], i;
    for (i=0;i<SIZE;i++) 
	  arr[i]=rand()%100;
    cout << "Here are the " <<SIZE <<" random numbers :"<<endl;
    for (i=0;i<SIZE;i++)  
	{
		cout<<arr[i]<<'\t';
		if(i%5==4) cout<<endl;
	}
    cout<<endl;   
    maxmin(arr,SIZE);
    return 0;
}

void maxmin(int ARR[], int n)
{
    int high,low;
    high=ARR[0]; 
    low=ARR[0];
    for(int i=1; i<n; i++)
    {
		if (ARR[i]>high)   high=ARR[i];
		if (ARR[i]<low)   low=ARR[i];    
    }
    cout<<"highest value is "<<high<<endl;
    cout<<"lowest value is "<<low<<endl;
}

