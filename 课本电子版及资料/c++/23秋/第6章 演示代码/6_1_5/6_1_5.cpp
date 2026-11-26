#include <iostream>
using namespace std;

template<typename numtype> //类模板声明 
class Compare //类模板名为Compare，定义通用的类
{ 
public:
       Compare(numtype a,numtype b)
	{   x=a;   y=b;   }
	   numtype max( ) ;   //成员函数max的声明
       numtype min( ) ;    //成员函数min的声明
 private:
       numtype x,y;
};

//在类模板外定义成员函数max()，具体格式看下两行的注释语句
template<typename numtype>      // template<模板参数表>
numtype Compare<numtype>::max() // 返回类型 类模板名<模板参数表>::成员函数名 (形参表)
{ return (x>y) ? x : y;  }

//在类模板外定义成员函数min()
template<typename numtype> 
numtype Compare<numtype>::min( )     
	{   return (x<y) ? x : y;     }

void main()
{
	
	Compare<double> com1(1.2,3.4);  //使用模板建立对象：        
                                  // 类模板名<模板参数表> 对象名1,...,对象名n；
	cout<<"最大值："<<com1.max()<<endl;
	cout<<"最小值："<<com1.min()<<endl;

}