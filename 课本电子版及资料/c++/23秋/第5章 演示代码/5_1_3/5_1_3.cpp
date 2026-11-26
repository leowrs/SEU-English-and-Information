#include<iostream>
#include<cstdlib>
using namespace std;

const int SIZE=15;
int main()
{
    int arr[SIZE], i,high,low;
    for (i=0; i<SIZE; i++) 
	  arr[i]=rand()%100;
    cout << "Here are the " <<SIZE<<" random numbers :"<<endl;
    for (i=0; i<SIZE; i++)  
	{
		cout<<arr[i]<<"\t";
		if (i%5==4)
			cout<<endl;
	}
	cout<<endl;	
///*
    high=arr[0]; 
    low=arr[0];
    for(i=1;i<SIZE;i++)
    {
	if(arr[i]>high)   high=arr[i];
	if(arr[i]<low)   low=arr[i];    
    }
    cout<<"highest value is "<<high<<endl;
    cout<<"lowest value is "<<low<<endl<<endl;   
	//*/
    return 0;
}
