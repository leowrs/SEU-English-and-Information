// Original Author: GitHub @leowrs (https://github.com/leowrs)

  // 完善代码1：完善头文件，begin （完善代码请填写在begin后面，end之前）
#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

//完善头文件，end

const  double epsilon = 1e-10;     //错误1

int main()
{
	double x0,x1;
	int n=0;//用来统计循环次数的
	ofstream file;               //错误2
	file.open("my.txt");

	cout << "请输入初始值（范围是(9,11)）：";
	cin >> x1;
	while (9>=x1||x1>=11)                         //错误3
	{
		 //完善代码2：完善代码:合法性检查，begin
		cout << "提示：输入错误，请输入初始值（范围是(9,11)）：";
		cin >> x1;
		//完善代码:合法性检查，end
	}


	file << "方程迭代过程中的近似解为：" << endl;
	do
	{
		//完善代码3：完善代码：迭代过程，begin
		x0 = x1;
		x1 = (x1 * x1 - 10 * (x1 * sin(x1) + cos(x1))) / (2 * x1 - 10 * sin(x1));
		//完善代码：迭代过程，end
		n++;
		if (n <= 5)
		{
	                   //完善代码4：完善代码：把迭代过程中产生的根保存到my.txt中，begin
			file << x1 << '\t';
	                   //完善代码：把迭代过程中产生的根保存到my.txt中，end

			
			//完善5：完善代码：每两个根就要换行，begin
			if (n % 2 == 0) file << endl;
			//完善代码：每两个根就要换行，end
		}
	} while (fabs(x1 - x0) > epsilon);                             //错误4


	cout<<"方程的一个近似根为："<<x1<<endl;

	file.close();  //                        //错误5
	return 0;
}