#include  <iostream>
using namespace std;

class  Rectangle
{
private:   
	int  Left,Right,Top,Bottom;
public:
      Rectangle(int L,int R,int T,int B)  
	  {
		  Left =L;    Right =R;    Top=T;   Bottom = B;
	      cout<<"调用带参数的构造函数!"<<endl;
	  } 
 // /*   
  Rectangle()
	 {
	    Left =0;     Right =0;     Top=0;	   Bottom = 0;
	    cout<<"调用不带参的构造函数!"<<endl;
     }   //*/
void Print( )   
{
	cout<<Left<<'\t'<<Right<<'\t'<<Top<<'\t'<<Bottom<<endl;
}

};

void main(void )
{ 
	Rectangle  r1(100,200,300,400);   		
	r1.Print();
	Rectangle  r2;//A
	r2.Print();						
}
