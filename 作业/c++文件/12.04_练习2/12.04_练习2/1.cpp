// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
void swao(int& a, int& b)
{
	int t;
	t = a; a = b; b = t;
}
void main() {
	int i = 3, j = 5;
	swap(i, j);
	cout << "i=" << i << "j=" << j;
}