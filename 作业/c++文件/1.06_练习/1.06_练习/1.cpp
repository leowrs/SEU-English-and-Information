// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
void main(){
	char arr[6] = { 1,2,3 };
	char* q = arr;
	q++;
	int* p = (int*)q;
	cout << *p++ << endl;
	cout << *p;
}