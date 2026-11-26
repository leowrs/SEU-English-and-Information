#include  <iostream>
using namespace std;

class  Rectangle
{
private:   
	int  Left,Right,Top,Bottom;
public:
      Rectangle(int L=0,int R=0,int T=0,int B=0)  
	  {
		  Left =L;    Right =R;    Top=T;   Bottom = B;
//	      cout<<"调用带参数的构造函数!"<<endl;
	  } 
      void Print( )   
	  {
	      cout<<Left<<'\t'<<Right<<'\t'<<Top<<'\t'<<Bottom<<endl;
	  }
};


 
void main(void )
{ 
	cout<<"1.调用带参的构造函数："<<endl;
	Rectangle  r1(100,200,300,400); 
	r1.Print();

	cout<<"2.调用不带参的构造函数："<<endl;
	Rectangle  r2; 
	r2.Print();	
	
	cout<<"3.调用带部分参数的构造函数："<<endl;
	Rectangle r3(100,200);
	r3.Print();
}
