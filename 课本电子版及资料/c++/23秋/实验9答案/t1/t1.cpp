#include <iostream>
#include <cmath>
using namespace std;

//此处可以添加你所需要的函数
int GCD(int , int );  //求两个数的绝对值的最大公约数

class fraction
{
	int above; //分子
	int below; //分母
public:
	fraction(int a=0, int b=1);   
	fraction(fraction&);    // 复制构造函数的函数声明。
 	fraction add(fraction); // 两分数相加，相加后的结果作为函数返回值
 	fraction mul(fraction); // 两分数相乘，相乘后的结果作为函数返回值
 	fraction reciprocal(); //  求倒数

 	bool equal(fraction);  // 判断是否等于的运算
 	void display(); //显示分数

};


void main()
{
	fraction f1( 2,  8),f2( 2, -5),f3=f2;

	cout<<"1、测试四则运算"<<endl; 
	cout<<"两个操作数分别是"<<endl; 
	f1.display();
	f2.display();
    cout<<"运算结果分别是："<<endl;
	cout<<"加法：";     f1.add(f2).display();     // 测试加法(注意分子分母要约分，即2/8要化简为1/4)
   cout<<"乘法：";     f1.mul(f2).display();     // 测试乘法
//  也可以写成 f3 = f1.add(f2);  f3.display();

	fraction f4=f2;
	cout<<endl<<"2、倒数运算："<<endl;
	cout<<"原数为"; f4.display();
	cout<<"倒数为"; f4.reciprocal().display();

 
	fraction f5(2, 8),f6( 1,4);
	cout<<endl<<"3、测试f5和f6是否相等，结果是（1表示成立，0表示不成立）"<<endl;
	cout<<"等于关系："<<f5.equal(f6)<<endl;
 
}


int GCD(int n1, int n2) //求两个数的绝对值的最大公约数
{
	int num1 = fabs(n1);
	int num2 = fabs(n2);
	int	resd = num1 % num2;   
	while(resd)
	{
		num1 = num2;
		num2 = resd;
		resd = num1 % num2;
	}
	return num2;
}

 fraction::fraction(int a , int b ) //构造函数
 {above = a; below = b;}

 //在此处给出复制构造函数的函数定义
 fraction::fraction(fraction& fr)
 {
	 above = fr.above; below = fr.below;
 }

fraction fraction::add(fraction fr)  // 两分数相加
{
 
	int new_below = below * fr.below;
	int new_above = above * fr.below + below * fr.above;
	int factor = GCD(new_below, new_above);
	fraction temp(new_above/factor,new_below/factor );
	return temp;
}

 
fraction fraction::mul(fraction fr)  // 两分数相乘
{
	int new_below = below * fr.below;
	int new_above = above * fr.above;
	int factor = GCD(new_below, new_above);
	fraction temp(new_above / factor, new_below / factor);
	return temp;
}

 

fraction fraction::reciprocal()  //求倒数
{
	if(above==0)
	{	cout<<"错误，无法对0求倒数！"<<endl;
		return NULL;
	}
	fraction temp;
	temp.above = below;
	temp.below = above;
    return temp;
}

bool fraction::equal(fraction fr)   // 等于运算
{
 
	int result = above* fr.below - below * fr.above;

	if(result==0)
		return true;
	else 
		return false;
}
void fraction::display()
{
	int factor = GCD(below, above);
	below = below / factor;
	above = above / factor;
	if(below==1)
		cout<<" "<<above<<endl;
	else if(below*above<0)
		cout<<"-"<<fabs(above)<<"/"<<fabs(below)<<endl;
	else
		cout<<" "<<fabs(above)<<"/"<<fabs(below)<<endl;
 
}

 
