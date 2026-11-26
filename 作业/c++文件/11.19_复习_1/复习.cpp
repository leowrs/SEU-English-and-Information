// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
using namespace std;
void inn(int a[]);
int main()
{
	int a[4];
	bool n = 1;
	inn(a);
	do
	{
		if (a[1] == a[2] || a[1] == a[3] || a[2] == a[3])
		{
			cout << "请输入三头猪的体重各不相同"<<endl;
			inn(a);
		}
		else n = 0;
	} while (n);
	if (a[1] > a[2])
	{
		if (a[1] > a[3])
			cout << "最重的猪是第一头";
		else cout << "最重的猪是第三头";
	}
	else if (a[2] > a[3])
		cout << "最重的猪是第二头";
	else cout << "最重的猪是第三头";
	cout << endl;
	system("pause");
	return 0;
}
void inn(int a[])
{
	for (int n = 1; n < 4; n++)
	{
		cout << "请输入第" << n << "只小猪的体重：";
		cin >> a[n];
	}
}
