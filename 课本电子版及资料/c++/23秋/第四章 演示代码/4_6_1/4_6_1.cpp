// Complex类的友元函数
#include <iostream>
using namespace std;
class Complex  //定义Complex类
{
public:
     Complex( ){real=0;imag=0;}   //定义默认构造函数
     Complex(double r,double i){  real=r;imag=i;  }
     friend Complex operator+ (double &c1,Complex &c2);  //友元函数的声明：实数加复数
     void display( );    //声明输出函数
 private:
     double real;   //实部
     double imag;  //虚部
};

int main( )
{
	double d1=3.0;
       Complex c2(5,-10),c3; 
       c3=d1+c2;      //+运算符的重载
       cout<<"d1="<<d1<<endl;     //输出c1的值
       cout<<"c2=";           c2.display( );    //输出c2的值
       cout<<"c1+c2=";     c3.display( );  //输出c3的值
       return 0;
}

Complex operator+(double &c1, Complex &c2) 
{
       return Complex(c1+c2.real,c2.imag);
}    

void Complex::display( )   //定义输出函数
{ 
       cout<<"("<<real<<","<<imag<<"i)"<<endl;
}
