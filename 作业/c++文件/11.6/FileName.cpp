// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
int n = 100;
int main()
{
	int i = 1, sum = 0;
	while (i <= n) {
		sum += i;
		i++;
	}
	cout << "sum=" << sum << endl;
}
