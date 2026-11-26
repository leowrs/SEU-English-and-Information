#include<iostream>
using namespace std;
int main()
{
	int i_array[6]={1,2,3,4};
	i_array[4]=i_array[1]+i_array[3];
		
	cout<<i_array[4]<<'\t'<<sizeof(i_array)<<'\t'<<i_array[5]<<'\n';
	return 1;
}
