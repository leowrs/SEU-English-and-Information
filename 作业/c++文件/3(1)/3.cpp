// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
int main() {
	int a[11], p = 0, m = 0, i=0;
	float sum = 0;
	cout << "请输入一组非0的整数，以输入0为结束标志：" << endl;
	cin >> a[0];
	while(a[i]!=0)
	{
		if (a[i] > 0)
			m++;
		else p++;
		sum += a[i];
		i++;
		cin >> a[i];
	}
	cout << "平均数=" << sum / i << endl;
	cout << "正整数的个数=" << m << endl;
	cout << "负整数的个数=" << p << endl;
	system("pause");
	return 0;
}