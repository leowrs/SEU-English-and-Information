#include <iostream>
using namespace std;

class C
{
 public:	
   C(int x,const char ch[],float n[])
     {   
		 i=x; 
		 num[0]=n[0];  
         num[1]=n[1]; 
		 for(int j=0;j<sizeof(name);j++)   
			 name[j]=ch[j]; 
	 }    
     void Print()
     {  cout<<i<<'\t'<<name<<'\t'<<num[0]<<'\t'<<num[1]<<endl; }
 private:
	int i;	  
	char name[20];	
	float num[2];
};

void main( )
{    
	float x[2]={77.8f,99.56f};
 	C c1(25, "张三", x);  // 对象的初始化
 	c1.Print();

}
