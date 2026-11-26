#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

const int SIZE=3;
void fun(int [], int);

int main()
{
    int arr[SIZE];
	int i;

    cout << "数组arr是实参："<<endl;
    for (i=0;i<SIZE;i++)  
          cout<<"arr["<<i<<"]的内存地址："<<&arr[i]<<endl;
    cout<<endl;   

    fun(arr,SIZE);
    return 0;
}

void fun(int ARR[], int n)
{
	int i;
	cout << "数组ARR是形参："<<endl;
    for (i=0;i<SIZE;i++)  
          cout<<"ARR["<<i<<"]的内存地址："<<&ARR[i]<<endl;
    cout<<endl;  

}

