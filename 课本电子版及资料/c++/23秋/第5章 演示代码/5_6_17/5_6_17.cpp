#include <iostream>
#include <string>
using namespace std;

void main()
{
	cout<<strlen("ab")<<endl;

	char s[]="ab";
	cout<<strlen(s)<<endl;

	char arr[][4] = {"ab","cd"};
	cout<<strlen(arr[1])<<endl;
 
}