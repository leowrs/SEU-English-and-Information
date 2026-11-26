#include<iostream>
using namespace std;
class  Part
{
 public:   
	 Part() 
	 {    
		 x=1;   
		 y=++x; 
	 }
     ~Part()
	 {    
		 y--;  
		 cout<<"y="<<y<<endl;   
	 }
     void number()
	 { cout<<"x="<<x<<endl;}
 protected:
	    int x, y;		
};
void main()
{
	   Part p1;
	   p1.number();
       
	   Part p2;
	   p2.number();
}
