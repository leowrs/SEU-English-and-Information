// 运算符重载
#include <iostream>
using namespace std;
class Complex  //定义Complex类
{
public:
     Complex(double r=0,double i=0)
	 {  
		 this->real=r;  
		 imag=i;  
	 }
     void display() { cout << real << "," << imag << endl; }    //声明输出函数
 private:
     double real;   //实部
     double imag;  //虚部
};

int main( )
{
       Complex c1(3,4);
	   Complex c2; 
       c1.display();
       c2.display();
  
       return 0;
}

 