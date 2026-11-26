#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Rectangle
{
private:
	double left,bottom,right,top ;  //左下角，右上角
public:
	Rectangle(double l=0,double b=0,double r=0,double t=0)
	{left = l; bottom = b; right = r; top = t;}  // 构造函数
	//~Rectangle(){};  //析构函数


//接口函数，通过调用下面的四个函数，可以返回对象的私有数据
    //注：普通函数会用到这些接口函数
	double getLeft(){return left;}
	double getBottom(){return bottom;}
	double getRight(){return right;}
	double getTop(){return top;}

// 成员函数，可以直接使用对象的私有数据
	double Area(){return fabs((right-left)*(top-bottom));}
	double Perimeter(){ return 2*(fabs(right-left)+fabs(top-bottom));}
//  此处最好是加个绝对值函数
// 输出函数
	void show()
	{ cout<<"left -bottom:"<<setw(8)<<left<<setw(8)<< bottom<<endl;
	  cout<<"right-   top:"<<setw(8)<<right<<setw(8)<< top <<endl;}
};

// 普通函数：计算矩形对象的面积，
double Area(Rectangle r)
{
	double right = r.getRight();//调研对象的接口函数
	double bottom = r.getBottom();
	double left = r.getLeft();
	double top = r.getTop();
	return fabs((right-left)*(top-bottom));
}

// 普通函数：计算矩形对象的周长
double Perimeter(Rectangle r)
{
	double right = r.getRight();
	double bottom = r.getBottom();
	double left = r.getLeft();
	double top = r.getTop();
	return 2*(fabs(right-left)+fabs(top-bottom));
}

void main()
{
	Rectangle r1(10,20,40,50);
	r1.show();
	
	cout<<"1、通过成员函数来计算面积和周长："<<endl;
	cout<<"面积: "<<r1.Area()<<endl;
	cout<<"周长: "<<r1.Perimeter()<<endl;

	cout<<endl<<"2、通过普通函数来计算面积和周长："<<endl;
	cout<<"面积："<<Area(r1)<<endl;
	cout<<"周长："<<Perimeter(r1)<<endl;
}













