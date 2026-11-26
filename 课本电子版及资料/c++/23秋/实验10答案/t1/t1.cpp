#include <iostream>
using namespace std;
class Complex  //定义Complex类
{
public:
     Complex(double r=0,double i=0){  real=r;imag=i;  }
     Complex operator-= ( Complex c); //成员函数重载-=
	 friend Complex operator*= (Complex & c1, Complex c2);//  友元函数重载*=，这里第一个形参必须是引用
	 void display( );    //声明输出函数
 private:
     double real;   //实部
     double imag;  //虚部
};

void main( )
{
       Complex c1(3,3),c2(1),c3(1,1),c4(1,2);
	   cout<<"1、已有的两个复数："<<endl;
       cout<<"c1=";           c1.display( );     //输出c1的值
       cout<<"c2=";           c2.display( );    //输出c2的值
       c1-=c2;      //-=运算符的重载

	   cout<<endl<<"运行c1-=c2后,c1的值为：";  
	   c1.display( );  //输出c1的值
	   cout << endl << endl;
	   cout << "2、已有的两个复数：" << endl;
	   cout << "c3=";           c3.display();     //输出c1的值
	   cout << "c4=";           c4.display();    //输出c2的值
	  cout<<endl<<"运行c4*=c3后,c4的值：";
	  c4*=c3;
	  c4.display();
	  cout << endl;
	  system("pause");
}



Complex Complex::operator-=(  Complex  c) 
{
       real -= c.real;
       imag -=  c.imag; 
       return Complex(real,imag);
}    

Complex operator*= (Complex & c1,Complex c2)  
{
	double new_real = c1.real * c2.real - c1.imag * c2.imag;
	double new_imag = c1.real * c2.imag + c1.imag * c2.real;
	c1.real = new_real;
	c1.imag = new_imag;
	return c1;
}

void Complex::display( )   //定义输出函数
{ 
       cout<<"("<<real<<","<<imag<<"i)"<<endl;
}

 
  