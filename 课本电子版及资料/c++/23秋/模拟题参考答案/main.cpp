#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;  // 完善代码1：完善头文件

const double epsilon = 1e-10;  // 改错1。原错误是：double epsilon = 1e-10;

int main()
{
	double x0,x1;
	int n=0;//用来统计循环次数的
	ofstream file;             //改错2。原错误是：ifstream file;
	file.open("my.txt");

	cout << "请输入初始值（范围是(9,11)）：";
	cin >> x1;
	while ( (x1 <= 9) || (x1>=11))     //改错3。原错误是： 9<x1<11
	{
		cout << "提示：输入错误，请输入初始值（范围是(9,11)）：" ;       //完善代码2
		cin >> x1;
	}


	file << "方程迭代过程中的近似解为：" << endl;
	do
	{
		x0=x1;
		x1=(x0*x0-10*(x0*sin(x0)+cos(x0)))/(2*x0-10*sin(x0));  //完善代码3
		n++;
		if (n <= 5)
		{
			file << x1 <<"\t";               //完善代码4
			if (n % 2 == 0)                  //完善代码5
				file << endl;
		}
	}while(fabs(x1-x0)>epsilon  );        //改错4。原错误是：少写了分号


	cout<<"方程的一个近似根为："<<x1<<endl;

	file.close();   //改错5。原错误是：close();
	return 0;
}