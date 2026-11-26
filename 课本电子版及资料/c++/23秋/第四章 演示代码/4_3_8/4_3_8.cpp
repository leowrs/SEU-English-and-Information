// 例子：析构函数
#include  <iostream>
using namespace std;
class  Q 
{
private:
     int  x,y;
public:
     Q(int a=0,int b=0)  
	 {  
		 x=a;
		 y=b;
	 }
     void P( ) 
	 {  
		 cout<<x<<','<<y<<endl; 
	 }
	 ~Q( ) 
	 { 
		 cout<<"调用析构函数,销毁对象中的数据x="<<x<<endl; 
	 }
};

void main( ) 
{
    Q  q(50,100);
    q.P();
    Q  qq;
    qq.P();
    cout<<"退出主函数"<<endl;
  }
