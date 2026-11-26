#include  <iostream>
using namespace std;
class Test
{
	int x,y;
public:
	Test(int a,int b)
	{
		x=a;  y=b;
		cout<<"调用了构造函数!\n";
	}
	Test(const Test &t)//若未定义，则系统提供默认拷贝构造函数
	{
		x=t.x;  y=t.y;
		cout<<"调用了拷贝构造函数!\n";
	}
	void Show() {  cout << "x="<<x<<'\t'<<"y="<<y<<endl; }
 };

void  main(void) 
{
      Test t1(10,10); //A
      Test  t2=t1;     //B
      Test  t3(t1);    //C
      t1.Show( );
      t2.Show( );
      t3.Show( ); 
}
