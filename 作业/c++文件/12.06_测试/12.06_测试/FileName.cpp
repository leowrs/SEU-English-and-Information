// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include <iostream>
#include <cmath>
using namespace std;

//此处可以添加你所需要的函数
int MaxCommonFactor(int a, int b)
{
	int temp;
	b > 0 ? b = b : b = -b;
	a > 0 ? a = a : a = -a;
	if (a > b)
	{
		temp = a;
		a = b;
		b = temp;
	}
	while (true)
		if (a != b) a > b ? a -= b : b -= a;
		else return a;
}
class fraction    //分数类
{
	int above; //分子
	int below; //分母
public:
	fraction(int a = 0, int b = 1);
	fraction(fraction&);    // 复制构造函数的函数声明。
	fraction add(fraction); // 两分数相加，相加后的结果作为函数返回值
	fraction mul(fraction); // 两分数相乘，相乘后的结果作为函数返回值
	fraction reciprocal(); //  求倒数，这个函数的定义已经给出，可以作为参考
	bool equal(fraction);  // 判断是否等于的运算
	void display(); //显示分数
};


void main()   //main函数里面的代码不要修改
{
	fraction f1(2, 8), f2(2, -5), f3 = f2;

	cout << "1、测试四则运算" << endl;
	cout << "两个操作数分别是" << endl;
	f1.display();
	f2.display();
	cout << "运算结果分别是：" << endl;
	cout << "加法：";     f1.add(f2).display();     // 测试加法(注意分子分母要约分，即2/8要化简为1/4)
	cout << "乘法：";     f1.mul(f2).display();     // 测试乘法
	//  也可以写成 f3 = f1.add(f2);  f3.display();

	fraction f4 = f2;
	cout << endl << "2、倒数运算：" << endl;
	cout << "原数为"; f4.display();
	cout << "倒数为"; f4.reciprocal().display();


	fraction f5(2, 8), f6(1, 4);
	cout << endl << "3、测试f5和f6是否相等，结果是（1表示成立，0表示不成立）" << endl;
	cout << "等于关系：" << f5.equal(f6) << endl;


}



fraction::fraction(int a, int b) //构造函数
{
	//补充代码1
	above = a / MaxCommonFactor(a, b) * (b / abs(b));
	below = b / MaxCommonFactor(a, b) * (b / abs(b));
}


fraction::fraction(fraction& fr)
{
	//补充代码2
	below = fr.below / MaxCommonFactor(fr.above, fr.below);
	above = fr.above / MaxCommonFactor(fr.above, fr.below);
}

fraction fraction::add(fraction fr)  // 两分数相加
{
	//补充代码3
	fr.above = fr.above * below + above * fr.below;
	fr.below = below * fr.below;
	return fr;
}


fraction fraction::mul(fraction fr)  // 两分数相乘
{
	//补充代码4
	fr.above = fr.above * above;
	fr.below = fr.below * below;
	return fr;
}

fraction fraction::reciprocal()  //求倒数
{
	if (above == 0)
	{
		cout << "错误，无法对0求倒数！" << endl;
		return NULL;
	}
	fraction temp;
	temp.above = below;
	temp.below = above;
	return temp;
}

bool fraction::equal(fraction fr)   // 等于运算
{
	//补充代码5
	if (fr.below * above == fr.above * below)
	{
		return true;
	}
	return false;
}

void fraction::display()
{
	//补充代码6
	cout << above << "/" << below;
}
