// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
int main(){
	int a[10][10] = { {1} };
	cout << '\t' << a[0][0] << endl;
	for (int i=1; i <= 9 ; i++) {
		int n = 0;
		for (int j=0; j <= i; j++) {
			if (j == 0)
				a[i][j] = a[i - 1][j];
			else a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
			cout << '\t' << a[i][j];
			if (n++ == i)
				cout << endl;
		}
	}
	return 0;
}
