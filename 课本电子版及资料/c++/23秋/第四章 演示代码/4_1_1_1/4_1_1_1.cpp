#include <iostream>
using namespace std;

class   Location 
{
public:
	void init(int x,int y)
	{   
		X=x;  
		Y=y;   
	}
    int GetX()
	{ 
		return X; 
	}
    int GetY() 
	{ 
		return Y;
	}
private:    
    int X,Y; 
};  //系统不为类Location分配空间

void main()
{
	Location L,*Lp;    //当说明对象L时，才会为L分配空间
	Lp = & L;
	Lp->init(2,3);

	cout<<Lp->GetX()<<" "<<Lp->GetY()<<endl;
//	L.X=3;   //X是私有的，在类外是不能直接通过“类名.数据成员”来调用的。
}
