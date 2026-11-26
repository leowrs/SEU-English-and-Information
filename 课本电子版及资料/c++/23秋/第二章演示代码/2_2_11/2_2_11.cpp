#include <iostream>
using namespace std;

void main(){
	int  a=3, b=6, c=5;

	switch(a>0)
	{
  	case 1: switch(b<0)
			 {
				case 1: cout<<"aa"; break;
                case 2: cout<<"bb"; break;
			 }  
		
    case  0:switch(c==5)
			{
                case  0:  cout<<"cc"; break;
                case  1:  cout<<"dd"; break;
                default:  cout<<"ee"; break;
             }
     default: cout<<"ff"<<endl; 
	}
}