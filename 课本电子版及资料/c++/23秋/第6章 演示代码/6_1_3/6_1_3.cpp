// 求最大数的函数模板
#include <iostream>
using namespace std;

template<typename T>  //模板声明，其中T为类型参数
T max1(T a,T b) //定义一个通用函数，用T作虚拟的类型名
//注意 vs中已经提供了max函数模板，所以这里就不能再定义同名的max函数了
{ 
          return a>b?a:b;
}
int main( )
{
      int   i1=18,  i2=-12, i;
      double  d1=25.8,  d2=29.2, d;
      long   g1=6785,  g2=-91245, g; 
	  //第一部分：调用模板函数，非缺省
     i=max1(i1,i2);   //调用模板函数，此时T被int取代，也可缺省<int>
     d=max1<double>(d1,d2);  //调用模板函数，此时T被double取代
     g=max1<long>(g1,g2);    //调用模板函数，此时T被long取代
     cout<<"i_max="<<i<<endl;
     cout<<"f_max="<<d<<endl;
     cout<<"g_max="<<g<<endl;

     return 0;
}






 