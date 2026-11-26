#include <iostream> //类模板应用举例
#include <cstdlib>
using namespace std;
class Student   //定义结构体类型Student
{
public:
	int id;     //学号
	float gpa;  //平均分  
	Student(int i=0,float g=0):id(i), gpa(g) { }
};

template<class T>  //类模板，实现对任意类型数据进行存取
class Store
{
       T item;   //存放任意类型数据
	int Valued;  //标记item是否已被存入内容
  public:
        Store();  //默认形式的构造函数
	T GetElem(); //提取数据函数
	void PutElem(T x); //存入数据函数
};

template<class T>
 Store<T>::Store( ):Valued(0){ }
 // Store<T>::Store( ){  Valued=0;}
template<class T>
T Store<T>::GetElem()
{
    if(Valued==0)
   {	
	cout<<"No item present!"<<endl;  
	exit(1);  //使程序完全退出，返回操作系统
    }
    return item;  //返回item中存放的数据
}

template<class T>
void Store<T>::PutElem(T x)
{
    Valued++;  //将此置为ture，表示item中已存入数值
    item=x;  //将x值存入item
}

void main()
{
	Student g(1000,23);

	Store<int> S1,S2; //声明两个Store<int>类对象     
	Store<Student> S3;//声明Store<Student>类对象S3   
	Store<double> D;//声明Store<double>类对象D   
	S1.PutElem(3);  //向对象S1中存入数据(初始化对象S1)
	S2.PutElem(-7);  //向对象S2中存入数据(初始化对象S2)
    cout<<S1.GetElem()<<" "<<S2.GetElem()<<endl;  	//S1和S2的数据成员
	S3.PutElem(g); //向对象S3中存入数据     
	cout<<S3.GetElem().id<<endl; //输出对象S3的数据成员
	cout<<"Retrieving object D"<<endl;
 	cout<<D.GetElem()<<endl; //输出对象D的数据成员
   //由于D未初始化，在执行函数D.GetElem()过程中导致程序终止

}